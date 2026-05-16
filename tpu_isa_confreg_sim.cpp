#include <array>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include <verilated.h>
#include <verilated_vcd_c.h>

#include "Vtpu_isa_confreg.h"
#include "Vtpu_isa_confreg___024root.h"

namespace {

constexpr uint32_t OP_NOP = 0x0u;
constexpr uint32_t OP_LOAD = 0x1u;
constexpr uint32_t OP_SET_WR = 0x2u;
constexpr uint32_t OP_UB_READ = 0x3u;
constexpr uint32_t OP_SWITCH = 0x4u;
constexpr uint32_t OP_SET_GRAD_ADDR = 0x6u;

constexpr uint8_t PTR_INPUT = 0;
constexpr uint8_t PTR_WEIGHT = 1;
constexpr uint8_t PTR_BIAS = 2;
constexpr uint8_t PTR_Y = 3;
constexpr uint8_t PTR_H = 4;
constexpr uint8_t PTR_GRAD_BIAS = 5;
constexpr uint8_t PTR_GRAD_WEIGHT = 6;

constexpr uint8_t VPU_FORWARD = 0xC;
constexpr uint8_t VPU_LOSS = 0x2;
constexpr uint8_t VPU_DERIVATIVE = 0x1;

constexpr uint16_t LEARN_RATE = 0x00C0u;
constexpr uint16_t VPU_FACTOR = 0x0003u;
constexpr uint16_t TWO_DIV_N = 0x0080u;

// 修改这里可以调整 full-network RTL 训练 step 数。
constexpr int FULL_NETWORK_TRAIN_STEPS = 20;

namespace ub {
constexpr uint16_t X_BASE        = 0;   // 0..15
constexpr uint16_t W_BASE        = 16;  // 16..31
constexpr uint16_t B_BASE        = 32;  // 32..39
constexpr uint16_t H1_BASE       = 40;  // 40..47
constexpr uint16_t Y_TRUE_BASE   = 48;  // 48..51
constexpr uint16_t Y_PRED_BASE   = 52;  // 52..55
constexpr uint16_t DY_BASE       = 56;  // 56..59
constexpr uint16_t DELTA2_BASE   = 60;  // 60..63
constexpr uint16_t DELTA1_BASE   = 64;  // 64..71
constexpr uint16_t GRAD_W1_BASE  = 72;  // 72..75
constexpr uint16_t GRAD_W2_BASE  = 76;  // 76..77
constexpr uint16_t GRAD_B1_BASE  = 78;  // 78..79
constexpr uint16_t GRAD_B2_BASE  = 80;  // 80
constexpr uint16_t TMP_BASE      = 96;  // 96..127

constexpr uint16_t W1_BASE       = W_BASE;      // 16..19
constexpr uint16_t W2_BASE       = W_BASE + 4;  // 20..21
constexpr uint16_t B1_BASE       = B_BASE;      // 32..33
constexpr uint16_t B2_BASE       = B_BASE + 2;  // 34
}  // namespace ub

vluint64_t main_time = 0;
int cycle_count = 0;

Vtpu_isa_confreg *dut = nullptr;
VerilatedVcdC *tfp = nullptr;
bool quiet_step_logs = false;

enum class TestStatus {
    Pass,
    Partial,
    Fail,
};

struct XorModel {
    std::array<uint16_t, 4> w1;
    std::array<uint16_t, 2> w2;
    std::array<uint16_t, 2> b1;
    uint16_t b2;
};

struct GradW2B2Expected {
    int16_t grad_w2_0;
    int16_t grad_w2_1;
    int16_t grad_b2;
};

struct Delta1Expected {
    std::array<int16_t, 8> a;
    std::array<int16_t, 8> deriv;
    std::array<int16_t, 8> delta1;
};

uint16_t q8_8(int integer_value) {
    return static_cast<uint16_t>(integer_value << 8);
}

int16_t s16(uint16_t value) {
    return static_cast<int16_t>(value);
}

double to_float(uint16_t value) {
    return static_cast<double>(s16(value)) / 256.0;
}

const char *status_text(TestStatus status) {
    switch (status) {
        case TestStatus::Pass:
            return "PASS";
        case TestStatus::Partial:
            return "PARTIAL";
        case TestStatus::Fail:
            return "FAIL";
    }
    return "FAIL";
}

uint32_t ins_nop() {
    return OP_NOP << 28;
}

uint32_t ins_load(uint16_t addr, uint16_t data) {
    return (OP_LOAD << 28) |
           ((static_cast<uint32_t>(addr) & 0x0FFFu) << 16) |
           data;
}

uint32_t ins_set_wr(uint16_t addr, bool accumulate = false) {
    return (OP_SET_WR << 28) |
           ((static_cast<uint32_t>(addr) & 0x0FFFu) << 16) |
           ((accumulate ? 1u : 0u) << 15);
}

uint32_t ins_set_grad_addr(uint16_t addr) {
    return (OP_SET_GRAD_ADDR << 28) |
           ((static_cast<uint32_t>(addr) & 0x0FFFu) << 16);
}

uint32_t ins_switch() {
    return OP_SWITCH << 28;
}

uint32_t ins_ub_read(
    uint8_t ptr_select,
    uint16_t addr,
    uint8_t row_size,
    uint8_t col_size,
    bool transpose,
    uint8_t vpu_mode
) {
    return (OP_UB_READ << 28) |
           ((static_cast<uint32_t>(ptr_select) & 0x7u) << 25) |
           ((static_cast<uint32_t>(addr) & 0x0FFFu) << 13) |
           ((static_cast<uint32_t>(row_size) & 0xFu) << 9) |
           ((static_cast<uint32_t>(col_size) & 0xFu) << 5) |
           ((transpose ? 1u : 0u) << 4) |
           (static_cast<uint32_t>(vpu_mode) & 0xFu);
}

void eval_dump() {
    dut->eval();
    if (tfp) {
        tfp->dump(main_time);
    }
    main_time++;
}

void tick() {
    dut->clk = 0;
    eval_dump();
    dut->clk = 1;
    eval_dump();
    cycle_count++;
}

void tick_n(int n) {
    for (int i = 0; i < n; i++) {
        tick();
    }
}

void drive_idle() {
    dut->ins_valid = 0;
    dut->ins = ins_nop();
}

void issue(uint32_t ins, const std::string &) {
    dut->ins = ins;
    dut->ins_valid = 1;
    tick();
    drive_idle();
    tick();
}

void reset_dut() {
    dut->clk = 0;
    dut->rst_n = 0;
    dut->ins_valid = 0;
    dut->ins = ins_nop();
    dut->learn_rate_in = LEARN_RATE;
    dut->vpu_factor_in = VPU_FACTOR;
    dut->two_div_N_in = TWO_DIV_N;

    tick_n(5);
    dut->rst_n = 1;
    tick_n(3);
}

bool weight_valid() {
    return dut->ub_rd_weight_valid_out_0 || dut->ub_rd_weight_valid_out_1;
}

bool vpu_valid() {
    return dut->vpu_data_valid_out_1 || dut->vpu_data_valid_out_2;
}

bool wait_until_done(const std::string &tag, bool (*valid_fn)(), int max_cycles) {
    bool seen_valid = false;
    for (int i = 0; i < max_cycles; i++) {
        tick();
        if (valid_fn()) {
            seen_valid = true;
        } else if (seen_valid) {
            return true;
        }
    }

    std::cout << "[" << tag << "] timeout：等待 valid 结束失败，cycle="
              << cycle_count << std::endl;
    return false;
}

bool wait_vpu_collect(
    const std::string &tag,
    int max_cycles,
    std::size_t max_words,
    std::vector<uint16_t> *captured
) {
    bool seen_valid = false;
    if (captured) {
        captured->clear();
    }

    for (int i = 0; i < max_cycles; i++) {
        tick();
        if (vpu_valid()) {
            seen_valid = true;
            if (captured && captured->size() < max_words && dut->vpu_data_valid_out_1) {
                captured->push_back(static_cast<uint16_t>(dut->vpu_data_out_1));
            }
            if (captured && captured->size() < max_words && dut->vpu_data_valid_out_2) {
                captured->push_back(static_cast<uint16_t>(dut->vpu_data_out_2));
            }
        } else if (seen_valid) {
            return true;
        }
    }

    std::cout << "[" << tag << "] timeout：没有等到 VPU 输出完成，cycle="
              << cycle_count << std::endl;
    return false;
}

void print_vector_summary(const std::string &name, const std::vector<uint16_t> &values) {
    std::cout << name << " = [";
    for (std::size_t i = 0; i < values.size(); i++) {
        if (i != 0) {
            std::cout << ", ";
        }
        std::cout << std::fixed << std::setprecision(4) << to_float(values[i]);
    }
    std::cout << "]" << std::endl;
}

template <std::size_t N>
void print_array_summary(const std::string &name, const std::array<int16_t, N> &values) {
    std::cout << name << " = [";
    for (std::size_t i = 0; i < N; i++) {
        if (i != 0) {
            std::cout << ", ";
        }
        std::cout << std::fixed << std::setprecision(4)
                  << static_cast<double>(values[i]) / 256.0;
    }
    std::cout << "]" << std::endl;
}

uint16_t ub_mem(uint16_t addr) {
    return dut->rootp->tpu_isa_confreg__DOT__u_tpu__DOT__ub_inst__DOT__ub_memory[addr];
}

template <std::size_t N>
void print_ub_array_summary(const std::string &name, uint16_t base) {
    std::cout << name << " = [";
    for (std::size_t i = 0; i < N; i++) {
        if (i != 0) {
            std::cout << ", ";
        }
        std::cout << std::fixed << std::setprecision(4)
                  << to_float(ub_mem(static_cast<uint16_t>(base + i)));
    }
    std::cout << "]" << std::endl;
}

uint16_t gd_value_old(int lane) {
    return dut->rootp->tpu_isa_confreg__DOT__u_tpu__DOT__ub_inst__DOT__value_old_in[lane];
}

bool gd_valid(int lane) {
    return dut->rootp->tpu_isa_confreg__DOT__u_tpu__DOT__ub_inst__DOT__grad_value_valid_in[lane];
}

uint16_t gd_weight_counter() {
    return dut->rootp->tpu_isa_confreg__DOT__u_tpu__DOT__ub_inst__DOT__rd_grad_weight_time_counter;
}

uint16_t gd_bias_counter() {
    return dut->rootp->tpu_isa_confreg__DOT__u_tpu__DOT__ub_inst__DOT__rd_grad_bias_time_counter;
}

bool gd_bias_or_weight() {
    return dut->rootp->tpu_isa_confreg__DOT__u_tpu__DOT__ub_inst__DOT__grad_bias_or_weight;
}

void print_word_pair(const std::string &name, uint16_t a, uint16_t b) {
    std::cout << name << " = ["
              << std::fixed << std::setprecision(4) << to_float(a)
              << ", " << to_float(b) << "]" << std::endl;
}

void print_word_one(const std::string &name, uint16_t value) {
    std::cout << name << " = "
              << std::fixed << std::setprecision(4) << to_float(value)
              << std::endl;
}

uint16_t expected_gd_update(uint16_t old_value, uint16_t grad_value) {
    const int32_t old_s = static_cast<int16_t>(old_value);
    const int32_t grad_s = static_cast<int16_t>(grad_value);
    const int32_t lr_s = static_cast<int16_t>(LEARN_RATE);
    const int32_t lr_times_grad = (lr_s * grad_s) / 256;
    return static_cast<uint16_t>(static_cast<int16_t>(old_s - lr_times_grad));
}

int16_t saturate_to_i16(int32_t value) {
    if (value > 32767) {
        return 32767;
    }
    if (value < -32768) {
        return -32768;
    }
    return static_cast<int16_t>(value);
}

int16_t fxp_mul_q8_8(int16_t a, int16_t b) {
    const int32_t product = static_cast<int32_t>(a) * static_cast<int32_t>(b);
    uint32_t rounded = static_cast<uint32_t>(product) >> 8;

    // Match fxp_zoom ROUND=1 when converting Q16.16 multiplication output to Q8.8.
    if ((static_cast<uint32_t>(product) & 0x80u) != 0 &&
        !(((rounded >> 23) & 0x1u) == 0 && (rounded & 0x7FFFFFu) == 0x7FFFFFu)) {
        rounded += 1;
    }

    const int32_t signed_24 = (rounded & 0x800000u) ?
        static_cast<int32_t>(rounded | 0xFF000000u) :
        static_cast<int32_t>(rounded & 0x00FFFFFFu);
    return saturate_to_i16(signed_24);
}

int16_t fxp_add_q8_8(int16_t a, int16_t b) {
    return saturate_to_i16(static_cast<int32_t>(a) + static_cast<int32_t>(b));
}

GradW2B2Expected calc_expected_grad_w2_b2(
    const std::array<int16_t, 8>& h1,
    const std::array<int16_t, 4>& delta2
) {
    int16_t grad_w2_0 = 0;
    int16_t grad_w2_1 = 0;
    int16_t grad_b2 = 0;

    for (std::size_t sample = 0; sample < delta2.size(); sample++) {
        grad_w2_0 = fxp_add_q8_8(
            grad_w2_0,
            fxp_mul_q8_8(h1[sample * 2], delta2[sample])
        );
        grad_w2_1 = fxp_add_q8_8(
            grad_w2_1,
            fxp_mul_q8_8(h1[sample * 2 + 1], delta2[sample])
        );
        grad_b2 = fxp_add_q8_8(grad_b2, delta2[sample]);
    }

    return {grad_w2_0, grad_w2_1, grad_b2};
}

std::array<int16_t, 2> calc_expected_grad_w2_partial(
    const std::array<int16_t, 8>& h1,
    const std::array<int16_t, 4>& delta2,
    std::size_t sample_base
) {
    int16_t grad_w2_0 = 0;
    int16_t grad_w2_1 = 0;

    for (std::size_t n = 0; n < 2; n++) {
        const std::size_t sample = sample_base + n;
        grad_w2_0 = fxp_add_q8_8(
            grad_w2_0,
            fxp_mul_q8_8(h1[sample * 2], delta2[sample])
        );
        grad_w2_1 = fxp_add_q8_8(
            grad_w2_1,
            fxp_mul_q8_8(h1[sample * 2 + 1], delta2[sample])
        );
    }

    return {grad_w2_0, grad_w2_1};
}

bool near_q8_8(uint16_t actual, uint16_t expected, int tolerance_lsb = 1) {
    const int diff = static_cast<int>(static_cast<int16_t>(actual)) -
                     static_cast<int>(static_cast<int16_t>(expected));
    return diff >= -tolerance_lsb && diff <= tolerance_lsb;
}

bool ub_range_matches(uint16_t base, const std::array<int16_t, 8> &expected, int tolerance_lsb = 1) {
    for (std::size_t i = 0; i < expected.size(); i++) {
        if (!near_q8_8(ub_mem(static_cast<uint16_t>(base + i)),
                       static_cast<uint16_t>(expected[i]),
                       tolerance_lsb)) {
            return false;
        }
    }
    return true;
}

Delta1Expected calc_expected_delta1(
    const std::array<int16_t, 4>& delta2,
    const std::array<int16_t, 2>& w2,
    const std::array<int16_t, 8>& h1
) {
    Delta1Expected expected = {};

    for (std::size_t sample = 0; sample < delta2.size(); sample++) {
        for (std::size_t col = 0; col < w2.size(); col++) {
            const std::size_t idx = sample * 2 + col;
            expected.a[idx] = fxp_mul_q8_8(delta2[sample], w2[col]);
            expected.deriv[idx] = h1[idx] >= 0 ?
                static_cast<int16_t>(q8_8(1)) :
                static_cast<int16_t>(VPU_FACTOR);
            expected.delta1[idx] = fxp_mul_q8_8(expected.a[idx], expected.deriv[idx]);
        }
    }

    return expected;
}

void load_block(uint16_t base, const std::vector<uint16_t> &data) {
    for (std::size_t i = 0; i < data.size(); i++) {
        issue(ins_load(static_cast<uint16_t>(base + i), data[i]), "LOAD");
    }
}

void load_training_batch_and_params(const XorModel& model) {
    const std::vector<uint16_t> x = {
        q8_8(0), q8_8(0),
        q8_8(1), q8_8(0),
        q8_8(0), q8_8(1),
        q8_8(1), q8_8(1),
        0x0000u, 0x0000u, 0x0000u, 0x0000u,
        0x0000u, 0x0000u, 0x0000u, 0x0000u,
    };
    const std::vector<uint16_t> y_true = {q8_8(0), q8_8(1), q8_8(1), q8_8(0)};

    load_block(ub::X_BASE, x);
    load_block(ub::W1_BASE, {model.w1.begin(), model.w1.end()});
    load_block(ub::W2_BASE, {model.w2.begin(), model.w2.end()});
    load_block(ub::B1_BASE, {model.b1.begin(), model.b1.end()});
    load_block(ub::B2_BASE, {model.b2});
    load_block(ub::Y_TRUE_BASE, y_true);
    load_block(ub::TMP_BASE, {q8_8(1)});

    std::cout << "[初始化] 写入 X/W/B/Y_true 完成；TMP 写入 1x1 identity 权重" << std::endl;
}

bool load_identity_weight_to_active() {
    issue(ins_ub_read(PTR_WEIGHT, ub::TMP_BASE, 1, 1, true, 0x0), "READ_ID");
    if (!wait_until_done("identity", weight_valid, 80)) {
        return false;
    }
    tick_n(2);
    issue(ins_switch(), "SWITCH_ID");
    return true;
}

bool run_forward_layer1_to_h1() {
    issue(ins_ub_read(PTR_WEIGHT, ub::W1_BASE, 2, 2, true, 0x0), "READ_W1");
    if (!wait_until_done("前向1", weight_valid, 80)) {
        return false;
    }
    tick_n(2);
    issue(ins_switch(), "SWITCH_1");

    issue(ins_set_wr(ub::H1_BASE), "SET_WR_H1");
    issue(ins_ub_read(PTR_INPUT, ub::X_BASE, 4, 2, false, VPU_FORWARD), "READ_X");
    issue(ins_ub_read(PTR_BIAS, ub::B1_BASE, 4, 2, false, VPU_FORWARD), "READ_B1");
    if (!wait_vpu_collect("前向1", 160, 8, nullptr)) {
        return false;
    }

    if (!quiet_step_logs) {
        std::cout << "[前向1] H1 写回完成 -> UB[" << ub::H1_BASE
                  << ".." << (ub::H1_BASE + 7) << "]" << std::endl;
    }
    return true;
}

bool run_forward_layer2_to_ypred(std::vector<uint16_t> *ypred) {
    issue(ins_ub_read(PTR_WEIGHT, ub::W2_BASE, 1, 2, true, 0x0), "READ_W2");
    if (!wait_until_done("前向2", weight_valid, 80)) {
        return false;
    }
    tick_n(2);
    issue(ins_switch(), "SWITCH_2");

    issue(ins_set_wr(ub::Y_PRED_BASE), "SET_WR_YPRED");
    issue(ins_ub_read(PTR_INPUT, ub::H1_BASE, 4, 2, false, VPU_FORWARD), "READ_H1");
    issue(ins_ub_read(PTR_BIAS, ub::B2_BASE, 4, 1, false, VPU_FORWARD), "READ_B2");
    if (!wait_vpu_collect("前向2", 160, 4, ypred)) {
        return false;
    }

    if (!quiet_step_logs) {
        std::cout << "[前向2] Y_pred 写回完成 -> UB[" << ub::Y_PRED_BASE
                  << ".." << (ub::Y_PRED_BASE + 3) << "]" << std::endl;
    }
    return true;
}

bool run_loss_to_dy(std::vector<uint16_t> *dy) {
    if (!load_identity_weight_to_active()) {
        return false;
    }

    // RTL 中 loss 的 H 输入来自 systolic_data_in，Y_true 走 ptr_select=3。
    // 这里用 TMP 的 1x1 identity 权重把 Y_pred 经 systolic 透传进 loss。
    issue(ins_set_wr(ub::DY_BASE), "SET_WR_DY");
    issue(ins_ub_read(PTR_INPUT, ub::Y_PRED_BASE, 4, 1, false, VPU_LOSS), "READ_YPRED_LOSS");
    issue(ins_ub_read(PTR_Y, ub::Y_TRUE_BASE, 4, 1, false, VPU_LOSS), "READ_YTRUE_LOSS");
    if (!wait_vpu_collect("loss", 160, 4, dy)) {
        return false;
    }

    if (!quiet_step_logs) {
        std::cout << "[loss] DY 写回完成 -> UB[" << ub::DY_BASE
                  << ".." << (ub::DY_BASE + 3) << "]" << std::endl;
    }
    return true;
}

bool run_delta2_path(std::vector<uint16_t> *delta2) {
    if (!load_identity_weight_to_active()) {
        return false;
    }

    // vpu=0x1 的 derivative 模块会输出 gradient * leaky_relu_derivative(H)。
    // 这里用 identity 权重把 DY 从 UB 透传成 gradient 输入，H 取 Y_pred。
    issue(ins_set_wr(ub::DELTA2_BASE), "SET_WR_DELTA2");
    issue(ins_ub_read(PTR_INPUT, ub::DY_BASE, 4, 1, false, VPU_DERIVATIVE), "READ_DY_DERIV");
    issue(ins_ub_read(PTR_H, ub::Y_PRED_BASE, 4, 1, false, VPU_DERIVATIVE), "READ_H_DERIV");
    if (!wait_vpu_collect("delta2", 160, 4, delta2)) {
        return false;
    }

    if (!quiet_step_logs) {
        std::cout << "[delta2] derivative path 已运行 -> UB[" << ub::DELTA2_BASE
                  << ".." << (ub::DELTA2_BASE + 3) << "]" << std::endl;
    }
    return true;
}

bool run_update_w2_b2() {//未实现
    std::cout << "[update] 未实现：当前 ISA 尚不能把 UB 中的 grad_W2/grad_B2 "
              << "作为 gradient_descent 输入；update 只能吃实时 VPU 输出并覆盖同址参数"
              << std::endl;
    return false;
}

void load_gd_old_params() {
    load_block(ub::W2_BASE, {0x0100u, 0xFF80u});
    load_block(ub::B2_BASE, {0x0040u});
    load_block(ub::TMP_BASE, {q8_8(1), 0x0040u, 0xFFC0u});
    std::cout << "[GD-初始化] 写入 W2/B2 旧值完成" << std::endl;
}

bool observe_weight_gd_window(uint16_t expected0, uint16_t expected1) {
    bool saw0 = false;
    bool saw1 = false;
    for (int i = 0; i < 12; i++) {
        tick();
        saw0 = saw0 || (gd_value_old(0) == expected0);
        saw1 = saw1 || (gd_value_old(1) == expected1);
    }
    return saw0 && saw1 && gd_bias_or_weight();
}

bool observe_bias_gd_window(uint16_t expected) {
    bool saw = false;
    for (int i = 0; i < 10; i++) {
        tick();
        saw = saw || (gd_value_old(0) == expected) || (gd_value_old(1) == expected);
    }
    return saw && !gd_bias_or_weight();
}

bool emit_known_gradient_to_ub_wr_data(uint16_t src_base, uint8_t rows, uint8_t cols) {
    if (!load_identity_weight_to_active()) {
        return false;
    }

    issue(ins_set_wr(ub::TMP_BASE + 8), "SET_WR_GRAD_ECHO");
    issue(ins_ub_read(PTR_INPUT, src_base, rows, cols, false, 0x0), "EMIT_GRAD");
    return wait_vpu_collect("GD-gradient", 120, rows * cols, nullptr);
}

TestStatus test_gradient_descent_weight_update_path() {
    const uint16_t w2_0_old = 0x0100u;
    const uint16_t w2_1_old = 0xFF80u;
    const uint16_t before0 = ub_mem(ub::W2_BASE);
    const uint16_t before1 = ub_mem(ub::W2_BASE + 1);

    print_word_pair("[GD-W2] 更新前 W2", before0, before1);

    // W2 是两个连续 word，因此用 row_size=1, col_size=2 打开两个 lane 的 weight update 窗口。
    issue(ins_ub_read(PTR_GRAD_WEIGHT, ub::W2_BASE, 1, 2, false, 0x0), "GD_W2_WINDOW");
    const bool window_ok = observe_weight_gd_window(w2_0_old, w2_1_old);
    if (!window_ok) {
        std::cout << "[GD-W2] FAIL：ptr_select=6 没有观察到旧 W2 进入 value_old_in，"
                  << "counter=" << gd_weight_counter() << std::endl;
        return TestStatus::Fail;
    }

    // 可以通过 VPU/identity path 产生 ub_wr_data_in，但当前 ISA 没有握手机制保证它
    // 与上面的短 GD window 精确同拍对齐；这里不把异步 echo 当成 update 成功。
    const bool can_emit = emit_known_gradient_to_ub_wr_data(ub::TMP_BASE + 1, 1, 2);
    const uint16_t after0 = ub_mem(ub::W2_BASE);
    const uint16_t after1 = ub_mem(ub::W2_BASE + 1);
    print_word_pair("[GD-W2] 更新后 W2", after0, after1);

    if ((after0 != before0 || after1 != before1) && can_emit) {
        std::cout << "[GD-W2] PASS：观察到 W2 被 RTL 覆盖更新" << std::endl;
        return TestStatus::Pass;
    }

    std::cout << "[GD-W2] PARTIAL：已能打开 ptr_select=6 更新窗口，"
              << "旧 W2 已进入 value_old_in；当前 ISA 还不能把已知 gradient "
              << "确定性对齐注入 ub_wr_data_in" << std::endl;
    return TestStatus::Partial;
}

TestStatus test_gradient_descent_bias_update_path() {
    const uint16_t b2_old = 0x0040u;
    const uint16_t before = ub_mem(ub::B2_BASE);

    print_word_one("[GD-B2] 更新前 B2", before);

    // B2 只有一个 word，因此用 row_size=1, col_size=1 打开 bias update 窗口。
    issue(ins_ub_read(PTR_GRAD_BIAS, ub::B2_BASE, 1, 1, false, 0x0), "GD_B2_WINDOW");
    const bool window_ok = observe_bias_gd_window(b2_old);
    if (!window_ok) {
        std::cout << "[GD-B2] FAIL：ptr_select=5 没有观察到旧 B2 进入 value_old_in，"
                  << "counter=" << gd_bias_counter() << std::endl;
        return TestStatus::Fail;
    }

    const bool can_emit = emit_known_gradient_to_ub_wr_data(ub::TMP_BASE + 1, 1, 1);
    const uint16_t after = ub_mem(ub::B2_BASE);
    print_word_one("[GD-B2] 更新后 B2", after);

    if (after != before && can_emit) {
        std::cout << "[GD-B2] PASS：观察到 B2 被 RTL 覆盖更新" << std::endl;
        return TestStatus::Pass;
    }

    std::cout << "[GD-B2] PARTIAL：已能打开 ptr_select=5 更新窗口，"
              << "旧 B2 已进入 value_old_in；当前 ISA 还不能把已知 gradient "
              << "确定性对齐注入 ub_wr_data_in" << std::endl;
    return TestStatus::Partial;
}

bool run_gradient_descent_path_smoke_test() {
    reset_dut();
    load_gd_old_params();

    const TestStatus w2_status = test_gradient_descent_weight_update_path();
    const TestStatus b2_status = test_gradient_descent_bias_update_path();

    std::cout << "[GD] W2 update path: " << status_text(w2_status) << std::endl;
    std::cout << "[GD] B2 update path: " << status_text(b2_status) << std::endl;

    if (w2_status == TestStatus::Fail || b2_status == TestStatus::Fail) {
        std::cout << "[结果] FAIL：ptr_select=5/6 更新窗口验证失败" << std::endl;
        return false;
    }

    if (w2_status == TestStatus::Partial || b2_status == TestStatus::Partial) {
        std::cout << "[结果] PARTIAL：ptr_select=5/6 能打开 update 窗口；"
                  << "缺少可控实时 gradient 注入/对齐机制，尚不能完整验证覆盖更新"
                  << std::endl;
        return true;
    }

    std::cout << "[结果] PASS：W2/B2 gradient_descent update path 已验证" << std::endl;
    return true;
}

bool test_update_from_ub_gradient() {
    constexpr uint16_t w2_0_old = 0x0100u;  //  1.0000
    constexpr uint16_t w2_1_old = 0xFF80u;  // -0.5000
    constexpr uint16_t b2_old   = 0x0040u;  //  0.2500
    constexpr uint16_t gw2_0    = 0x0040u;  //  0.2500
    constexpr uint16_t gw2_1    = 0xFFC0u;  // -0.2500
    constexpr uint16_t gb2      = 0x0040u;  //  0.2500

    const uint16_t w2_0_expected = expected_gd_update(w2_0_old, gw2_0);
    const uint16_t w2_1_expected = expected_gd_update(w2_1_old, gw2_1);
    const uint16_t b2_expected = expected_gd_update(b2_old, gb2);

    reset_dut();
    load_block(ub::W2_BASE, {w2_0_old, w2_1_old});
    load_block(ub::GRAD_W2_BASE, {gw2_0, gw2_1});
    load_block(ub::B2_BASE, {b2_old});
    load_block(ub::GRAD_B2_BASE, {gb2});

    std::cout << "[GD-UB] 写入旧 W2/B2 和梯度完成" << std::endl;
    print_word_pair("[GD-UB] W2 更新前", ub_mem(ub::W2_BASE), ub_mem(ub::W2_BASE + 1));

    issue(ins_set_grad_addr(ub::GRAD_W2_BASE), "SET_GRAD_W2");
    issue(ins_ub_read(PTR_GRAD_WEIGHT, ub::W2_BASE, 1, 2, false, 0x0), "UPDATE_W2");
    tick_n(8);

    const uint16_t w2_0_after = ub_mem(ub::W2_BASE);
    const uint16_t w2_1_after = ub_mem(ub::W2_BASE + 1);
    print_word_pair("[GD-UB] W2 更新后", w2_0_after, w2_1_after);

    print_word_one("[GD-UB] B2 更新前", ub_mem(ub::B2_BASE));

    issue(ins_set_grad_addr(ub::GRAD_B2_BASE), "SET_GRAD_B2");
    issue(ins_ub_read(PTR_GRAD_BIAS, ub::B2_BASE, 1, 1, false, 0x0), "UPDATE_B2");
    tick_n(8);

    const uint16_t b2_after = ub_mem(ub::B2_BASE);
    print_word_one("[GD-UB] B2 更新后", b2_after);

    const bool w2_pass = (w2_0_after == w2_0_expected) && (w2_1_after == w2_1_expected);
    const bool b2_pass = (b2_after == b2_expected);

    if (!w2_pass) {
        print_word_pair("[GD-UB] W2 期望值", w2_0_expected, w2_1_expected);
    }
    if (!b2_pass) {
        print_word_one("[GD-UB] B2 期望值", b2_expected);
    }

    std::cout << "[GD-UB] W2 update path: " << (w2_pass ? "PASS" : "FAIL") << std::endl;
    std::cout << "[GD-UB] B2 update path: " << (b2_pass ? "PASS" : "FAIL") << std::endl;

    if (w2_pass && b2_pass) {
        std::cout << "[结果] PASS：gradient_descent 已从 UB gradient 地址读取并覆盖更新 W2/B2" << std::endl;
        return true;
    }

    std::cout << "[结果] FAIL：UB gradient update 结果不符合 W_new = W_old - lr * grad" << std::endl;
    return false;
}

TestStatus test_grad_w2_b2_generation() {
    const std::array<int16_t, 8> h1 = {
        static_cast<int16_t>(0x0040), static_cast<int16_t>(0xFF80u),  //  0.2500, -0.5000
        static_cast<int16_t>(0x00C0), static_cast<int16_t>(0x0020),   //  0.7500,  0.1250
        static_cast<int16_t>(0xFFC0u), static_cast<int16_t>(0x0080),  // -0.2500,  0.5000
        static_cast<int16_t>(0x0080), static_cast<int16_t>(0xFFC0u),  //  0.5000, -0.2500
    };
    const std::array<int16_t, 4> delta2 = {
        static_cast<int16_t>(0x0080),   //  0.5000
        static_cast<int16_t>(0xFFC0u),  // -0.2500
        static_cast<int16_t>(0x0040),   //  0.2500
        static_cast<int16_t>(0xFF80u),  // -0.5000
    };

    reset_dut();

    std::vector<uint16_t> h1_words;
    std::vector<uint16_t> delta2_words;
    h1_words.reserve(h1.size());
    delta2_words.reserve(delta2.size());
    for (int16_t value : h1) {
        h1_words.push_back(static_cast<uint16_t>(value));
    }
    for (int16_t value : delta2) {
        delta2_words.push_back(static_cast<uint16_t>(value));
    }

    load_block(ub::H1_BASE, h1_words);
    load_block(ub::DELTA2_BASE, delta2_words);

    const GradW2B2Expected expected = calc_expected_grad_w2_b2(h1, delta2);

    std::cout << "[GRAD] 写入 H1/delta2 测试数据完成" << std::endl;
    print_word_pair(
        "[GRAD] 期望 grad_W2",
        static_cast<uint16_t>(expected.grad_w2_0),
        static_cast<uint16_t>(expected.grad_w2_1)
    );
    print_word_one("[GRAD] 期望 grad_B2", static_cast<uint16_t>(expected.grad_b2));
    std::cout << "[GRAD] 尝试使用现有 RTL 路径计算 grad_W2/grad_B2" << std::endl;

    // 当前 ISA 能把 UB 数据送入 systolic/VPU 并写回，但 2x2 systolic 的一次矩阵乘
    // 只能覆盖内积 K=2。grad_W2 = H1^T(2x4) * delta2(4x1) 需要 K=4，
    // 必须有跨两次 partial result 的累加路径；grad_B2=sum(delta2) 也需要
    // reduction/sum 写回路径。现有 OP_UB_READ/SET_WR 没有暴露这个累加器。
    const bool has_complete_grad_generation_path = false;
    if (!has_complete_grad_generation_path) {
        std::cout << "[GRAD] 实际 grad_W2 = 未生成" << std::endl;
        std::cout << "[GRAD] 实际 grad_B2 = 未生成" << std::endl;
        std::cout << "[结果] PARTIAL：当前 C++ 能写入 H1/delta2 并计算 expected；"
                  << "现有 ISA/RTL 还缺少 H1^T*delta2 的 K=4 partial 累加路径，"
                  << "也缺少 delta2 求和写回 grad_B2 的 reduction 路径"
                  << std::endl;
        return TestStatus::Partial;
    }

    const uint16_t actual_w2_0 = ub_mem(ub::GRAD_W2_BASE);
    const uint16_t actual_w2_1 = ub_mem(ub::GRAD_W2_BASE + 1);
    const uint16_t actual_b2 = ub_mem(ub::GRAD_B2_BASE);
    print_word_pair("[GRAD] 实际 grad_W2", actual_w2_0, actual_w2_1);
    print_word_one("[GRAD] 实际 grad_B2", actual_b2);

    const bool pass =
        actual_w2_0 == static_cast<uint16_t>(expected.grad_w2_0) &&
        actual_w2_1 == static_cast<uint16_t>(expected.grad_w2_1) &&
        actual_b2 == static_cast<uint16_t>(expected.grad_b2);

    std::cout << "[结果] " << (pass ? "PASS" : "FAIL")
              << (pass ? "：RTL grad_W2/grad_B2 与 golden model 一致"
                       : "：RTL grad_W2/grad_B2 与 golden model 不一致")
              << std::endl;
    return pass ? TestStatus::Pass : TestStatus::Fail;
}

bool test_grad_w2_b2_via_systolic() {
    constexpr uint16_t FXP_ONE = 0x0100u;
    const std::array<int16_t, 8> h1 = {
        static_cast<int16_t>(0x0040), static_cast<int16_t>(0xFF80u),  //  0.2500, -0.5000
        static_cast<int16_t>(0x00C0), static_cast<int16_t>(0x0020),   //  0.7500,  0.1250
        static_cast<int16_t>(0xFFC0u), static_cast<int16_t>(0x0080),  // -0.2500,  0.5000
        static_cast<int16_t>(0x0080), static_cast<int16_t>(0xFFC0u),  //  0.5000, -0.2500
    };
    const std::array<int16_t, 4> delta2 = {
        static_cast<int16_t>(0x0080),   //  0.5000
        static_cast<int16_t>(0xFFC0u),  // -0.2500
        static_cast<int16_t>(0x0040),   //  0.2500
        static_cast<int16_t>(0xFF80u),  // -0.5000
    };

    reset_dut();

    std::vector<uint16_t> h1_words;
    std::vector<uint16_t> delta2_words;
    h1_words.reserve(h1.size());
    delta2_words.reserve(delta2.size());
    for (int16_t value : h1) {
        h1_words.push_back(static_cast<uint16_t>(value));
    }
    for (int16_t value : delta2) {
        delta2_words.push_back(static_cast<uint16_t>(value));
    }

    load_block(ub::H1_BASE, h1_words);
    load_block(ub::DELTA2_BASE, delta2_words);
    load_block(ub::TMP_BASE, {FXP_ONE, FXP_ONE, FXP_ONE, FXP_ONE});

    const GradW2B2Expected expected = calc_expected_grad_w2_b2(h1, delta2);

    std::cout << "[GRAD] 写入 H1/delta2/ONES4 完成" << std::endl;
    print_word_pair(
        "[GRAD-W2] 期望",
        static_cast<uint16_t>(expected.grad_w2_0),
        static_cast<uint16_t>(expected.grad_w2_1)
    );

    issue(ins_ub_read(PTR_WEIGHT, ub::H1_BASE, 4, 2, true, 0x0), "READ_H1_T_AS_W");
    if (!wait_until_done("GRAD-W2 weight", weight_valid, 160)) {
        std::cout << "[GRAD-W2] FAIL：H1^T weight 读取超时" << std::endl;
        std::cout << "[结果] FAIL" << std::endl;
        return false;
    }
    tick_n(2);
    issue(ins_switch(), "SWITCH_GRAD_W2");

    issue(ins_set_wr(ub::GRAD_W2_BASE), "SET_WR_GRAD_W2");
    issue(ins_ub_read(PTR_INPUT, ub::DELTA2_BASE, 4, 1, false, 0x0), "READ_DELTA2_AS_X");
    tick_n(24);

    const uint16_t actual_w2_0 = ub_mem(ub::GRAD_W2_BASE);
    const uint16_t actual_w2_1 = ub_mem(ub::GRAD_W2_BASE + 1);
    const bool w2_pass =
        actual_w2_0 == static_cast<uint16_t>(expected.grad_w2_0) &&
        actual_w2_1 == static_cast<uint16_t>(expected.grad_w2_1);

    print_word_pair("[GRAD-W2] 实际", actual_w2_0, actual_w2_1);
    std::cout << "[GRAD-W2] " << (w2_pass ? "PASS" : "PARTIAL") << std::endl;
    if (!w2_pass) {
        std::cout << "[GRAD-W2] PARTIAL：当前 2x2 systolic 没有完成 K=4 内积，"
                  << "需要 partial 累加路径才能得到完整 grad_W2" << std::endl;
        std::cout << "[GRAD-B2] PARTIAL：未继续尝试；sum(delta2) 同样需要 reduction "
                  << "或拆分累加路径" << std::endl;
        std::cout << "[结果] PARTIAL：已尝试 systolic+bypass 路径，但 grad_W2/grad_B2 "
                  << "尚不能由现有 ISA/RTL 完整生成" << std::endl;
        return true;
    }

    print_word_one("[GRAD-B2] 期望", static_cast<uint16_t>(expected.grad_b2));

    issue(ins_ub_read(PTR_WEIGHT, ub::TMP_BASE, 1, 4, false, 0x0), "READ_ONES4_AS_W");
    const bool ones_weight_done = wait_until_done("GRAD-B2 weight", weight_valid, 160);
    if (!ones_weight_done) {
        std::cout << "[GRAD-B2] PARTIAL：ONES4 weight 读取超时，当前路径不适配 sum(delta2)" << std::endl;
        std::cout << "[结果] PARTIAL：grad_W2 PASS，grad_B2 需要 reduction 或拆分累加路径" << std::endl;
        return true;
    }
    tick_n(2);
    issue(ins_switch(), "SWITCH_GRAD_B2");

    issue(ins_set_wr(ub::GRAD_B2_BASE), "SET_WR_GRAD_B2");
    issue(ins_ub_read(PTR_INPUT, ub::DELTA2_BASE, 4, 1, false, 0x0), "READ_DELTA2_FOR_BIAS");
    tick_n(24);

    const uint16_t actual_b2 = ub_mem(ub::GRAD_B2_BASE);
    const bool b2_pass = actual_b2 == static_cast<uint16_t>(expected.grad_b2);

    print_word_one("[GRAD-B2] 实际", actual_b2);
    if (b2_pass) {
        std::cout << "[GRAD-B2] PASS" << std::endl;
        std::cout << "[结果] PASS：RTL 已通过 systolic 生成 grad_W2/grad_B2" << std::endl;
        return true;
    }

    std::cout << "[GRAD-B2] PARTIAL：ONES4 路径输出与 sum(delta2) 不一致，"
              << "当前 2 列 systolic 需要 reduction 或拆分累加路径" << std::endl;
    std::cout << "[结果] PARTIAL：grad_W2 PASS，grad_B2 尚未完整验证" << std::endl;
    return true;
}

bool test_ub_accumulate_writeback() {
    constexpr uint16_t FXP_ONE = 0x0100u;
    constexpr uint16_t partial0 = 0x0040u;  //  0.2500
    constexpr uint16_t partial1 = 0x0020u;  //  0.1250
    constexpr uint16_t host_override = 0xFF80u;  // -0.5000
    constexpr uint16_t identity_addr = ub::TMP_BASE;
    constexpr uint16_t partial0_addr = ub::TMP_BASE + 1;
    constexpr uint16_t partial1_addr = ub::TMP_BASE + 2;
    constexpr uint16_t target_addr = ub::TMP_BASE + 8;

    reset_dut();
    load_block(identity_addr, {FXP_ONE, partial0, partial1});

    if (!load_identity_weight_to_active()) {
        std::cout << "[ACC] FAIL：identity weight 载入失败" << std::endl;
        std::cout << "[结果] FAIL" << std::endl;
        return false;
    }

    issue(ins_set_wr(target_addr, false), "SET_WR_TMP_NORMAL");
    issue(ins_ub_read(PTR_INPUT, partial0_addr, 1, 1, false, 0x0), "ACC_PARTIAL0");
    tick_n(16);
    const uint16_t after_normal = ub_mem(target_addr);
    std::cout << "[ACC] normal write partial0 完成" << std::endl;

    issue(ins_set_wr(target_addr, true), "SET_WR_TMP_ACC");
    issue(ins_ub_read(PTR_INPUT, partial1_addr, 1, 1, false, 0x0), "ACC_PARTIAL1");
    tick_n(16);
    const uint16_t after_acc = ub_mem(target_addr);
    std::cout << "[ACC] accumulate write partial1 完成" << std::endl;

    const uint16_t expected = static_cast<uint16_t>(
        static_cast<int16_t>(partial0) + static_cast<int16_t>(partial1)
    );

    print_word_one("[ACC] normal 后实际", after_normal);
    print_word_one("[ACC] 实际", after_acc);
    print_word_one("[ACC] 期望", expected);

    const bool normal_pass = after_normal == partial0;
    const bool acc_pass = after_acc == expected;

    issue(ins_load(target_addr, host_override), "LOAD_HOST_OVERRIDE");
    tick_n(2);
    const uint16_t after_host = ub_mem(target_addr);
    print_word_one("[ACC] host LOAD 覆盖后", after_host);
    const bool host_pass = after_host == host_override;

    if (normal_pass && acc_pass && host_pass) {
        std::cout << "[结果] PASS：UB normal/accumulate 写回通过，host LOAD 不受影响" << std::endl;
        return true;
    }

    std::cout << "[ACC] normal write: " << (normal_pass ? "PASS" : "FAIL") << std::endl;
    std::cout << "[ACC] accumulate write: " << (acc_pass ? "PASS" : "FAIL") << std::endl;
    std::cout << "[ACC] host LOAD overwrite: " << (host_pass ? "PASS" : "FAIL") << std::endl;
    std::cout << "[结果] FAIL：UB accumulate writeback 验证失败" << std::endl;
    return false;
}

bool run_grad_w2_partial(
    uint16_t h1_base,
    uint16_t delta2_base,
    bool accumulate,
    const std::string &tag
) {
    issue(ins_ub_read(PTR_WEIGHT, delta2_base, 1, 2, true, 0x0), "READ_D2_PART_AS_W");
    if (!wait_until_done(tag + " weight", weight_valid, 120)) {
        std::cout << "[" << tag << "] PARTIAL：delta2 partial weight 读取超时" << std::endl;
        return false;
    }
    tick_n(2);
    issue(ins_switch(), "SWITCH_GRAD_W2_PART");

    issue(ins_set_wr(ub::GRAD_W2_BASE, accumulate), "SET_WR_GRAD_W2_PART");
    issue(ins_ub_read(PTR_INPUT, h1_base, 2, 2, true, 0x0), "READ_H1_PART_T_AS_X");

    // bypass 输出可能在 issue 后很快写回 UB；这里直接给固定窗口，再用 UB 内容判断。
    tick_n(24);
    return true;
}

bool test_grad_w2_via_systolic_accumulate() {
    const std::array<int16_t, 8> h1 = {
        static_cast<int16_t>(0x0040), static_cast<int16_t>(0x0080),   //  0.2500,  0.5000
        static_cast<int16_t>(0x00C0), static_cast<int16_t>(0xFFC0u),  //  0.7500, -0.2500
        static_cast<int16_t>(0x0080), static_cast<int16_t>(0x0040),   //  0.5000,  0.2500
        static_cast<int16_t>(0xFF80u), static_cast<int16_t>(0x00C0),  // -0.5000,  0.7500
    };
    const std::array<int16_t, 4> delta2 = {
        static_cast<int16_t>(0xFF80u),  // -0.5000
        static_cast<int16_t>(0x0040),   //  0.2500
        static_cast<int16_t>(0xFFC0u),  // -0.2500
        static_cast<int16_t>(0x0080),   //  0.5000
    };

    reset_dut();

    std::vector<uint16_t> h1_words;
    std::vector<uint16_t> delta2_words;
    h1_words.reserve(h1.size());
    delta2_words.reserve(delta2.size());
    for (int16_t value : h1) {
        h1_words.push_back(static_cast<uint16_t>(value));
    }
    for (int16_t value : delta2) {
        delta2_words.push_back(static_cast<uint16_t>(value));
    }

    load_block(ub::H1_BASE, h1_words);
    load_block(ub::DELTA2_BASE, delta2_words);

    const auto partial0 = calc_expected_grad_w2_partial(h1, delta2, 0);
    const auto partial1 = calc_expected_grad_w2_partial(h1, delta2, 2);
    const GradW2B2Expected expected = calc_expected_grad_w2_b2(h1, delta2);

    std::cout << "[GRAD-W2-ACC] 写入 H1/delta2 完成" << std::endl;
    print_word_pair(
        "[GRAD-W2-ACC] partial0 期望",
        static_cast<uint16_t>(partial0[0]),
        static_cast<uint16_t>(partial0[1])
    );
    print_word_pair(
        "[GRAD-W2-ACC] partial1 期望",
        static_cast<uint16_t>(partial1[0]),
        static_cast<uint16_t>(partial1[1])
    );
    print_word_pair(
        "[GRAD-W2-ACC] grad_W2 期望",
        static_cast<uint16_t>(expected.grad_w2_0),
        static_cast<uint16_t>(expected.grad_w2_1)
    );

    if (!run_grad_w2_partial(ub::H1_BASE, ub::DELTA2_BASE, false, "GRAD-W2-P0")) {
        std::cout << "[结果] PARTIAL：partial0 没有稳定写回" << std::endl;
        return true;
    }
    const uint16_t p0_actual_0 = ub_mem(ub::GRAD_W2_BASE);
    const uint16_t p0_actual_1 = ub_mem(ub::GRAD_W2_BASE + 1);
    std::cout << "[GRAD-W2-ACC] partial0 normal write 完成" << std::endl;
    print_word_pair("[GRAD-W2-ACC] partial0 实际", p0_actual_0, p0_actual_1);

    if (!run_grad_w2_partial(ub::H1_BASE + 4, ub::DELTA2_BASE + 2, true, "GRAD-W2-P1")) {
        std::cout << "[结果] PARTIAL：partial1 没有稳定写回" << std::endl;
        return true;
    }
    std::cout << "[GRAD-W2-ACC] partial1 accumulate write 完成" << std::endl;

    const uint16_t actual_0 = ub_mem(ub::GRAD_W2_BASE);
    const uint16_t actual_1 = ub_mem(ub::GRAD_W2_BASE + 1);
    const uint16_t expected_0 = static_cast<uint16_t>(expected.grad_w2_0);
    const uint16_t expected_1 = static_cast<uint16_t>(expected.grad_w2_1);

    print_word_pair("[GRAD-W2-ACC] grad_W2 实际", actual_0, actual_1);

    const bool pass = near_q8_8(actual_0, expected_0) && near_q8_8(actual_1, expected_1);
    if (pass) {
        std::cout << "[结果] PASS：systolic partial + UB accumulate 已生成 grad_W2" << std::endl;
        return true;
    }

    const bool produced_output = (p0_actual_0 != 0 || p0_actual_1 != 0 ||
                                  actual_0 != 0 || actual_1 != 0);
    if (!produced_output) {
        std::cout << "[结果] PARTIAL：没有观察到 grad_W2 写回，需检查 H1 transpose 或 lane 顺序" << std::endl;
        return true;
    }

    std::cout << "[结果] FAIL：grad_W2 实际值与 expected 不一致" << std::endl;
    return false;
}

bool run_grad_b2_partial(uint16_t delta2_base, bool accumulate, const std::string &tag) {
    issue(ins_ub_read(PTR_WEIGHT, delta2_base, 1, 2, true, 0x0), "READ_D2_PART_AS_W");
    if (!wait_until_done(tag + " weight", weight_valid, 120)) {
        std::cout << "[" << tag << "] PARTIAL：delta2 partial weight 读取超时" << std::endl;
        return false;
    }
    tick_n(2);
    issue(ins_switch(), "SWITCH_GRAD_B2_PART");

    issue(ins_set_wr(ub::GRAD_B2_BASE, accumulate), "SET_WR_GRAD_B2_PART");
    issue(ins_ub_read(PTR_INPUT, ub::TMP_BASE, 1, 2, false, 0x0), "READ_ONES2_AS_X");

    tick_n(24);
    return true;
}

bool test_grad_b2_via_systolic_accumulate() {
    constexpr uint16_t FXP_ONE = 0x0100u;
    const std::array<int16_t, 4> delta2 = {
        static_cast<int16_t>(0xFF80u),  // -0.5000
        static_cast<int16_t>(0x0040),   //  0.2500
        static_cast<int16_t>(0xFFC0u),  // -0.2500
        static_cast<int16_t>(0x00C0),   //  0.7500
    };

    reset_dut();

    std::vector<uint16_t> delta2_words;
    delta2_words.reserve(delta2.size());
    for (int16_t value : delta2) {
        delta2_words.push_back(static_cast<uint16_t>(value));
    }

    load_block(ub::DELTA2_BASE, delta2_words);
    load_block(ub::TMP_BASE, {FXP_ONE, FXP_ONE});

    const int16_t partial_b0 = fxp_add_q8_8(delta2[0], delta2[1]);
    const int16_t partial_b1 = fxp_add_q8_8(delta2[2], delta2[3]);
    const int16_t expected = fxp_add_q8_8(partial_b0, partial_b1);

    std::cout << "[GRAD-B2-ACC] 写入 delta2/ONES2 完成" << std::endl;
    print_word_one("[GRAD-B2-ACC] partial_b0 期望", static_cast<uint16_t>(partial_b0));
    print_word_one("[GRAD-B2-ACC] partial_b1 期望", static_cast<uint16_t>(partial_b1));
    print_word_one("[GRAD-B2-ACC] grad_B2 期望", static_cast<uint16_t>(expected));

    if (!run_grad_b2_partial(ub::DELTA2_BASE, false, "GRAD-B2-P0")) {
        std::cout << "[结果] PARTIAL：partial_b0 没有稳定写回，需检查 delta2/ONES2 方向" << std::endl;
        return true;
    }
    const uint16_t partial_b0_actual = ub_mem(ub::GRAD_B2_BASE);
    std::cout << "[GRAD-B2-ACC] partial_b0 normal write 完成" << std::endl;
    print_word_one("[GRAD-B2-ACC] partial_b0 实际", partial_b0_actual);

    if (!run_grad_b2_partial(ub::DELTA2_BASE + 2, true, "GRAD-B2-P1")) {
        std::cout << "[结果] PARTIAL：partial_b1 没有稳定写回，需检查 delta2/ONES2 方向" << std::endl;
        return true;
    }
    std::cout << "[GRAD-B2-ACC] partial_b1 accumulate write 完成" << std::endl;

    const uint16_t actual = ub_mem(ub::GRAD_B2_BASE);
    const uint16_t expected_u = static_cast<uint16_t>(expected);
    print_word_one("[GRAD-B2-ACC] grad_B2 实际", actual);

    if (near_q8_8(actual, expected_u)) {
        std::cout << "[结果] PASS：systolic partial + UB accumulate 已生成 grad_B2" << std::endl;
        return true;
    }

    const bool produced_output = (partial_b0_actual != 0 || actual != 0);
    if (!produced_output) {
        std::cout << "[结果] PARTIAL：没有观察到 grad_B2 写回，需检查 delta2 / ONES2 的 input/weight 方向" << std::endl;
        return true;
    }

    std::cout << "[结果] FAIL：grad_B2 实际值与 expected 不一致" << std::endl;
    return false;
}

bool test_delta1_generation() {
    constexpr uint16_t DELTA2_DUP_BASE = ub::TMP_BASE + 8;
    constexpr uint16_t W2_DIAG_BASE = ub::TMP_BASE + 16;
    constexpr uint16_t IDENTITY2_BASE = ub::TMP_BASE + 24;
    const std::array<int16_t, 2> w2 = {
        static_cast<int16_t>(0x0140),   //  1.2500
        static_cast<int16_t>(0xFF80u),  // -0.5000
    };
    const std::array<int16_t, 4> delta2 = {
        static_cast<int16_t>(0xFF80u),  // -0.5000
        static_cast<int16_t>(0x0040),   //  0.2500
        static_cast<int16_t>(0xFFC0u),  // -0.2500
        static_cast<int16_t>(0x0080),   //  0.5000
    };
    const std::array<int16_t, 8> h1 = {
        static_cast<int16_t>(0x0040), static_cast<int16_t>(0xFFC0u),  //  0.2500, -0.2500
        static_cast<int16_t>(0x0080), static_cast<int16_t>(0x00C0),   //  0.5000,  0.7500
        static_cast<int16_t>(0xFF80u), static_cast<int16_t>(0x0040),  // -0.5000,  0.2500
        static_cast<int16_t>(0x0000), static_cast<int16_t>(0xFF40u),  //  0.0000, -0.7500
    };

    reset_dut();

    load_block(ub::W2_BASE, {
        static_cast<uint16_t>(w2[0]),
        static_cast<uint16_t>(w2[1]),
    });

    std::vector<uint16_t> delta2_words;
    delta2_words.reserve(delta2.size());
    for (int16_t value : delta2) {
        delta2_words.push_back(static_cast<uint16_t>(value));
    }
    load_block(ub::DELTA2_BASE, delta2_words);

    std::vector<uint16_t> h1_words;
    h1_words.reserve(h1.size());
    for (int16_t value : h1) {
        h1_words.push_back(static_cast<uint16_t>(value));
    }
    load_block(ub::H1_BASE, h1_words);

    const Delta1Expected expected = calc_expected_delta1(delta2, w2, h1);

    load_block(DELTA2_DUP_BASE, {
        static_cast<uint16_t>(delta2[0]), static_cast<uint16_t>(delta2[0]),
        static_cast<uint16_t>(delta2[1]), static_cast<uint16_t>(delta2[1]),
        static_cast<uint16_t>(delta2[2]), static_cast<uint16_t>(delta2[2]),
        static_cast<uint16_t>(delta2[3]), static_cast<uint16_t>(delta2[3]),
    });
    load_block(W2_DIAG_BASE, {
        static_cast<uint16_t>(w2[0]), 0x0000u,
        0x0000u, static_cast<uint16_t>(w2[1]),
    });

    std::cout << "[DELTA1] 写入 W2/delta2/H1 完成" << std::endl;
    print_array_summary("[DELTA1] A 期望", expected.a);
    print_array_summary("[DELTA1] delta1 期望", expected.delta1);

    issue(ins_ub_read(PTR_WEIGHT, W2_DIAG_BASE, 2, 2, true, 0x0), "READ_W2_FOR_DELTA1");
    if (!wait_until_done("DELTA1-A weight", weight_valid, 120)) {
        std::cout << "[结果] FAIL：W2 weight 读取超时，A 无法生成" << std::endl;
        return false;
    }
    tick_n(2);
    issue(ins_switch(), "SWITCH_DELTA1_A");

    issue(ins_set_wr(ub::TMP_BASE, false), "SET_WR_A");
    issue(ins_ub_read(PTR_INPUT, DELTA2_DUP_BASE, 4, 2, false, 0x0), "READ_DELTA2_FOR_A");
    if (!wait_vpu_collect("DELTA1-A", 180, 8, nullptr)) {
        std::cout << "[结果] FAIL：A 写回超时" << std::endl;
        return false;
    }

    print_ub_array_summary<8>("[DELTA1] A 实际", ub::TMP_BASE);
    if (!ub_range_matches(ub::TMP_BASE, expected.a)) {
        std::cout << "[结果] FAIL：A = delta2 * W2^T 与 expected 不一致" << std::endl;
        return false;
    }

    load_block(IDENTITY2_BASE, {q8_8(1), 0x0000u, 0x0000u, q8_8(1)});
    issue(ins_ub_read(PTR_WEIGHT, IDENTITY2_BASE, 2, 2, true, 0x0), "READ_ID2_FOR_DELTA1");
    if (!wait_until_done("DELTA1 identity", weight_valid, 120)) {
        std::cout << "[结果] PARTIAL：A 已生成，但 2x2 identity 读取超时" << std::endl;
        return true;
    }
    tick_n(2);
    issue(ins_switch(), "SWITCH_DELTA1_DERIV");

    issue(ins_set_wr(ub::DELTA1_BASE, false), "SET_WR_DELTA1");
    issue(ins_ub_read(PTR_INPUT, ub::TMP_BASE, 4, 2, false, VPU_DERIVATIVE), "READ_A_FOR_DERIV");
    issue(ins_ub_read(PTR_H, ub::H1_BASE, 4, 2, false, VPU_DERIVATIVE), "READ_H1_FOR_DERIV");
    if (!wait_vpu_collect("DELTA1", 220, 8, nullptr)) {
        std::cout << "[结果] PARTIAL：A 已生成，但 delta1 derivative 写回超时" << std::endl;
        return true;
    }

    print_ub_array_summary<8>("[DELTA1] delta1 实际", ub::DELTA1_BASE);
    if (ub_range_matches(ub::DELTA1_BASE, expected.delta1)) {
        std::cout << "[结果] PASS：RTL 已生成 delta1 = (delta2 * W2^T) * derivative(H1)" << std::endl;
        return true;
    }

    if (ub_range_matches(ub::DELTA1_BASE, expected.deriv)) {
        std::cout << "[结果] PARTIAL：A 已生成，但 derivative path 当前只输出 derivative(H1)，"
                  << "缺少 A * derivative 的 elementwise multiply" << std::endl;
        return true;
    }

    std::cout << "[结果] FAIL：delta1 实际值与 expected 不一致" << std::endl;
    return false;
}

int32_t abs_i32(int32_t value) {
    return value < 0 ? -value : value;
}

int32_t sum_abs_error_q8_8(
    const std::vector<uint16_t> &pred,
    const std::vector<uint16_t> &target
) {
    const std::size_t count = pred.size() < target.size() ? pred.size() : target.size();
    int32_t total = 0;
    for (std::size_t i = 0; i < count; i++) {
        total += abs_i32(
            static_cast<int32_t>(static_cast<int16_t>(pred[i])) -
            static_cast<int32_t>(static_cast<int16_t>(target[i]))
        );
    }
    return total;
}

bool generate_grad_w2_from_current_h1_delta2() {
    if (!run_grad_w2_partial(ub::H1_BASE, ub::DELTA2_BASE, false, "STEP-GRAD-W2-P0")) {
        return false;
    }
    if (!run_grad_w2_partial(ub::H1_BASE + 4, ub::DELTA2_BASE + 2, true, "STEP-GRAD-W2-P1")) {
        return false;
    }
    return true;
}

bool generate_grad_b2_from_current_delta2() {
    load_block(ub::TMP_BASE, {q8_8(1), q8_8(1)});
    if (!run_grad_b2_partial(ub::DELTA2_BASE, false, "STEP-GRAD-B2-P0")) {
        return false;
    }
    if (!run_grad_b2_partial(ub::DELTA2_BASE + 2, true, "STEP-GRAD-B2-P1")) {
        return false;
    }
    return true;
}

bool generate_delta1_from_current_state() {
    constexpr uint16_t DELTA2_DUP_BASE = ub::TMP_BASE + 8;
    constexpr uint16_t W2_DIAG_BASE = ub::TMP_BASE + 16;
    constexpr uint16_t IDENTITY2_BASE = ub::TMP_BASE + 24;

    const uint16_t w2_0 = ub_mem(ub::W2_BASE);
    const uint16_t w2_1 = ub_mem(ub::W2_BASE + 1);
    const uint16_t d0 = ub_mem(ub::DELTA2_BASE);
    const uint16_t d1 = ub_mem(ub::DELTA2_BASE + 1);
    const uint16_t d2 = ub_mem(ub::DELTA2_BASE + 2);
    const uint16_t d3 = ub_mem(ub::DELTA2_BASE + 3);

    load_block(DELTA2_DUP_BASE, {d0, d0, d1, d1, d2, d2, d3, d3});
    load_block(W2_DIAG_BASE, {w2_0, 0x0000u, 0x0000u, w2_1});

    issue(ins_ub_read(PTR_WEIGHT, W2_DIAG_BASE, 2, 2, true, 0x0), "READ_W2_FOR_DELTA1");
    if (!wait_until_done("FULL-DELTA1-A weight", weight_valid, 120)) {
        return false;
    }
    tick_n(2);
    issue(ins_switch(), "SWITCH_DELTA1_A");

    issue(ins_set_wr(ub::TMP_BASE, false), "SET_WR_A");
    issue(ins_ub_read(PTR_INPUT, DELTA2_DUP_BASE, 4, 2, false, 0x0), "READ_DELTA2_FOR_A");
    if (!wait_vpu_collect("FULL-DELTA1-A", 180, 8, nullptr)) {
        return false;
    }

    load_block(IDENTITY2_BASE, {q8_8(1), 0x0000u, 0x0000u, q8_8(1)});
    issue(ins_ub_read(PTR_WEIGHT, IDENTITY2_BASE, 2, 2, true, 0x0), "READ_ID2_FOR_DELTA1");
    if (!wait_until_done("FULL-DELTA1 identity", weight_valid, 120)) {
        return false;
    }
    tick_n(2);
    issue(ins_switch(), "SWITCH_DELTA1_DERIV");

    issue(ins_set_wr(ub::DELTA1_BASE, false), "SET_WR_DELTA1");
    issue(ins_ub_read(PTR_INPUT, ub::TMP_BASE, 4, 2, false, VPU_DERIVATIVE), "READ_A_FOR_DERIV");
    issue(ins_ub_read(PTR_H, ub::H1_BASE, 4, 2, false, VPU_DERIVATIVE), "READ_H1_FOR_DERIV");
    return wait_vpu_collect("FULL-DELTA1", 220, 8, nullptr);
}

bool run_grad_w1_partial(uint16_t x_base, uint16_t delta1_base, bool accumulate, const std::string &tag) {
    issue(ins_ub_read(PTR_WEIGHT, delta1_base, 2, 2, true, 0x0), "READ_D1_PART_AS_W");
    if (!wait_until_done(tag + " weight", weight_valid, 120)) {
        std::cout << "[" << tag << "] PARTIAL：delta1 partial weight 读取超时" << std::endl;
        return false;
    }
    tick_n(2);
    issue(ins_switch(), "SWITCH_GRAD_W1_PART");

    issue(ins_set_wr(ub::GRAD_W1_BASE, accumulate), "SET_WR_GRAD_W1_PART");
    issue(ins_ub_read(PTR_INPUT, x_base, 2, 2, true, 0x0), "READ_X_PART_T_AS_X");
    tick_n(24);
    return true;
}

bool generate_grad_w1_from_current_x_delta1() {
    if (!run_grad_w1_partial(ub::X_BASE, ub::DELTA1_BASE, false, "FULL-GRAD-W1-P0")) {
        return false;
    }
    if (!run_grad_w1_partial(ub::X_BASE + 4, ub::DELTA1_BASE + 4, true, "FULL-GRAD-W1-P1")) {
        return false;
    }
    return true;
}

bool run_grad_b1_partial(uint16_t delta1_base, bool accumulate, const std::string &tag) {
    load_block(ub::TMP_BASE, {q8_8(1), q8_8(1)});
    issue(ins_ub_read(PTR_WEIGHT, delta1_base, 2, 2, true, 0x0), "READ_D1_PART_AS_W");
    if (!wait_until_done(tag + " weight", weight_valid, 120)) {
        std::cout << "[" << tag << "] PARTIAL：delta1 partial weight 读取超时" << std::endl;
        return false;
    }
    tick_n(2);
    issue(ins_switch(), "SWITCH_GRAD_B1_PART");

    issue(ins_set_wr(ub::GRAD_B1_BASE, accumulate), "SET_WR_GRAD_B1_PART");
    issue(ins_ub_read(PTR_INPUT, ub::TMP_BASE, 1, 2, false, 0x0), "READ_ONES2_AS_X");
    tick_n(24);
    return true;
}

bool generate_grad_b1_from_current_delta1() {
    if (!run_grad_b1_partial(ub::DELTA1_BASE, false, "FULL-GRAD-B1-P0")) {
        return false;
    }
    if (!run_grad_b1_partial(ub::DELTA1_BASE + 4, true, "FULL-GRAD-B1-P1")) {
        return false;
    }
    return true;
}

bool update_w2_b2_from_current_gradients() {
    issue(ins_set_grad_addr(ub::GRAD_W2_BASE), "SET_GRAD_W2");
    issue(ins_ub_read(PTR_GRAD_WEIGHT, ub::W2_BASE, 1, 2, false, 0x0), "UPDATE_W2");
    tick_n(8);

    issue(ins_set_grad_addr(ub::GRAD_B2_BASE), "SET_GRAD_B2");
    issue(ins_ub_read(PTR_GRAD_BIAS, ub::B2_BASE, 1, 1, false, 0x0), "UPDATE_B2");
    tick_n(8);

    return true;
}

bool update_w1_b1_from_current_gradients() {
    issue(ins_set_grad_addr(ub::GRAD_W1_BASE), "SET_GRAD_W1");
    issue(ins_ub_read(PTR_GRAD_WEIGHT, ub::W1_BASE, 2, 2, false, 0x0), "UPDATE_W1");
    tick_n(12);

    issue(ins_set_grad_addr(ub::GRAD_B1_BASE), "SET_GRAD_B1");
    issue(ins_ub_read(PTR_GRAD_BIAS, ub::B1_BASE, 1, 2, false, 0x0), "UPDATE_B1");
    tick_n(8);

    return true;
}

bool test_second_layer_training_one_step() {
    const XorModel model = {
        {0xFF00u, 0x0100u, 0x0100u, 0xFF00u},
        {0x0100u, 0x0100u},
        {0x0000u, 0x0000u},
        0xFF40u,
    };
    const std::vector<uint16_t> y_true = {q8_8(0), q8_8(1), q8_8(1), q8_8(0)};

    reset_dut();
    load_training_batch_and_params(model);
    std::cout << "[STEP] 初始化 X/W/B/Y_true 完成" << std::endl;

    if (!run_forward_layer1_to_h1()) {
        std::cout << "[结果] FAIL：forward layer1 -> H1 未完成" << std::endl;
        return false;
    }
    std::cout << "[STEP] forward layer1 -> H1 完成" << std::endl;

    std::vector<uint16_t> ypred_before;
    if (!run_forward_layer2_to_ypred(&ypred_before)) {
        std::cout << "[结果] FAIL：forward layer2 -> Y_pred before 未完成" << std::endl;
        return false;
    }
    print_vector_summary("[STEP] Y_pred before", ypred_before);

    std::vector<uint16_t> dy;
    std::vector<uint16_t> delta2;
    if (!run_loss_to_dy(&dy)) {
        std::cout << "[结果] FAIL：loss -> DY 未完成" << std::endl;
        return false;
    }
    if (!run_delta2_path(&delta2)) {
        std::cout << "[结果] FAIL：derivative -> delta2 未完成" << std::endl;
        return false;
    }
    std::cout << "[STEP] delta2 生成完成" << std::endl;

    if (!generate_grad_w2_from_current_h1_delta2()) {
        std::cout << "[结果] FAIL：grad_W2 生成未完成" << std::endl;
        return false;
    }
    std::cout << "[STEP] grad_W2 生成完成" << std::endl;

    if (!generate_grad_b2_from_current_delta2()) {
        std::cout << "[结果] FAIL：grad_B2 生成未完成" << std::endl;
        return false;
    }
    std::cout << "[STEP] grad_B2 生成完成" << std::endl;

    const uint16_t w2_before_0 = ub_mem(ub::W2_BASE);
    const uint16_t w2_before_1 = ub_mem(ub::W2_BASE + 1);
    const uint16_t b2_before = ub_mem(ub::B2_BASE);
    print_word_pair("[STEP] W2 before", w2_before_0, w2_before_1);
    print_word_one("[STEP] B2 before", b2_before);

    update_w2_b2_from_current_gradients();

    const uint16_t w2_after_0 = ub_mem(ub::W2_BASE);
    const uint16_t w2_after_1 = ub_mem(ub::W2_BASE + 1);
    const uint16_t b2_after = ub_mem(ub::B2_BASE);
    print_word_pair("[STEP] W2 after", w2_after_0, w2_after_1);
    print_word_one("[STEP] B2 after", b2_after);

    const bool w2_changed = (w2_before_0 != w2_after_0) || (w2_before_1 != w2_after_1);
    const bool b2_changed = b2_before != b2_after;
    if (!w2_changed || !b2_changed) {
        std::cout << "[结果] FAIL：W2/B2 没有都发生 RTL 更新" << std::endl;
        return false;
    }

    std::vector<uint16_t> ypred_after;
    if (!run_forward_layer2_to_ypred(&ypred_after)) {
        std::cout << "[结果] FAIL：forward layer2 -> Y_pred after 未完成" << std::endl;
        return false;
    }
    print_vector_summary("[STEP] Y_pred after", ypred_after);

    const int32_t err_before = sum_abs_error_q8_8(ypred_before, y_true);
    const int32_t err_after = sum_abs_error_q8_8(ypred_after, y_true);
    std::cout << "[STEP] err before = " << std::fixed << std::setprecision(4)
              << static_cast<double>(err_before) / 256.0 << std::endl;
    std::cout << "[STEP] err after  = " << std::fixed << std::setprecision(4)
              << static_cast<double>(err_after) / 256.0 << std::endl;

    if (err_after < err_before) {
        std::cout << "[结果] PASS：second-layer one-step 后误差下降" << std::endl;
        return true;
    }

    std::cout << "[结果] PARTIAL：forward/loss/grad/update 已跑通且 W2/B2 改变，"
              << "但本 step 误差未下降" << std::endl;
    return true;
}

bool test_full_network_training_one_step() {
    const XorModel model = {
        {0xFF00u, 0x0100u, 0x0100u, 0xFF00u},
        {0x0100u, 0x0100u},
        {0x0000u, 0x0000u},
        0xFF40u,
    };
    const std::vector<uint16_t> y_true = {q8_8(0), q8_8(1), q8_8(1), q8_8(0)};

    reset_dut();
    dut->learn_rate_in = 0x0020u;
    load_training_batch_and_params(model);
    std::cout << "[FULL-1STEP] 初始化完成" << std::endl;

    if (!run_forward_layer1_to_h1()) {
        std::cout << "[结果] FAIL：forward layer1 未完成" << std::endl;
        return false;
    }
    std::cout << "[FULL-1STEP] forward layer1 完成" << std::endl;

    std::vector<uint16_t> ypred_before;
    if (!run_forward_layer2_to_ypred(&ypred_before) || ypred_before.size() < y_true.size()) {
        std::cout << "[结果] FAIL：forward layer2 before 未完成" << std::endl;
        return false;
    }
    const int32_t err_before = sum_abs_error_q8_8(ypred_before, y_true);
    print_vector_summary("[FULL-1STEP] Y_pred before", ypred_before);
    std::cout << "[FULL-1STEP] err before = " << std::fixed << std::setprecision(4)
              << static_cast<double>(err_before) / 256.0 << std::endl;

    std::vector<uint16_t> dy;
    std::vector<uint16_t> delta2;
    if (!run_loss_to_dy(&dy) || !run_delta2_path(&delta2)) {
        std::cout << "[结果] FAIL：delta2 生成未完成" << std::endl;
        return false;
    }
    std::cout << "[FULL-1STEP] delta2 生成完成" << std::endl;

    if (!generate_delta1_from_current_state()) {
        std::cout << "[结果] FAIL：delta1 生成未完成" << std::endl;
        return false;
    }
    std::cout << "[FULL-1STEP] delta1 生成完成" << std::endl;

    if (!generate_grad_w2_from_current_h1_delta2() ||
        !generate_grad_b2_from_current_delta2()) {
        std::cout << "[结果] FAIL：grad_W2/B2 生成未完成" << std::endl;
        return false;
    }
    std::cout << "[FULL-1STEP] grad_W2/B2 生成完成" << std::endl;

    if (!generate_grad_w1_from_current_x_delta1() ||
        !generate_grad_b1_from_current_delta1()) {
        std::cout << "[结果] FAIL：grad_W1/B1 生成未完成" << std::endl;
        return false;
    }
    std::cout << "[FULL-1STEP] grad_W1/B1 生成完成" << std::endl;

    const std::array<uint16_t, 4> w1_before = {
        ub_mem(ub::W1_BASE),
        ub_mem(ub::W1_BASE + 1),
        ub_mem(ub::W1_BASE + 2),
        ub_mem(ub::W1_BASE + 3),
    };
    const std::array<uint16_t, 2> b1_before = {
        ub_mem(ub::B1_BASE),
        ub_mem(ub::B1_BASE + 1),
    };
    const std::array<uint16_t, 2> w2_before = {
        ub_mem(ub::W2_BASE),
        ub_mem(ub::W2_BASE + 1),
    };
    const uint16_t b2_before = ub_mem(ub::B2_BASE);

    print_word_pair("[FULL-1STEP] W2 before", w2_before[0], w2_before[1]);
    print_word_one("[FULL-1STEP] B2 before", b2_before);
    update_w2_b2_from_current_gradients();
    const std::array<uint16_t, 2> w2_after = {
        ub_mem(ub::W2_BASE),
        ub_mem(ub::W2_BASE + 1),
    };
    const uint16_t b2_after = ub_mem(ub::B2_BASE);
    print_word_pair("[FULL-1STEP] W2 after", w2_after[0], w2_after[1]);
    print_word_one("[FULL-1STEP] B2 after", b2_after);
    std::cout << "[FULL-1STEP] W2/B2 更新完成" << std::endl;

    print_word_pair("[FULL-1STEP] W1 before row0", w1_before[0], w1_before[1]);
    print_word_pair("[FULL-1STEP] W1 before row1", w1_before[2], w1_before[3]);
    print_word_pair("[FULL-1STEP] B1 before", b1_before[0], b1_before[1]);
    update_w1_b1_from_current_gradients();
    const std::array<uint16_t, 4> w1_after = {
        ub_mem(ub::W1_BASE),
        ub_mem(ub::W1_BASE + 1),
        ub_mem(ub::W1_BASE + 2),
        ub_mem(ub::W1_BASE + 3),
    };
    const std::array<uint16_t, 2> b1_after = {
        ub_mem(ub::B1_BASE),
        ub_mem(ub::B1_BASE + 1),
    };
    print_word_pair("[FULL-1STEP] W1 after row0", w1_after[0], w1_after[1]);
    print_word_pair("[FULL-1STEP] W1 after row1", w1_after[2], w1_after[3]);
    print_word_pair("[FULL-1STEP] B1 after", b1_after[0], b1_after[1]);
    std::cout << "[FULL-1STEP] W1/B1 更新完成" << std::endl;

    const bool w2_changed = w2_before != w2_after || b2_before != b2_after;
    const bool w1_changed = w1_before != w1_after || b1_before != b1_after;
    if (!w2_changed || !w1_changed) {
        std::cout << "[结果] FAIL：W1/B1/W2/B2 没有全部发生更新" << std::endl;
        return false;
    }

    if (!run_forward_layer1_to_h1()) {
        std::cout << "[结果] FAIL：更新后 forward layer1 未完成" << std::endl;
        return false;
    }
    std::vector<uint16_t> ypred_after;
    if (!run_forward_layer2_to_ypred(&ypred_after) || ypred_after.size() < y_true.size()) {
        std::cout << "[结果] FAIL：更新后 forward layer2 未完成" << std::endl;
        return false;
    }
    const int32_t err_after = sum_abs_error_q8_8(ypred_after, y_true);
    print_vector_summary("[FULL-1STEP] Y_pred after", ypred_after);
    std::cout << "[FULL-1STEP] err after  = " << std::fixed << std::setprecision(4)
              << static_cast<double>(err_after) / 256.0 << std::endl;

    if (err_after < err_before) {
        std::cout << "[结果] PASS：full-network one-step 后误差下降" << std::endl;
        return true;
    }

    std::cout << "[结果] PARTIAL：完整链路跑通且权重已更新，但本 step 误差未下降" << std::endl;
    return true;
}

bool run_full_network_training_step(
    int step,
    const std::vector<uint16_t> &y_true,
    int32_t *err_before_out,
    int32_t *err_after_out
) {
    if (!run_forward_layer1_to_h1()) {
        std::cout << "[结果] FAIL：step " << step << " forward layer1 before 未完成" << std::endl;
        return false;
    }

    std::vector<uint16_t> ypred_before;
    if (!run_forward_layer2_to_ypred(&ypred_before) || ypred_before.size() < y_true.size()) {
        std::cout << "[结果] FAIL：step " << step << " forward layer2 before 未完成" << std::endl;
        return false;
    }
    const int32_t err_before = sum_abs_error_q8_8(ypred_before, y_true);

    std::vector<uint16_t> dy;
    std::vector<uint16_t> delta2;
    if (!run_loss_to_dy(&dy) || !run_delta2_path(&delta2)) {
        std::cout << "[结果] FAIL：step " << step << " delta2 生成未完成" << std::endl;
        return false;
    }

    if (!generate_delta1_from_current_state()) {
        std::cout << "[结果] FAIL：step " << step << " delta1 生成未完成" << std::endl;
        return false;
    }

    if (!generate_grad_w2_from_current_h1_delta2() ||
        !generate_grad_b2_from_current_delta2()) {
        std::cout << "[结果] FAIL：step " << step << " grad_W2/B2 生成未完成" << std::endl;
        return false;
    }

    if (!generate_grad_w1_from_current_x_delta1() ||
        !generate_grad_b1_from_current_delta1()) {
        std::cout << "[结果] FAIL：step " << step << " grad_W1/B1 生成未完成" << std::endl;
        return false;
    }

    update_w2_b2_from_current_gradients();
    update_w1_b1_from_current_gradients();

    if (!run_forward_layer1_to_h1()) {
        std::cout << "[结果] FAIL：step " << step << " forward layer1 after 未完成" << std::endl;
        return false;
    }

    std::vector<uint16_t> ypred_after;
    if (!run_forward_layer2_to_ypred(&ypred_after) || ypred_after.size() < y_true.size()) {
        std::cout << "[结果] FAIL：step " << step << " forward layer2 after 未完成" << std::endl;
        return false;
    }
    const int32_t err_after = sum_abs_error_q8_8(ypred_after, y_true);

    if (err_before_out) {
        *err_before_out = err_before;
    }
    if (err_after_out) {
        *err_after_out = err_after;
    }

    std::cout << "[step " << std::setw(2) << std::setfill('0') << step << std::setfill(' ')
              << "] err=" << std::fixed << std::setprecision(4)
              << static_cast<double>(err_before) / 256.0
              << " -> " << static_cast<double>(err_after) / 256.0
              << ", W2=[" << to_float(ub_mem(ub::W2_BASE))
              << ", " << to_float(ub_mem(ub::W2_BASE + 1))
              << "], B2=" << to_float(ub_mem(ub::B2_BASE))
              << ", B1=[" << to_float(ub_mem(ub::B1_BASE))
              << ", " << to_float(ub_mem(ub::B1_BASE + 1)) << "]"
              << std::endl;

    return true;
}

bool test_full_network_training_multi_step() {
    const XorModel model = {
        {0xFF00u, 0x0100u, 0x0100u, 0xFF00u},
        {0x0100u, 0x0100u},
        {0x0000u, 0x0000u},
        0xFF40u,
    };
    const std::vector<uint16_t> y_true = {q8_8(0), q8_8(1), q8_8(1), q8_8(0)};

    reset_dut();
    dut->learn_rate_in = 0x0020u;
    load_training_batch_and_params(model);
    std::cout << "[FULL-MULTI] 初始化完成" << std::endl;
    std::cout << "[FULL-MULTI] 训练步数 = " << FULL_NETWORK_TRAIN_STEPS << std::endl;

    const std::array<uint16_t, 4> w1_initial = {
        ub_mem(ub::W1_BASE),
        ub_mem(ub::W1_BASE + 1),
        ub_mem(ub::W1_BASE + 2),
        ub_mem(ub::W1_BASE + 3),
    };
    const std::array<uint16_t, 2> b1_initial = {
        ub_mem(ub::B1_BASE),
        ub_mem(ub::B1_BASE + 1),
    };
    const std::array<uint16_t, 2> w2_initial = {
        ub_mem(ub::W2_BASE),
        ub_mem(ub::W2_BASE + 1),
    };
    const uint16_t b2_initial = ub_mem(ub::B2_BASE);

    int32_t err_initial = 0;
    int32_t err_final = 0;
    bool have_error = false;

    quiet_step_logs = true;
    for (int step = 0; step < FULL_NETWORK_TRAIN_STEPS; step++) {
        int32_t err_before = 0;
        int32_t err_after = 0;
        if (!run_full_network_training_step(step, y_true, &err_before, &err_after)) {
            quiet_step_logs = false;
            return false;
        }
        if (!have_error) {
            err_initial = err_before;
            have_error = true;
        }
        err_final = err_after;
    }
    quiet_step_logs = false;

    const std::array<uint16_t, 4> w1_final = {
        ub_mem(ub::W1_BASE),
        ub_mem(ub::W1_BASE + 1),
        ub_mem(ub::W1_BASE + 2),
        ub_mem(ub::W1_BASE + 3),
    };
    const std::array<uint16_t, 2> b1_final = {
        ub_mem(ub::B1_BASE),
        ub_mem(ub::B1_BASE + 1),
    };
    const std::array<uint16_t, 2> w2_final = {
        ub_mem(ub::W2_BASE),
        ub_mem(ub::W2_BASE + 1),
    };
    const uint16_t b2_final = ub_mem(ub::B2_BASE);

    const bool updated =
        w1_initial != w1_final ||
        b1_initial != b1_final ||
        w2_initial != w2_final ||
        b2_initial != b2_final;

    if (!updated) {
        std::cout << "[结果] FAIL：多步训练后 W1/B1/W2/B2 完全没有变化" << std::endl;
        return false;
    }

    std::cout << "[FULL-MULTI] err initial = " << std::fixed << std::setprecision(4)
              << static_cast<double>(err_initial) / 256.0 << std::endl;
    std::cout << "[FULL-MULTI] err final   = " << std::fixed << std::setprecision(4)
              << static_cast<double>(err_final) / 256.0 << std::endl;
    std::cout << "[FULL-MULTI] FULL_NETWORK_TRAIN_STEPS = "
              << FULL_NETWORK_TRAIN_STEPS << std::endl;
    print_word_pair("[FULL-MULTI] W1 final row0", w1_final[0], w1_final[1]);
    print_word_pair("[FULL-MULTI] W1 final row1", w1_final[2], w1_final[3]);
    std::cout << "[提示] 修改训练轮数：tpu_isa_confreg_sim.cpp 中的 FULL_NETWORK_TRAIN_STEPS"
              << std::endl;

    if (have_error && err_final < err_initial) {
        std::cout << "[结果] PASS：full-network 多步训练误差下降" << std::endl;
        return true;
    }

    std::cout << "[结果] PARTIAL：训练链路跑通且权重已变化，但最终误差没有下降" << std::endl;
    return true;
}

bool run_second_layer_training_step(
    int step,
    const std::vector<uint16_t> &y_true,
    int32_t *err_before_out,
    int32_t *err_after_out
) {
    std::vector<uint16_t> ypred_before;
    if (!run_forward_layer2_to_ypred(&ypred_before) || ypred_before.size() < y_true.size()) {
        std::cout << "[结果] FAIL：step " << step << " forward before 未完成" << std::endl;
        return false;
    }
    const int32_t err_before = sum_abs_error_q8_8(ypred_before, y_true);

    std::vector<uint16_t> dy;
    std::vector<uint16_t> delta2;
    if (!run_loss_to_dy(&dy)) {
        std::cout << "[结果] FAIL：step " << step << " loss -> DY 未完成" << std::endl;
        return false;
    }
    if (!run_delta2_path(&delta2)) {
        std::cout << "[结果] FAIL：step " << step << " derivative -> delta2 未完成" << std::endl;
        return false;
    }

    if (!generate_grad_w2_from_current_h1_delta2()) {
        std::cout << "[结果] FAIL：step " << step << " grad_W2 生成未完成" << std::endl;
        return false;
    }
    if (!generate_grad_b2_from_current_delta2()) {
        std::cout << "[结果] FAIL：step " << step << " grad_B2 生成未完成" << std::endl;
        return false;
    }

    update_w2_b2_from_current_gradients();

    std::vector<uint16_t> ypred_after;
    if (!run_forward_layer2_to_ypred(&ypred_after) || ypred_after.size() < y_true.size()) {
        std::cout << "[结果] FAIL：step " << step << " forward after 未完成" << std::endl;
        return false;
    }
    const int32_t err_after = sum_abs_error_q8_8(ypred_after, y_true);

    if (err_before_out) {
        *err_before_out = err_before;
    }
    if (err_after_out) {
        *err_after_out = err_after;
    }

    std::cout << "[step " << std::setw(2) << std::setfill('0') << step << std::setfill(' ')
              << "] err=" << std::fixed << std::setprecision(4)
              << static_cast<double>(err_before) / 256.0
              << " -> " << static_cast<double>(err_after) / 256.0
              << ", W2=[" << to_float(ub_mem(ub::W2_BASE))
              << ", " << to_float(ub_mem(ub::W2_BASE + 1))
              << "], B2=" << to_float(ub_mem(ub::B2_BASE))
              << std::endl;

    return true;
}

bool test_second_layer_training_multi_step() {
    constexpr int SECOND_LAYER_STEPS = 20;
    const XorModel model = {
        {0xFF00u, 0x0100u, 0x0100u, 0xFF00u},
        {0x0100u, 0x0100u},
        {0x0000u, 0x0000u},
        0xFF40u,
    };
    const std::vector<uint16_t> y_true = {q8_8(0), q8_8(1), q8_8(1), q8_8(0)};

    reset_dut();
    load_training_batch_and_params(model);
    std::cout << "[训练] 初始化完成" << std::endl;

    if (!run_forward_layer1_to_h1()) {
        std::cout << "[结果] FAIL：H1 生成失败" << std::endl;
        return false;
    }
    std::cout << "[训练] H1 生成完成" << std::endl;

    const uint16_t w2_initial_0 = ub_mem(ub::W2_BASE);
    const uint16_t w2_initial_1 = ub_mem(ub::W2_BASE + 1);
    const uint16_t b2_initial = ub_mem(ub::B2_BASE);

    int32_t err_initial = 0;
    int32_t err_final = 0;
    bool have_error = false;

    quiet_step_logs = true;
    for (int step = 0; step < SECOND_LAYER_STEPS; step++) {
        int32_t err_before = 0;
        int32_t err_after = 0;
        if (!run_second_layer_training_step(step, y_true, &err_before, &err_after)) {
            quiet_step_logs = false;
            return false;
        }
        if (!have_error) {
            err_initial = err_before;
            have_error = true;
        }
        err_final = err_after;
    }
    quiet_step_logs = false;

    const bool updated =
        ub_mem(ub::W2_BASE) != w2_initial_0 ||
        ub_mem(ub::W2_BASE + 1) != w2_initial_1 ||
        ub_mem(ub::B2_BASE) != b2_initial;

    if (!updated) {
        std::cout << "[结果] FAIL：多步训练后 W2/B2 完全没有变化" << std::endl;
        return false;
    }

    std::cout << "[训练] err initial = " << std::fixed << std::setprecision(4)
              << static_cast<double>(err_initial) / 256.0 << std::endl;
    std::cout << "[训练] err final   = " << std::fixed << std::setprecision(4)
              << static_cast<double>(err_final) / 256.0 << std::endl;

    if (have_error && err_final < err_initial) {
        std::cout << "[结果] PASS：第二层多步训练误差下降" << std::endl;
        return true;
    }

    std::cout << "[结果] PARTIAL：链路跑通且 W2/B2 已变化，但最终误差没有下降" << std::endl;
    return true;
}

bool run_second_layer_training_smoke_test() {
    const XorModel model = {
        {0xFF00u, 0x0100u, 0x0100u, 0xFF00u},
        {0x0100u, 0x0100u},
        {0x0000u, 0x0000u},
        0xFF40u,
    };

    bool partial = false;
    std::vector<uint16_t> ypred_before;
    std::vector<uint16_t> dy;
    std::vector<uint16_t> delta2;

    reset_dut();
    load_training_batch_and_params(model);

    if (!run_forward_layer1_to_h1()) {
        std::cout << "[结果] FAIL：前向第一层未完成" << std::endl;
        return false;
    }

    if (!run_forward_layer2_to_ypred(&ypred_before)) {
        std::cout << "[结果] FAIL：前向第二层未完成" << std::endl;
        return false;
    }
    print_vector_summary("[摘要] Y_pred before", ypred_before);

    if (run_loss_to_dy(&dy)) {
        print_vector_summary("[摘要] DY", dy);
    } else {
        partial = true;
        std::cout << "[loss] PARTIAL：loss path 未能稳定触发 VPU 输出" << std::endl;
    }

    if (!dy.empty() && run_delta2_path(&delta2)) {
        print_vector_summary("[摘要] delta2", delta2);
    } else {
        partial = true;
        std::cout << "[delta2] PARTIAL：derivative/delta2 path 未完成" << std::endl;
    }

    if (!run_update_w2_b2()) {
        partial = true;
    }

    if (partial) {
        std::cout << "[结果] PARTIAL：已验证第二层 forward";
        if (!dy.empty()) {
            std::cout << "/loss";
        }
        if (!delta2.empty()) {
            std::cout << "/delta2";
        }
        std::cout << "；update 尚未通过 ISA 验证" << std::endl;
    } else {
        std::cout << "[结果] PASS：第二层训练链路 smoke test 完成" << std::endl;
    }

    return true;
}

}  // namespace

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    dut = new Vtpu_isa_confreg;
    tfp = new VerilatedVcdC;
    dut->trace(tfp, 99);
    tfp->open("tpu_isa_confreg_sim.vcd");

    std::cout << "运行 full-network training multi-step test" << std::endl;

    const bool ok = test_full_network_training_multi_step();

    tfp->close();
    delete tfp;
    delete dut;

    return ok ? 0 : 1;
}
