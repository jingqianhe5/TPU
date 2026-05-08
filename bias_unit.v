module bias_unit#(
    parameter WIDTH = 16,
    parameter F_BITS = 8
)
(
    input   clk,
    input   rst_n,
    //输入
    input   signed [WIDTH-1:0] bias_data_in,//需要偏置的数据
    input               bias_valid_in,//数据有效
    input   signed [WIDTH-1:0] bias_scalar_in, //偏置的标量输入
    //输出
    output  reg signed [WIDTH-1:0] bias_data_out,//偏置后的数据输出
    output  reg             bias_valid_out,//数据有效输出
    output  reg             overflow_out//溢出输出
);
    wire signed [WIDTH-1:0] result;//暂存结果
    wire add_overflow;


    fxp_add #(
        .WIIA   (WIDTH - F_BITS),
        .WIFA   (F_BITS),
        .WIIB   (WIDTH - F_BITS),
        .WIFB   (F_BITS),
        .WOI    (WIDTH - F_BITS),
        .WOF    (F_BITS)
    ) adder (
        .ina(bias_data_in),
        .inb(bias_scalar_in),
        .out(result),
        .overflow(add_overflow)
    );

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            bias_data_out <= {WIDTH{1'b0}};
            bias_valid_out <= 1'b0;
            overflow_out <= 1'b0;
        end
        else begin
            if(bias_valid_in)begin
                bias_valid_out <= 1'b1;
                bias_data_out <= result;
                overflow_out <= add_overflow|overflow_out;
            end
            else begin
                bias_valid_out <= 1'b0;
                bias_data_out <= {WIDTH{1'b0}};
            end
        end
    end
endmodule
