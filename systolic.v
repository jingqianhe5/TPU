module systolic #(
    parameter WIDTH = 16,
    parameter F_BITS = 8
)
(
    input   clk,
    input   rst_n,
    //输入矩阵 输入的行数量
    input   [WIDTH-1:0]  x_11,
    input   [WIDTH-1:0]  x_21,
    input   x_valid_11,
    input   x_valid_21,

    output  [WIDTH-1:0]  z_21,
    output  [WIDTH-1:0]  z_22,
    output  z_valid_21,
    output  z_valid_22,
    //权重举证 输入的列数量
    input   [WIDTH-1:0]  w_11,
    input   [WIDTH-1:0]  w_12,
    input   weight_valid_col_1,
    input   weight_valid_col_2,
    input   switch_in,//双缓冲切换信号
    //脉动矩阵激活的列数
    /* verilator lint_off UNUSEDSIGNAL */
    /* verilator lint_off PINCONNECTEMPTY */
    input   [15:0]  col_num,
    input   col_num_valid
);
    reg [1:0] pe_enabled;
    always @(posedge clk or negedge rst_n) begin
        if(!rst_n) begin
            pe_enabled <= 2'b11;  // 两列全开
        end else begin
            if(col_num_valid) begin
                case (col_num[1:0])
                    2'd1:    pe_enabled <= 2'b01;
                    2'd2:    pe_enabled <= 2'b11;
                    default: pe_enabled <= 2'b00;
                endcase
            end
        end
    end


    //实例化PE
    //----------------
    //PE(1,1)
    //----------------
    wire    [WIDTH-1:0]     weight_out_11;//PE(1,1)的权重输出
    wire    [WIDTH-1:0]     psum_out_11;//PE(1,1)的结果输出
    wire                    switch_out_11;//PE(1,1)的双缓冲切换输出
    wire    [WIDTH-1:0]     input_out_11;//PE(1,1)的输入矩阵输出
    wire                    input_out_valid_11;//PE(1,1)的输入矩阵有效信号输出
    pe #(
        .WIDTH(WIDTH),
        .F_BITS(F_BITS)
    ) pe_11 (
        .clk            (clk),
        .rst_n          (rst_n),
        .input_in       (x_11),
        .input_out      (input_out_11),
        .input_in_valid (x_valid_11),
        .input_out_valid(input_out_valid_11),
        .weight_in      (w_11),
        .weight_out     (weight_out_11), 
        .weight_valid   (weight_valid_col_1),
        .psum_in        ({WIDTH{1'b0}}),
        .psum_out       (psum_out_11),
        .switch_in      (switch_in),
        .switch_out     (switch_out_11),
        .pe_enabled     (pe_enabled[0]),
        .overflow_out   ()//暂时不接
    );

    //----------------
    //PE(1,2)
    //----------------
    wire    [WIDTH-1:0]     weight_out_12;//PE(1,2)的权重输出
    wire    [WIDTH-1:0]     psum_out_12;//PE(1,2)的结果输出
    wire                    switch_out_12;//PE(1,2)的双缓冲切换输出
    wire    [WIDTH-1:0]     input_out_12;//PE(1,2)的输入矩阵输出
    wire                    input_out_valid_12;//PE(1,2)的输入矩阵有效信号输出
    pe #(
        .WIDTH(WIDTH),
        .F_BITS(F_BITS)
    ) pe_12 (
        .clk            (clk),
        .rst_n          (rst_n),
        .input_in       (input_out_11),
        .input_out      (input_out_12),
        .input_in_valid (input_out_valid_11),
        .input_out_valid(input_out_valid_12),
        .weight_in      (w_12),
        .weight_out     (weight_out_12), 
        .weight_valid   (weight_valid_col_2),
        .psum_in        ({WIDTH{1'b0}}),
        .psum_out       (psum_out_12),
        .switch_in      (switch_out_11),
        .switch_out     (switch_out_12),
        .pe_enabled     (pe_enabled[1]),
        .overflow_out   ()//暂时不接
    );

    //----------------
    //PE(2,1)
    //----------------
    wire    [WIDTH-1:0]     weight_out_21;//PE(2,1)的权重输出
    wire    [WIDTH-1:0]     psum_out_21;//PE(2,1)的结果输出
    wire                    switch_out_21;//PE(2,1)的双缓冲切换输出
    wire    [WIDTH-1:0]     input_out_21;//PE(2,1)的输入矩阵输出
    wire                    input_out_valid_21;//PE(2,1)的输入矩阵有效信号输出
    pe #(
        .WIDTH(WIDTH),
        .F_BITS(F_BITS)
    ) pe_21 (
        .clk            (clk),
        .rst_n          (rst_n),
        .input_in       (x_21),
        .input_out      (input_out_21),
        .input_in_valid (input_out_valid_11),
        .input_out_valid(input_out_valid_21),
        .weight_in      (weight_out_11),
        .weight_out     (weight_out_21), 
        .weight_valid   (weight_valid_col_1),
        .psum_in        (psum_out_11),
        .psum_out       (z_21),
        .switch_in      (switch_out_11),
        .switch_out     (switch_out_21),
        .pe_enabled     (pe_enabled[0]),
        .overflow_out   ()//暂时不接
    );

    //----------------
    //PE(2,2)
    //----------------
    wire    [WIDTH-1:0]     weight_out_22;//PE(2,2)的权重输出
    wire    [WIDTH-1:0]     psum_out_22;//PE(2,2)的结果输出
    wire                    switch_out_22;//PE(2,2)的双缓冲切换输出
    wire    [WIDTH-1:0]     input_out_22;//PE(2,2)的输入矩阵输出
    wire                    input_out_valid_22;//PE(2,2)的输入矩阵有效信号输出
    pe #(
        .WIDTH(WIDTH),
        .F_BITS(F_BITS)
    ) pe_22 (
        .clk            (clk),
        .rst_n          (rst_n),
        .input_in       (input_out_21),
        .input_out      (),//这里不需要在输出
        .input_in_valid (input_out_valid_12),
        .input_out_valid(input_out_valid_22),
        .weight_in      (weight_out_12),
        .weight_out     (weight_out_22), 
        .weight_valid   (weight_valid_col_2),
        .psum_in        (psum_out_12),
        .psum_out       (z_22),
        .switch_in      (switch_out_12),
        .switch_out     (switch_out_22),
        .pe_enabled     (pe_enabled[1]),
        .overflow_out   ()//暂时不接
    );
/* verilator lint_on UNUSEDSIGNAL */
/* verilator lint_on PINCONNECTEMPTY */

    assign z_valid_21 = input_out_valid_21; //结果有效赋值
    assign z_valid_22 = input_out_valid_22; 
endmodule
