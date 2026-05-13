`timescale 1ns/1ps

module vpu#(
    parameter WIDTH = 16,
    parameter F_BITS = 8
)
(
    input  clk,
    input  rst_n,

    //选择模式
    input  [3:0] vpu_mode,

    //从矩阵运算单元输入数据
    input  signed [WIDTH-1:0] systolic_data_in_1,
    input  signed [WIDTH-1:0] systolic_data_in_2,
    input                     sysdata_valid_in_1,
    input                     sysdata_valid_in_2,

    //从UB来的数据
    input  signed [WIDTH-1:0] bias_scalar_in_1,//输入偏置
    input  signed [WIDTH-1:0] bias_scalar_in_2,
    input  signed [WIDTH-1:0] leak_factor_in,//输入乘法因子
    input  signed [WIDTH-1:0] Y_in_1,
    input  signed [WIDTH-1:0] Y_in_2,
    input  signed [WIDTH-1:0] H_in_1,
    input  signed [WIDTH-1:0] H_in_2,

    input  signed [WIDTH-1:0] two_div_N_in,//缩放因子2/N

    //输出到UB的数据
    output reg signed [WIDTH-1:0] vpu_out_1,
    output reg signed [WIDTH-1:0] vpu_out_2,
    output reg                    vpu_valid_out_1,
    output reg                    vpu_valid_out_2
);
    //bias
    reg signed [WIDTH-1:0] bias_data_in_1;
    reg signed [WIDTH-1:0] bias_data_in_2;
    reg bias_valid_in_1;
    reg bias_valid_in_2;
    reg signed [WIDTH-1:0] bias_data_out_1;
    reg signed [WIDTH-1:0] bias_data_out_2;
    reg bias_valid_out_1;
    reg bias_valid_out_2;

    //bias_to_leaky_relu
    reg signed [WIDTH-1:0] b2lr_data_in_1;
    reg signed [WIDTH-1:0] b2lr_data_in_2;
    reg b2lr_valid_in_1;
    reg b2lr_valid_in_2;

    //lr
    reg signed [WIDTH-1:0] lr_data_in_1;
    reg signed [WIDTH-1:0] lr_data_in_2;
    reg lr_valid_in_1;
    reg lr_valid_in_2;
    reg signed [WIDTH-1:0] lr_data_out_1;
    reg signed [WIDTH-1:0] lr_data_out_2;
    reg lr_valid_out_1;
    reg lr_valid_out_2;

    //lr_to_loss
    reg signed [WIDTH-1:0] lr2loss_data_in_1;
    reg signed [WIDTH-1:0] lr2loss_data_in_2;
    reg lr2loss_valid_in_1;
    reg lr2loss_valid_in_2;

    //loss
    reg signed [WIDTH-1:0] loss_data_in_1;
    reg signed [WIDTH-1:0] loss_data_in_2;
    reg loss_valid_in_1;
    reg loss_valid_in_2;
    reg signed [WIDTH-1:0] loss_data_out_1;
    reg signed [WIDTH-1:0] loss_data_out_2;
    reg loss_valid_out_1;
    reg loss_valid_out_2;

    //loss_to_lrd
    reg signed [WIDTH-1:0] loss2lrd_data_in_1;
    reg signed [WIDTH-1:0] loss2lrd_data_in_2;
    reg loss2lrd_valid_in_1;
    reg loss2lrd_valid_in_2;

    //lrd
    reg signed [WIDTH-1:0] lrd_data_in_1;
    reg signed [WIDTH-1:0] lrd_data_in_2;
    reg lrd_valid_in_1;
    reg lrd_valid_in_2;
    reg signed [WIDTH-1:0] lrd_data_out_1;
    reg signed [WIDTH-1:0] lrd_data_out_2;
    reg lrd_valid_out_1;
    reg lrd_valid_out_2;
    reg signed [WIDTH-1:0] leaky_data_in_1;//输入历史数据
    reg signed [WIDTH-1:0] leaky_data_in_2;

    //temp H
    reg signed [WIDTH-1:0] last_H_data_in_1;
    reg signed [WIDTH-1:0] last_H_data_in_2;
    reg signed [WIDTH-1:0] last_H_data_out_1;
    reg signed [WIDTH-1:0] last_H_data_out_2;

    //fix
    reg signed [WIDTH-1:0] vpu_data_mux_1;
    reg signed [WIDTH-1:0] vpu_data_mux_2;
    reg vpu_valid_mux_1;
    reg vpu_valid_mux_2;

    bias_centre #(
        .WIDTH(WIDTH),
        .F_BITS(F_BITS)
    ) bias_centre (
        .clk(clk),
        .rst_n(rst_n),
        .bias_scalar_in_1(bias_scalar_in_1),
        .bias_scalar_in_2(bias_scalar_in_2),

        .bias_valid_out_1(bias_valid_out_1),
        .bias_valid_out_2(bias_valid_out_2),

        .bias_data_out_1(bias_data_out_1),
        .bias_data_out_2(bias_data_out_2),

        .bias_data_in_1(bias_data_in_1),
        .bias_data_in_2(bias_data_in_2),

        .bias_valid_in_1(bias_valid_in_1),
        .bias_valid_in_2(bias_valid_in_2),

        .overflow_out_1(),
        .overflow_out_2()
    );

    leaky_relu_centre #(
        .WIDTH(WIDTH),
        .F_BITS(F_BITS)
    ) leaky_relu_centre (
        .clk(clk),
        .rst_n(rst_n),

        .leaky_data_in_1(lr_data_in_1),
        .leaky_data_in_2(lr_data_in_2),

        .leaky_valid_in_1(lr_valid_in_1),
        .leaky_valid_in_2(lr_valid_in_2),

        .leaky_factor_in(leak_factor_in),

        .leaky_data_out_1(lr_data_out_1),
        .leaky_data_out_2(lr_data_out_2),

        .leaky_valid_out_1(lr_valid_out_1),
        .leaky_valid_out_2(lr_valid_out_2),

        .leaky_overflow_out_1(),
        .leaky_overflow_out_2()
    );

    loss_centre #(
        .WIDTH(WIDTH),
        .F_BITS(F_BITS)
    ) loss_centre (
        .clk(clk),
        .rst_n(rst_n),

        .H_in_1(loss_data_in_1),
        .H_in_2(loss_data_in_2),
        .Y_in_1(Y_in_1),
        .Y_in_2(Y_in_2),

        .valid_in_1(loss_valid_in_1),
        .valid_in_2(loss_valid_in_2),

        .two_div_N_in(two_div_N_in),//缩放因子

        .gradient_out_1(loss_data_out_1),
        .gradient_out_2(loss_data_out_2),

        .valid_out_1(loss_valid_out_1),
        .valid_out_2(loss_valid_out_2),

        .loss_overflow_out_1(),
        .loss_overflow_out_2()
    );

    leaky_relu_derivative_centre #(
        .WIDTH(WIDTH),
        .F_BITS(F_BITS)
    ) leaky_relu_derivative_centre (
        .clk(clk),
        .rst_n(rst_n),

        .leaky_factor_in(leak_factor_in),

        .leaky_data_in_1(leaky_data_in_1),
        .leaky_data_in_2(leaky_data_in_2),

        .gradient_in_1(lrd_data_in_1),
        .gradient_in_2(lrd_data_in_2),

        .gradient_valid_in_1(lrd_valid_in_1),
        .gradient_valid_in_2(lrd_valid_in_2),

        .gradient_out_1(lrd_data_out_1),
        .gradient_out_2(lrd_data_out_2),

        .gradient_valid_out_1(lrd_valid_out_1),
        .gradient_valid_out_2(lrd_valid_out_2),

        .overflow_out_1(),
        .overflow_out_2()
    );

    //数据的输入选择 决定什么模块工作
    always@ (*)begin
        b2lr_data_in_1 = 0;
        b2lr_data_in_2 = 0;
        b2lr_valid_in_1 = 0;
        b2lr_valid_in_2 = 0;
        lr2loss_data_in_1 = 0;
        lr2loss_data_in_2 = 0;
        lr2loss_valid_in_1 = 0;
        lr2loss_valid_in_2 = 0;
        loss2lrd_data_in_1 = 0;
        loss2lrd_data_in_2 = 0;
        loss2lrd_valid_in_1 = 0;
        loss2lrd_valid_in_2 = 0;
        last_H_data_in_1 = 0;
        last_H_data_in_2 = 0;
        leaky_data_in_1 = 0;
        leaky_data_in_2 = 0;
        if(!rst_n)begin
            vpu_data_mux_1 = 0;
            vpu_data_mux_2 = 0;
            vpu_valid_mux_1 = 0;
            vpu_valid_mux_2 = 0;

            bias_data_in_1 = 0;
            bias_data_in_2 = 0;
            bias_valid_in_1 = 0;
            bias_valid_in_2 = 0;
            lr_data_in_1 = 0;
            lr_data_in_2 = 0;
            lr_valid_in_1 = 0;
            lr_valid_in_2 = 0;
            loss_data_in_1 = 0;
            loss_data_in_2 = 0;
            loss_valid_in_1 = 0;
            loss_valid_in_2 = 0;
            lrd_data_in_1 = 0;
            lrd_data_in_2 = 0;
            lrd_valid_in_1 = 0;
            lrd_valid_in_2 = 0;
        end
        else begin
            if(vpu_mode[3])begin
                bias_data_in_1 = systolic_data_in_1;
                bias_data_in_2 = systolic_data_in_2;
                bias_valid_in_1 = sysdata_valid_in_1;
                bias_valid_in_2 = sysdata_valid_in_2;

                b2lr_data_in_1 = bias_data_out_1;
                b2lr_data_in_2 = bias_data_out_2;
                b2lr_valid_in_1 = bias_valid_out_1;
                b2lr_valid_in_2 = bias_valid_out_2;
            end
            else begin
                bias_data_in_1 = 0;
                bias_data_in_2 = 0;
                bias_valid_in_1 = 0;
                bias_valid_in_2 = 0;

                b2lr_data_in_1 = systolic_data_in_1;
                b2lr_data_in_2 = systolic_data_in_2;
                b2lr_valid_in_1 = sysdata_valid_in_1;
                b2lr_valid_in_2 = sysdata_valid_in_2;
            end



            
            if(vpu_mode[2])begin
                lr_data_in_1 = b2lr_data_in_1;
                lr_data_in_2 = b2lr_data_in_2;
                lr_valid_in_1 = b2lr_valid_in_1;
                lr_valid_in_2 = b2lr_valid_in_2;

                lr2loss_data_in_1 = lr_data_out_1;
                lr2loss_data_in_2 = lr_data_out_2;
                lr2loss_valid_in_1 = lr_valid_out_1;
                lr2loss_valid_in_2 = lr_valid_out_2;
            end
            else begin
                lr_data_in_1 = 0;
                lr_data_in_2 = 0;
                lr_valid_in_1 = 0;
                lr_valid_in_2 = 0;

                lr2loss_data_in_1 = b2lr_data_in_1;
                lr2loss_data_in_2 = b2lr_data_in_2;
                lr2loss_valid_in_1 = b2lr_valid_in_1;
                lr2loss_valid_in_2 = b2lr_valid_in_2;
            end




            if(vpu_mode[1])begin
                loss_data_in_1 = lr2loss_data_in_1;
                loss_data_in_2 = lr2loss_data_in_2;
                loss_valid_in_1 = lr2loss_valid_in_1;
                loss_valid_in_2 = lr2loss_valid_in_2;

                loss2lrd_data_in_1 = loss_data_out_1;
                loss2lrd_data_in_2 = loss_data_out_2;
                loss2lrd_valid_in_1 = loss_valid_out_1;
                loss2lrd_valid_in_2 = loss_valid_out_2;


                last_H_data_in_1 = lr_data_out_1;
                last_H_data_in_2 = lr_data_out_2;
                leaky_data_in_1 = last_H_data_out_1;
                leaky_data_in_2 = last_H_data_out_2;
            end
            else begin
                loss_data_in_1 = 0;
                loss_data_in_2 = 0;
                loss_valid_in_1 = 0;
                loss_valid_in_2 = 0;

                loss2lrd_data_in_1 = lr2loss_data_in_1;
                loss2lrd_data_in_2 = lr2loss_data_in_2;
                loss2lrd_valid_in_1 = lr2loss_valid_in_1;
                loss2lrd_valid_in_2 = lr2loss_valid_in_2;

                last_H_data_in_1 =0;
                last_H_data_in_2 =0;
                leaky_data_in_1  = H_in_1;
                leaky_data_in_2  = H_in_2;
            end





            if(vpu_mode[0])begin
                lrd_data_in_1 = loss2lrd_data_in_1;
                lrd_data_in_2 = loss2lrd_data_in_2;
                lrd_valid_in_1 = loss2lrd_valid_in_1;
                lrd_valid_in_2 = loss2lrd_valid_in_2;

                vpu_data_mux_1 = lrd_data_out_1;
                vpu_data_mux_2 = lrd_data_out_2;
                vpu_valid_mux_1 = lrd_valid_out_1;
                vpu_valid_mux_2 = lrd_valid_out_2;
            end
            else begin
                lrd_data_in_1 = 0;
                lrd_data_in_2 = 0;
                lrd_valid_in_1 = 0;
                lrd_valid_in_2 = 0;

                vpu_data_mux_1 = loss2lrd_data_in_1;
                vpu_data_mux_2 = loss2lrd_data_in_2;
                vpu_valid_mux_1 = loss2lrd_valid_in_1;
                vpu_valid_mux_2 = loss2lrd_valid_in_2;
            end
        end
    end
//输出信号逻辑
    always @(posedge clk or negedge rst_n)begin
        if(!rst_n)begin
            last_H_data_out_1 <= 0;
            last_H_data_out_2 <= 0;
            vpu_out_1 <= 0;
            vpu_out_2 <= 0;
            vpu_valid_out_1 <= 0;
            vpu_valid_out_2 <= 0;
        end
        else begin
            vpu_out_1 <= vpu_data_mux_1;
            vpu_out_2 <= vpu_data_mux_2;
            vpu_valid_out_1 <= vpu_valid_mux_1;
            vpu_valid_out_2 <= vpu_valid_mux_2;
            if(vpu_mode[1])begin
                last_H_data_out_1 <= last_H_data_in_1;
                last_H_data_out_2 <= last_H_data_in_2;
            end
            else begin
                last_H_data_out_1 <= 0;
                last_H_data_out_2 <= 0;
            end
        end
    end
endmodule
