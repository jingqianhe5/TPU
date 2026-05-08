#include <iostream>
#include <iomanip>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vsystolic.h"

vluint64_t main_time = 0; // 全局仿真时间
Vsystolic* dut;           // 你的阵列模块
VerilatedVcdC* tfp;       // 波形指针
int cycle_cnt = 0;        // 时钟周期计数器

static constexpr int FXP_SHIFT = 8;
static constexpr int FXP_ONE   = 1 << FXP_SHIFT;

void tick();

int int_to_fxp(int value) {
    return value * FXP_ONE;
}

int fxp_to_int(int value) {
    return value >> FXP_SHIFT;
}

void print_status(const char* tag) {
    std::cout << std::setw(6) << cycle_cnt
              << " | " << std::setw(14) << tag
              << " | " << std::setw(2) << fxp_to_int(dut->x_11)
              << " | " << std::setw(2) << fxp_to_int(dut->x_21)
              << " | " << std::setw(2) << static_cast<int>(dut->switch_in)
              << " | " << std::setw(2) << static_cast<int>(dut->z_valid_21)
              << " | " << std::setw(2) << static_cast<int>(dut->z_valid_22)
              << " | " << std::setw(3) << fxp_to_int(dut->z_21)
              << " | " << std::setw(3) << fxp_to_int(dut->z_22)
              << std::endl;
}

void clear_inputs() {
    dut->x_11 = 0;
    dut->x_21 = 0;
    dut->w_11 = 0;
    dut->w_12 = 0;
    dut->x_valid_11 = 0;
    dut->x_valid_21 = 0;
    dut->weight_valid_col_1 = 0;
    dut->weight_valid_col_2 = 0;
    dut->switch_in = 0;
}

void load_shadow_weights(int w11, int w12, int w21, int w22, const char* tag) {
    std::cout << "\n[Load] " << tag << " -> shadow buffer" << std::endl;

    dut->w_11 = int_to_fxp(w21);
    dut->w_12 = int_to_fxp(w22);
    dut->weight_valid_col_1 = 1;
    dut->weight_valid_col_2 = 1;
    tick();
    print_status("load row2");

    dut->w_11 = int_to_fxp(w11);
    dut->w_12 = int_to_fxp(w12);
    tick();
    print_status("load row1");

    dut->w_11 = 0;
    dut->w_12 = 0;
    dut->weight_valid_col_1 = 0;
    dut->weight_valid_col_2 = 0;
}

void switch_weights(const char* tag) {
    std::cout << "\n[Switch] " << tag << std::endl;

    dut->switch_in = 1;
    tick();
    print_status("switch=1");

    dut->switch_in = 0;
    tick();
    print_status("switch=0");
}

