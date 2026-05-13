#include <array>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include <verilated.h>
#include <verilated_vcd_c.h>

#include "Vtpu_isa_confreg.h"

namespace {

constexpr uint32_t OP_NOP = 0x0u;
constexpr uint32_t OP_LOAD = 0x1u;
constexpr uint32_t OP_UB_READ = 0x3u;
constexpr uint32_t OP_SWITCH = 0x4u;

constexpr uint16_t LEARN_RATE = 0x00C0u;
constexpr uint16_t VPU_FACTOR = 0x0003u;
constexpr uint16_t TWO_DIV_N = 0x0080u;

vluint64_t main_time = 0;
int cycle_count = 0;

Vtpu_isa_confreg *dut = nullptr;
VerilatedVcdC *tfp = nullptr;

uint16_t q8_8(int integer_value) {
    return static_cast<uint16_t>(integer_value << 8);
}

int16_t s16(uint16_t value) {
    return static_cast<int16_t>(value);
}

double to_float(uint16_t value) {
    return static_cast<double>(s16(value)) / 256.0;
}

uint32_t ins_nop() {
    return OP_NOP << 28;
}

uint32_t ins_load(uint16_t data) {
    return (OP_LOAD << 28) | data;
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

void issue(uint32_t ins, const std::string &name) {
    dut->ins = ins;
    dut->ins_valid = 1;
    tick();

    drive_idle();
    tick();

    std::cout << "  cycle " << std::setw(4) << cycle_count
              << " issue " << std::left << std::setw(12) << name << std::right
              << " ins=0x" << std::hex << std::setw(8) << std::setfill('0') << ins
              << std::setfill(' ') << std::dec << std::endl;
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

std::vector<uint16_t> xor_memory_image(int a, int b) {
    const uint16_t x0 = q8_8(a);
    const uint16_t x1 = q8_8(b);

    return {
        // Input matrix X, addresses 0..11. This is the flattened memory image
        // produced by de1_soc_tiny_tpu_xor_top.v ST_LOAD.
        x0, x1, x0, x1, x0, x1, x0, x1,
        0x0000u, 0x0000u, 0x0000u, 0x0000u,

        // W1 and B1, addresses 12..17.
        0xFF00u, 0x0100u, 0x0100u, 0xFF00u,
        0x0000u, 0x0000u,

        // W2 and B2, addresses 18..20.
        0x0100u, 0x0100u, 0xFF40u,
    };
}

void load_memory_with_isa(int a, int b) {
    const auto image = xor_memory_image(a, b);
    std::cout << "  Loading " << image.size() << " words through OP_LOAD instructions" << std::endl;

    for (std::size_t addr = 0; addr < image.size(); addr++) {
        issue(ins_load(image[addr]), "LOAD");
        std::cout << "    mem[" << std::setw(2) << addr << "] <= 0x"
                  << std::hex << std::setw(4) << std::setfill('0') << image[addr]
                  << std::setfill(' ') << std::dec
                  << " (" << std::fixed << std::setprecision(4) << to_float(image[addr]) << ")"
                  << std::endl;
    }
}

bool weight_valid() {
    return dut->ub_rd_weight_valid_out_0 || dut->ub_rd_weight_valid_out_1;
}

bool vpu_valid() {
    return dut->vpu_data_valid_out_1 || dut->vpu_data_valid_out_2;
}

bool wait_for_valid_burst(const std::string &name, bool (*valid_fn)(), int max_cycles) {
    bool seen_valid = false;
    for (int i = 0; i < max_cycles; i++) {
        tick();
        if (valid_fn()) {
            seen_valid = true;
            std::cout << "  cycle " << std::setw(4) << cycle_count
                      << " " << name << " valid"
                      << " sys=(" << static_cast<int>(dut->sys_valid_out_21)
                      << "," << static_cast<int>(dut->sys_valid_out_22) << ")"
                      << " vpu=(" << static_cast<int>(dut->vpu_data_valid_out_1)
                      << "," << static_cast<int>(dut->vpu_data_valid_out_2) << ")"
                      << " vpu_out=(0x" << std::hex << std::setw(4) << std::setfill('0')
                      << static_cast<int>(dut->vpu_data_out_1)
                      << ",0x" << std::setw(4) << static_cast<int>(dut->vpu_data_out_2)
                      << std::setfill(' ') << std::dec << ")"
                      << std::endl;
        } else if (seen_valid) {
            return true;
        }
    }

    std::cout << "  timeout waiting for " << name << " valid burst" << std::endl;
    return false;
}

bool wait_for_final_vpu(uint16_t &final_raw, int max_cycles) {
    bool seen_valid = false;
    bool captured = false;

    for (int i = 0; i < max_cycles; i++) {
        tick();
        if (vpu_valid()) {
            seen_valid = true;

            if (!captured && dut->vpu_data_valid_out_1) {
                final_raw = static_cast<uint16_t>(dut->vpu_data_out_1);
                captured = true;
            }

            std::cout << "  cycle " << std::setw(4) << cycle_count
                      << " final VPU valid"
                      << " out1=0x" << std::hex << std::setw(4) << std::setfill('0')
                      << static_cast<int>(dut->vpu_data_out_1)
                      << " out2=0x" << std::setw(4) << static_cast<int>(dut->vpu_data_out_2)
                      << std::setfill(' ') << std::dec
                      << " captured=" << captured
                      << std::endl;
        } else if (seen_valid) {
            return captured;
        }
    }

    std::cout << "  timeout waiting for final VPU result" << std::endl;
    return false;
}

bool wait_for_first_layer_and_prefetch(int max_cycles) {
    bool seen_vpu = false;
    bool done_vpu = false;
    bool seen_weight = false;
    bool done_weight = false;
    bool overlapped = false;

    for (int i = 0; i < max_cycles; i++) {
        tick();

        const bool weight_now = weight_valid();
        const bool vpu_now = vpu_valid();

        if (weight_now) {
            seen_weight = true;
        } else if (seen_weight) {
            done_weight = true;
        }

        if (vpu_now) {
            seen_vpu = true;
        } else if (seen_vpu) {
            done_vpu = true;
        }

        overlapped |= weight_now && vpu_now;

        if (weight_now || vpu_now) {
            std::cout << "  cycle " << std::setw(4) << cycle_count
                      << " overlap wait"
                      << " w_valid=(" << static_cast<int>(dut->ub_rd_weight_valid_out_0)
                      << "," << static_cast<int>(dut->ub_rd_weight_valid_out_1) << ")"
                      << " vpu_valid=(" << static_cast<int>(dut->vpu_data_valid_out_1)
                      << "," << static_cast<int>(dut->vpu_data_valid_out_2) << ")"
                      << " vpu_out=(0x" << std::hex << std::setw(4) << std::setfill('0')
                      << static_cast<int>(dut->vpu_data_out_1)
                      << ",0x" << std::setw(4) << static_cast<int>(dut->vpu_data_out_2)
                      << std::setfill(' ') << std::dec << ")"
                      << std::endl;
        }

        if (done_vpu && done_weight) {
            std::cout << "  W2 prefetch overlapped first-layer compute: "
                      << (overlapped ? "yes" : "no") << std::endl;
            return true;
        }
    }

    std::cout << "  timeout waiting for first-layer VPU and W2 prefetch" << std::endl;
    return false;
}

bool run_xor_case(int a, int b) {
    const int expected = a ^ b;
    uint16_t final_raw = 0;

    std::cout << "\n[Case] XOR(" << a << ", " << b << "), expected=" << expected << std::endl;
    reset_dut();
    load_memory_with_isa(a, b);

    issue(ins_ub_read(1, 12, 2, 2, true, 0x0), "READ_W1");
    if (!wait_for_valid_burst("W1", weight_valid, 80)) {
        return false;
    }
    tick_n(2);
    issue(ins_switch(), "SWITCH_1");

    issue(ins_ub_read(0, 0, 4, 2, false, 0xC), "READ_X");
    issue(ins_ub_read(2, 16, 4, 2, false, 0xC), "READ_B1");
    issue(ins_ub_read(1, 18, 1, 2, true, 0xC), "READ_W2");
    if (!wait_for_first_layer_and_prefetch(160)) {
        return false;
    }
    tick_n(2);
    issue(ins_switch(), "SWITCH_2");

    issue(ins_ub_read(0, 21, 4, 2, false, 0xC), "READ_H1");
    issue(ins_ub_read(2, 20, 4, 1, false, 0xC), "READ_B2");
    if (!wait_for_final_vpu(final_raw, 160)) {
        return false;
    }

    const bool got = (s16(final_raw) > 0);
    const bool pass = got == static_cast<bool>(expected);

    std::cout << "  final out1=0x" << std::hex << std::setw(4) << std::setfill('0')
              << final_raw << std::setfill(' ') << std::dec
              << " signed=" << s16(final_raw)
              << " float=" << std::fixed << std::setprecision(4) << to_float(final_raw)
              << " pred=" << got
              << " expected=" << expected
              << " => " << (pass ? "PASS" : "FAIL") << std::endl;

    return pass;
}

}  // namespace

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    dut = new Vtpu_isa_confreg;
    tfp = new VerilatedVcdC;
    dut->trace(tfp, 99);
    tfp->open("tpu_isa_confreg_sim.vcd");

    std::cout << "Running tpu_isa_confreg ISA-driven XOR simulation" << std::endl;
    std::cout << "All TPU actions below are driven by 32-bit instructions into decode.v." << std::endl;

    bool all_pass = true;
    const std::array<std::array<int, 2>, 4> cases = {{
        {{0, 0}},
        {{1, 0}},
        {{0, 1}},
        {{1, 1}},
    }};

    for (const auto &test_case : cases) {
        all_pass &= run_xor_case(test_case[0], test_case[1]);
        tick_n(8);
    }

    std::cout << "\nSummary: " << (all_pass ? "PASS" : "FAIL") << std::endl;

    tfp->close();
    delete tfp;
    delete dut;

    return all_pass ? 0 : 1;
}
