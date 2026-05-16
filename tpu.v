module tpu#(
    parameter SYSTOLIC_ARRAY_WIDTH = 2
)
(
    input  clk,
    input  rst_n,
    
    input wire [15:0] ub_wr_host_data_in_0,
    input wire [15:0] ub_wr_host_data_in_1,
    input wire [15:0] ub_wr_host_addr_in_0,
    input wire [15:0] ub_wr_host_addr_in_1,
    input wire ub_wr_host_valid_in_0,
    input wire ub_wr_host_valid_in_1,

    //数据操作信号
    input   ub_wr_addr_start_in,
    input   [15:0] ub_wr_addr_in,//VPU写回UB的起始地址
    input   ub_wr_accumulate_in,//VPU写回UB时是否累加
    input   ub_grad_addr_start_in,
    input   [15:0] ub_grad_addr_in,//gradient_descent读取gradient的起始地址
    input   ub_rd_start_in,
    input   ub_rd_transpose_in,
    input   [8:0] ub_ptr_select_in,//需要读取的数据类型
    input   [15:0] ub_rd_addr_in,//需要读取的数据地址
    input   [15:0] ub_rd_row_size_in,//数据矩阵的行数
    input   [15:0] ub_rd_col_size_in,//数据矩阵的烈数

    //学习率传入
    input   [15:0] learn_rate_in,

    //VPU
    input   [3:0] vpu_mode,//选择信号在VPU的数据通路
    input   switch_in,//双缓冲切换信号
    input   [15:0] vpu_factor_in,//VPU的计算因子
    input   [15:0] two_div_N_in,//   2/N

    //vpu数据输出
    output  [15:0] vpu_data_out_1,
    output  [15:0] vpu_data_out_2,
    output  vpu_data_valid_out_1,
    output  vpu_data_valid_out_2,

        // Outputs - Systolic 运算的结果
    output wire [15:0] sys_data_out_21,
    output wire [15:0] sys_data_out_22,
    output wire sys_valid_out_21,
    output wire sys_valid_out_22,

    //其他数据输出
    output  [15:0] ub_rd_input_data_out_0,
    output  [15:0] ub_rd_input_data_out_1,
    output  ub_rd_input_valid_out_0,
    output  ub_rd_input_valid_out_1,

    output  [15:0] ub_rd_weight_data_out_0,
    output  [15:0] ub_rd_weight_data_out_1,
    output  ub_rd_weight_valid_out_0,
    output  ub_rd_weight_valid_out_1,

    output  [15:0] ub_rd_bias_data_out_0,
    output  [15:0] ub_rd_bias_data_out_1,
    output  [15:0] ub_rd_Y_data_out_0,
    output  [15:0] ub_rd_Y_data_out_1,
    output  [15:0] ub_rd_H_data_out_0,
    output  [15:0] ub_rd_H_data_out_1,

    output  [15:0] ub_rd_col_size_out,
    output  ub_rd_col_size_valid_out

);

    //vpu的写回数据
    wire [15:0] ub_wr_data_in_0;
    wire [15:0] ub_wr_data_in_1;
    wire ub_wr_valid_in_0;
    wire ub_wr_valid_in_1;

    assign ub_wr_data_in_0 = vpu_data_out_1;
    assign ub_wr_data_in_1 = vpu_data_out_2;
    assign ub_wr_valid_in_0 = vpu_data_valid_out_1;
    assign ub_wr_valid_in_1 = vpu_data_valid_out_2;

    wire [15:0] ub_wr_data_in [0:SYSTOLIC_ARRAY_WIDTH-1];
    wire ub_wr_valid_in [0:SYSTOLIC_ARRAY_WIDTH-1];
    wire [15:0] ub_wr_host_data_in [0:SYSTOLIC_ARRAY_WIDTH-1];
    wire [15:0] ub_wr_host_addr_in [0:SYSTOLIC_ARRAY_WIDTH-1];
    wire ub_wr_host_valid_in [0:SYSTOLIC_ARRAY_WIDTH-1];

    assign ub_wr_data_in[0] = ub_wr_data_in_0;
    assign ub_wr_data_in[1] = ub_wr_data_in_1;
    assign ub_wr_valid_in[0] = ub_wr_valid_in_0;
    assign ub_wr_valid_in[1] = ub_wr_valid_in_1;

    assign ub_wr_host_data_in[0] = ub_wr_host_data_in_0;
    assign ub_wr_host_data_in[1] = ub_wr_host_data_in_1;
    assign ub_wr_host_addr_in[0] = ub_wr_host_addr_in_0;
    assign ub_wr_host_addr_in[1] = ub_wr_host_addr_in_1;
    assign ub_wr_host_valid_in[0] = ub_wr_host_valid_in_0;
    assign ub_wr_host_valid_in[1] = ub_wr_host_valid_in_1;

    unified_buffer #(
        .SYSTOLIC_ARRAY_WIDTH(SYSTOLIC_ARRAY_WIDTH)
    ) ub_inst(
        .clk(clk),
        .rst(~rst_n),

        .ub_wr_data_in(ub_wr_data_in),
        .ub_wr_valid_in(ub_wr_valid_in),
        .ub_wr_addr_in(ub_wr_addr_in),
        .ub_wr_addr_start_in(ub_wr_addr_start_in),
        .ub_wr_accumulate_in(ub_wr_accumulate_in),
        .ub_grad_addr_in(ub_grad_addr_in),
        .ub_grad_addr_start_in(ub_grad_addr_start_in),

        // Write ports from host to UB (for loading in parameters)
        .ub_wr_host_data_in(ub_wr_host_data_in),
        .ub_wr_host_addr_in(ub_wr_host_addr_in),
        .ub_wr_host_valid_in(ub_wr_host_valid_in),

        // Read instruction input from instruction memory
        .ub_rd_start_in(ub_rd_start_in),
        .ub_rd_transpose(ub_rd_transpose_in),
        .ub_ptr_select(ub_ptr_select_in),
        .ub_rd_addr_in(ub_rd_addr_in),
        .ub_rd_row_size(ub_rd_row_size_in),
        .ub_rd_col_size(ub_rd_col_size_in),

        // Learning rate input
        .learning_rate_in(learn_rate_in),

        // Read ports from UB to left side of systolic array
        .ub_rd_input_data_out_0(ub_rd_input_data_out_0),
        .ub_rd_input_data_out_1(ub_rd_input_data_out_1),
        .ub_rd_input_valid_out_0(ub_rd_input_valid_out_0),
        .ub_rd_input_valid_out_1(ub_rd_input_valid_out_1),

        // Read ports from UB to top of systolic array
        .ub_rd_weight_data_out_0(ub_rd_weight_data_out_0),
        .ub_rd_weight_data_out_1(ub_rd_weight_data_out_1),
        .ub_rd_weight_valid_out_0(ub_rd_weight_valid_out_0),
        .ub_rd_weight_valid_out_1(ub_rd_weight_valid_out_1),

        // Read ports from UB to bias modules in VPU
        .ub_rd_bias_data_out_0(ub_rd_bias_data_out_0),
        .ub_rd_bias_data_out_1(ub_rd_bias_data_out_1),

        // Read ports from UB to loss modules (Y matrices) in VPU
        .ub_rd_Y_data_out_0(ub_rd_Y_data_out_0),
        .ub_rd_Y_data_out_1(ub_rd_Y_data_out_1),

        // Read ports from UB to activation derivative modules (H matrices) in VPU
        .ub_rd_H_data_out_0(ub_rd_H_data_out_0),
        .ub_rd_H_data_out_1(ub_rd_H_data_out_1),

        //激活的列数
        .ub_rd_col_size_out(ub_rd_col_size_out),
        .ub_rd_col_size_valid_out(ub_rd_col_size_valid_out)
    );

     systolic systolic_inst (
        .clk(clk),
        .rst_n(rst_n),

        // input signals from left side of systolic array
        .x_11(ub_rd_input_data_out_0),
        .x_21(ub_rd_input_data_out_1),
        .x_valid_11(ub_rd_input_valid_out_0),
        .x_valid_21(ub_rd_input_valid_out_1),

        .z_21(sys_data_out_21),
        .z_22(sys_data_out_22),
        .z_valid_21(sys_valid_out_21),
        .z_valid_22(sys_valid_out_22),

        // input signals from top of systolic array
        .w_11(ub_rd_weight_data_out_0),
        .w_12(ub_rd_weight_data_out_1),
        .weight_valid_col_1(ub_rd_weight_valid_out_0),       // accept weight signal propagates only from top to bottom in column 1
        .weight_valid_col_2(ub_rd_weight_valid_out_1),       // accept weight signal propagates only from top to bottom in column 2

        .switch_in(switch_in),          // switch signal copies weight from shadow buffer to active buffer. propagates from top left to bottom right

        .col_num(ub_rd_col_size_out),
        .col_num_valid(ub_rd_col_size_valid_out)
    );

    vpu vpu_inst (
        .clk(clk),
        .rst_n(rst_n),

        .vpu_mode(vpu_mode), // 4-bits to signify which modules to route the inputs to (1 bit for each module)

        // Inputs from systolic array
        .systolic_data_in_1(sys_data_out_21),
        .systolic_data_in_2(sys_data_out_22),
        .sysdata_valid_in_1(sys_valid_out_21),
        .sysdata_valid_in_2(sys_valid_out_22),

        // Inputs from UB
        .bias_scalar_in_1(ub_rd_bias_data_out_0),               // For bias modules
        .bias_scalar_in_2(ub_rd_bias_data_out_1),               // For bias modules
        .leak_factor_in(vpu_factor_in),                 // For leaky relu modules
        .Y_in_1(ub_rd_Y_data_out_0),                                  // For loss modules
        .Y_in_2(ub_rd_Y_data_out_1),                                  // For loss modules
        .H_in_1(ub_rd_H_data_out_0),                                  // For leaky relu derivative modules (WE ONLY NEED THIS PORT FOR EVERY dL/dH after the first node)
        .H_in_2(ub_rd_H_data_out_1),                                  // For leaky relu derivative modules (WE ONLY NEED THIS PORT FOR EVERY dL/dH after the first node)
        .two_div_N_in(two_div_N_in),             // For loss modules
        // Outputs to UB
        .vpu_out_1(vpu_data_out_1),
        .vpu_out_2(vpu_data_out_2),
        .vpu_valid_out_1(vpu_data_valid_out_1),
        .vpu_valid_out_2(vpu_data_valid_out_2)
    ); 
endmodule