// 封装一个时钟翻转函数
void tick() {
    dut->clk = 1;
    dut->eval();
    tfp->dump(main_time++);
    
    dut->clk = 0;
    dut->eval();
    tfp->dump(main_time++);
    
    cycle_cnt++;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);
    
    dut = new Vsystolic;
    tfp = new VerilatedVcdC;
    dut->trace(tfp, 99);
    tfp->open("systolic.vcd");

    // ==========================================
    // 阶段 0: 复位与初始化
    // ==========================================
    dut->rst_n = 0;
    dut->clk = 0;
    dut->col_num = 2; // 开启 2x2
    dut->col_num_valid = 1;
    dut->x_11 = 0; dut->x_21 = 0;
    dut->w_11 = 0; dut->w_12 = 0;
    dut->x_valid_11 = 0; dut->x_valid_21 = 0;
    dut->weight_valid_col_1 = 0; dut->weight_valid_col_2 = 0;
    dut->switch_in = 0;

    tick(); tick(); 
    dut->rst_n = 1; // 释放复位
    tick();

    std::cout << "\n[System] 脉动阵列复位完成，开启 2x2 模式。" << std::endl;
    std::cout << "[Info] 第一次计算使用 W1 = [[1,2],[3,4]]，同时在 shadow 里预加载 W2 = [[2,1],[0,1]]" << std::endl;
    std::cout << "[Info] 两次计算都使用 X = [[1,2],[3,4]]" << std::endl;
    std::cout << "[Info] 期望结果: X*W1 = [[7,10],[15,22]], X*W2 = [[2,3],[6,7]]" << std::endl;
    std::cout << "--------------------------------------------------------------------" << std::endl;
    std::cout << " Cycle |          Tag | x11 | x21 | sw | v1 | v2 | z21 | z22" << std::endl;
    std::cout << "--------------------------------------------------------------------" << std::endl;

    // 先把 W1 装进 shadow 并切到 active
    load_shadow_weights(1, 2, 3, 4, "W1 = [[1,2],[3,4]]");
    switch_weights("activate W1");

    std::cout << "\n[Run] Multiply-1: 使用 active W1，同时把 W2 预加载到 shadow" << std::endl;

    // Round 1, cycle 1: 输入 X(1,1)，同时把 W2 第二行装入 shadow
    dut->x_11 = int_to_fxp(1);
    dut->x_valid_11 = 1;
    dut->x_21 = 0;
    dut->x_valid_21 = 0;
    dut->w_11 = int_to_fxp(0);
    dut->w_12 = int_to_fxp(1);
    dut->weight_valid_col_1 = 1;
    dut->weight_valid_col_2 = 1;
    tick();
    print_status("mul1 + W2 row2");

    // Round 1, cycle 2: 输入 X(2,1)/X(1,2)，同时把 W2 第一行装入 shadow
    dut->x_11 = int_to_fxp(3);
    dut->x_21 = int_to_fxp(2);
    dut->x_valid_21 = 1;
    dut->w_11 = int_to_fxp(2);
    dut->w_12 = int_to_fxp(1);
    tick();
    print_status("mul1 + W2 row1");

    // Round 1, cycle 3: 输入最后一个元素，停止写 shadow
    dut->x_11 = 0;
    dut->x_valid_11 = 0;
    dut->x_21 = int_to_fxp(4);
    dut->w_11 = 0;
    dut->w_12 = 0;
    dut->weight_valid_col_1 = 0;
    dut->weight_valid_col_2 = 0;
    tick();
    print_status("mul1 drain-1");

    // Round 1, cycle 4: 最后一个结果流出的同时，立即触发 switch
    dut->x_21 = 0;
    dut->x_valid_21 = 0;
    dut->switch_in = 1;
    tick();
    print_status("mul1 done+sw");

    // 立刻撤下 switch 输入，同时马上开始第二轮输入。
    // pe11 已经在上一拍切到 W2，后级 PE 会在数据到达前完成 switch 传播。
    dut->switch_in = 0;
    dut->x_11 = int_to_fxp(1);
    dut->x_valid_11 = 1;
    dut->x_21 = 0;
    dut->x_valid_21 = 0;
    tick();
    print_status("sw+mul2 feed1");

    std::cout << "\n[Run] Multiply-2: 使用新的 active W2" << std::endl;

    // Round 2, cycle 2
    dut->x_11 = int_to_fxp(3);
    dut->x_21 = int_to_fxp(2);
    dut->x_valid_21 = 1;
    tick();
    print_status("mul2 feed-2");

    // Round 2, cycle 3
    dut->x_11 = 0;
    dut->x_valid_11 = 0;
    dut->x_21 = int_to_fxp(4);
    tick();
    print_status("mul2 drain-1");

    // Round 2, cycle 4
    dut->x_21 = 0;
    dut->x_valid_21 = 0;
    tick();
    print_status("mul2 drain-2");

    // 再空跑一些拍，方便观察第二轮结果
    clear_inputs();
    for (int i = 0; i < 8; i++) {
        tick();
        print_status("mul2 idle");
    }

    std::cout << "--------------------------------------------------------------------" << std::endl;
    std::cout << "\n[Success] 两轮矩阵计算已完成，可以据此检查双缓冲切换前后的结果差异。" << std::endl;

    // 清理
    tfp->close();
    delete dut;
    delete tfp;
    return 0;
}
