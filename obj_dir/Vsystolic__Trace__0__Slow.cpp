// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vsystolic__Syms.h"


VL_ATTR_COLD void Vsystolic___024root__trace_init_sub__TOP__0(Vsystolic___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsystolic___024root__trace_init_sub__TOP__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBit(c+136,"clk", false,-1);
    tracep->declBit(c+137,"rst_n", false,-1);
    tracep->declBus(c+138,"x_11", false,-1, 15,0);
    tracep->declBus(c+139,"x_21", false,-1, 15,0);
    tracep->declBit(c+140,"x_valid_11", false,-1);
    tracep->declBit(c+141,"x_valid_21", false,-1);
    tracep->declBus(c+142,"z_21", false,-1, 15,0);
    tracep->declBus(c+143,"z_22", false,-1, 15,0);
    tracep->declBit(c+144,"z_valid_21", false,-1);
    tracep->declBit(c+145,"z_valid_22", false,-1);
    tracep->declBus(c+146,"w_11", false,-1, 15,0);
    tracep->declBus(c+147,"w_12", false,-1, 15,0);
    tracep->declBit(c+148,"weight_valid_col_1", false,-1);
    tracep->declBit(c+149,"weight_valid_col_2", false,-1);
    tracep->declBit(c+150,"switch_in", false,-1);
    tracep->declBus(c+151,"col_num", false,-1, 15,0);
    tracep->declBit(c+152,"col_num_valid", false,-1);
    tracep->pushNamePrefix("systolic ");
    tracep->declBus(c+153,"WIDTH", false,-1, 31,0);
    tracep->declBus(c+154,"F_BITS", false,-1, 31,0);
    tracep->declBit(c+136,"clk", false,-1);
    tracep->declBit(c+137,"rst_n", false,-1);
    tracep->declBus(c+138,"x_11", false,-1, 15,0);
    tracep->declBus(c+139,"x_21", false,-1, 15,0);
    tracep->declBit(c+140,"x_valid_11", false,-1);
    tracep->declBit(c+141,"x_valid_21", false,-1);
    tracep->declBus(c+142,"z_21", false,-1, 15,0);
    tracep->declBus(c+143,"z_22", false,-1, 15,0);
    tracep->declBit(c+144,"z_valid_21", false,-1);
    tracep->declBit(c+145,"z_valid_22", false,-1);
    tracep->declBus(c+146,"w_11", false,-1, 15,0);
    tracep->declBus(c+147,"w_12", false,-1, 15,0);
    tracep->declBit(c+148,"weight_valid_col_1", false,-1);
    tracep->declBit(c+149,"weight_valid_col_2", false,-1);
    tracep->declBit(c+150,"switch_in", false,-1);
    tracep->declBus(c+151,"col_num", false,-1, 15,0);
    tracep->declBit(c+152,"col_num_valid", false,-1);
    tracep->declBus(c+55,"pe_enabled", false,-1, 1,0);
    tracep->declBus(c+56,"weight_out_11", false,-1, 15,0);
    tracep->declBus(c+57,"psum_out_11", false,-1, 15,0);
    tracep->declBit(c+58,"switch_out_11", false,-1);
    tracep->declBus(c+59,"input_out_11", false,-1, 15,0);
    tracep->declBit(c+60,"input_out_valid_11", false,-1);
    tracep->declBus(c+61,"weight_out_12", false,-1, 15,0);
    tracep->declBus(c+62,"psum_out_12", false,-1, 15,0);
    tracep->declBit(c+63,"switch_out_12", false,-1);
    tracep->declBus(c+155,"input_out_12", false,-1, 15,0);
    tracep->declBit(c+156,"input_out_valid_12", false,-1);
    tracep->declBus(c+64,"weight_out_21", false,-1, 15,0);
    tracep->declBus(c+157,"psum_out_21", false,-1, 15,0);
    tracep->declBit(c+65,"switch_out_21", false,-1);
    tracep->declBus(c+66,"input_out_21", false,-1, 15,0);
    tracep->declBit(c+67,"input_out_valid_21", false,-1);
    tracep->declBus(c+68,"weight_out_22", false,-1, 15,0);
    tracep->declBus(c+158,"psum_out_22", false,-1, 15,0);
    tracep->declBit(c+69,"switch_out_22", false,-1);
    tracep->declBus(c+159,"input_out_22", false,-1, 15,0);
    tracep->declBit(c+70,"input_out_valid_22", false,-1);
    tracep->pushNamePrefix("pe_11 ");
    tracep->declBus(c+153,"WIDTH", false,-1, 31,0);
    tracep->declBus(c+154,"F_BITS", false,-1, 31,0);
    tracep->declBit(c+136,"clk", false,-1);
    tracep->declBit(c+137,"rst_n", false,-1);
    tracep->declBus(c+138,"input_in", false,-1, 15,0);
    tracep->declBus(c+59,"input_out", false,-1, 15,0);
    tracep->declBit(c+140,"input_in_valid", false,-1);
    tracep->declBit(c+60,"input_out_valid", false,-1);
    tracep->declBus(c+146,"weight_in", false,-1, 15,0);
    tracep->declBus(c+56,"weight_out", false,-1, 15,0);
    tracep->declBit(c+148,"weight_valid", false,-1);
    tracep->declBus(c+160,"psum_in", false,-1, 15,0);
    tracep->declBus(c+57,"psum_out", false,-1, 15,0);
    tracep->declBit(c+150,"switch_in", false,-1);
    tracep->declBit(c+58,"switch_out", false,-1);
    tracep->declBit(c+71,"pe_enabled", false,-1);
    tracep->declBit(c+72,"overflow_out", false,-1);
    tracep->declBus(c+73,"weight_in_active", false,-1, 15,0);
    tracep->declBus(c+74,"weight_in_buffer", false,-1, 15,0);
    tracep->declBus(c+17,"mul_result", false,-1, 15,0);
    tracep->declBit(c+18,"mul_overflow", false,-1);
    tracep->declBit(c+19,"add_overflow", false,-1);
    tracep->declBus(c+20,"result", false,-1, 15,0);
    tracep->pushNamePrefix("adder ");
    tracep->declBus(c+154,"WIIA", false,-1, 31,0);
    tracep->declBus(c+154,"WIFA", false,-1, 31,0);
    tracep->declBus(c+154,"WIIB", false,-1, 31,0);
    tracep->declBus(c+154,"WIFB", false,-1, 31,0);
    tracep->declBus(c+154,"WOI", false,-1, 31,0);
    tracep->declBus(c+154,"WOF", false,-1, 31,0);
    tracep->declBus(c+161,"ROUND", false,-1, 31,0);
    tracep->declBus(c+17,"ina", false,-1, 15,0);
    tracep->declBus(c+160,"inb", false,-1, 15,0);
    tracep->declBus(c+20,"out", false,-1, 15,0);
    tracep->declBit(c+19,"overflow", false,-1);
    tracep->declBus(c+154,"WII", false,-1, 31,0);
    tracep->declBus(c+154,"WIF", false,-1, 31,0);
    tracep->declBus(c+162,"WRI", false,-1, 31,0);
    tracep->declBus(c+154,"WRF", false,-1, 31,0);
    tracep->declBus(c+21,"inaz", false,-1, 15,0);
    tracep->declBus(c+1,"inbz", false,-1, 15,0);
    tracep->declBus(c+22,"res", false,-1, 16,0);
    tracep->pushNamePrefix("ina_zoom ");
    tracep->declBus(c+154,"WII", false,-1, 31,0);
    tracep->declBus(c+154,"WIF", false,-1, 31,0);
    tracep->declBus(c+154,"WOI", false,-1, 31,0);
    tracep->declBus(c+154,"WOF", false,-1, 31,0);
    tracep->declBus(c+163,"ROUND", false,-1, 31,0);
    tracep->declBus(c+17,"in", false,-1, 15,0);
    tracep->declBus(c+21,"out", false,-1, 15,0);
    tracep->declBit(c+2,"overflow", false,-1);
    tracep->declBus(c+23,"inr", false,-1, 15,0);
    tracep->declBus(c+24,"ini", false,-1, 7,0);
    tracep->declBus(c+25,"outi", false,-1, 7,0);
    tracep->declBus(c+26,"outf", false,-1, 7,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("inb_zoom ");
    tracep->declBus(c+154,"WII", false,-1, 31,0);
    tracep->declBus(c+154,"WIF", false,-1, 31,0);
    tracep->declBus(c+154,"WOI", false,-1, 31,0);
    tracep->declBus(c+154,"WOF", false,-1, 31,0);
    tracep->declBus(c+163,"ROUND", false,-1, 31,0);
    tracep->declBus(c+160,"in", false,-1, 15,0);
    tracep->declBus(c+1,"out", false,-1, 15,0);
    tracep->declBit(c+3,"overflow", false,-1);
    tracep->declBus(c+160,"inr", false,-1, 15,0);
    tracep->declBus(c+4,"ini", false,-1, 7,0);
    tracep->declBus(c+5,"outi", false,-1, 7,0);
    tracep->declBus(c+6,"outf", false,-1, 7,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("res_zoom ");
    tracep->declBus(c+162,"WII", false,-1, 31,0);
    tracep->declBus(c+154,"WIF", false,-1, 31,0);
    tracep->declBus(c+154,"WOI", false,-1, 31,0);
    tracep->declBus(c+154,"WOF", false,-1, 31,0);
    tracep->declBus(c+161,"ROUND", false,-1, 31,0);
    tracep->declBus(c+22,"in", false,-1, 16,0);
    tracep->declBus(c+20,"out", false,-1, 15,0);
    tracep->declBit(c+19,"overflow", false,-1);
    tracep->declBus(c+27,"inr", false,-1, 16,0);
    tracep->declBus(c+28,"ini", false,-1, 8,0);
    tracep->declBus(c+29,"outi", false,-1, 7,0);
    tracep->declBus(c+30,"outf", false,-1, 7,0);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("mult ");
    tracep->declBus(c+154,"WIIA", false,-1, 31,0);
    tracep->declBus(c+154,"WIFA", false,-1, 31,0);
    tracep->declBus(c+154,"WIIB", false,-1, 31,0);
    tracep->declBus(c+154,"WIFB", false,-1, 31,0);
    tracep->declBus(c+154,"WOI", false,-1, 31,0);
    tracep->declBus(c+154,"WOF", false,-1, 31,0);
    tracep->declBus(c+161,"ROUND", false,-1, 31,0);
    tracep->declBus(c+138,"ina", false,-1, 15,0);
    tracep->declBus(c+73,"inb", false,-1, 15,0);
    tracep->declBus(c+17,"out", false,-1, 15,0);
    tracep->declBit(c+18,"overflow", false,-1);
    tracep->declBus(c+153,"WRI", false,-1, 31,0);
    tracep->declBus(c+153,"WRF", false,-1, 31,0);
    tracep->declBus(c+31,"res", false,-1, 31,0);
    tracep->pushNamePrefix("res_zoom ");
    tracep->declBus(c+153,"WII", false,-1, 31,0);
    tracep->declBus(c+153,"WIF", false,-1, 31,0);
    tracep->declBus(c+154,"WOI", false,-1, 31,0);
    tracep->declBus(c+154,"WOF", false,-1, 31,0);
    tracep->declBus(c+161,"ROUND", false,-1, 31,0);
    tracep->declBus(c+31,"in", false,-1, 31,0);
    tracep->declBus(c+17,"out", false,-1, 15,0);
    tracep->declBit(c+18,"overflow", false,-1);
    tracep->declBus(c+32,"inr", false,-1, 23,0);
    tracep->declBus(c+33,"ini", false,-1, 15,0);
    tracep->declBus(c+34,"outi", false,-1, 7,0);
    tracep->declBus(c+35,"outf", false,-1, 7,0);
    tracep->popNamePrefix(3);
    tracep->pushNamePrefix("pe_12 ");
    tracep->declBus(c+153,"WIDTH", false,-1, 31,0);
    tracep->declBus(c+154,"F_BITS", false,-1, 31,0);
    tracep->declBit(c+136,"clk", false,-1);
    tracep->declBit(c+137,"rst_n", false,-1);
    tracep->declBus(c+59,"input_in", false,-1, 15,0);
    tracep->declBus(c+75,"input_out", false,-1, 15,0);
    tracep->declBit(c+60,"input_in_valid", false,-1);
    tracep->declBit(c+76,"input_out_valid", false,-1);
    tracep->declBus(c+147,"weight_in", false,-1, 15,0);
    tracep->declBus(c+61,"weight_out", false,-1, 15,0);
    tracep->declBit(c+149,"weight_valid", false,-1);
    tracep->declBus(c+160,"psum_in", false,-1, 15,0);
    tracep->declBus(c+62,"psum_out", false,-1, 15,0);
    tracep->declBit(c+58,"switch_in", false,-1);
    tracep->declBit(c+63,"switch_out", false,-1);
    tracep->declBit(c+77,"pe_enabled", false,-1);
    tracep->declBit(c+78,"overflow_out", false,-1);
    tracep->declBus(c+79,"weight_in_active", false,-1, 15,0);
    tracep->declBus(c+80,"weight_in_buffer", false,-1, 15,0);
    tracep->declBus(c+81,"mul_result", false,-1, 15,0);
    tracep->declBit(c+82,"mul_overflow", false,-1);
    tracep->declBit(c+83,"add_overflow", false,-1);
    tracep->declBus(c+84,"result", false,-1, 15,0);
    tracep->pushNamePrefix("adder ");
    tracep->declBus(c+154,"WIIA", false,-1, 31,0);
    tracep->declBus(c+154,"WIFA", false,-1, 31,0);
    tracep->declBus(c+154,"WIIB", false,-1, 31,0);
    tracep->declBus(c+154,"WIFB", false,-1, 31,0);
    tracep->declBus(c+154,"WOI", false,-1, 31,0);
    tracep->declBus(c+154,"WOF", false,-1, 31,0);
    tracep->declBus(c+161,"ROUND", false,-1, 31,0);
    tracep->declBus(c+81,"ina", false,-1, 15,0);
    tracep->declBus(c+160,"inb", false,-1, 15,0);
    tracep->declBus(c+84,"out", false,-1, 15,0);
    tracep->declBit(c+83,"overflow", false,-1);
    tracep->declBus(c+154,"WII", false,-1, 31,0);
    tracep->declBus(c+154,"WIF", false,-1, 31,0);
    tracep->declBus(c+162,"WRI", false,-1, 31,0);
    tracep->declBus(c+154,"WRF", false,-1, 31,0);
    tracep->declBus(c+85,"inaz", false,-1, 15,0);
    tracep->declBus(c+7,"inbz", false,-1, 15,0);
    tracep->declBus(c+86,"res", false,-1, 16,0);
    tracep->pushNamePrefix("ina_zoom ");
    tracep->declBus(c+154,"WII", false,-1, 31,0);
    tracep->declBus(c+154,"WIF", false,-1, 31,0);
    tracep->declBus(c+154,"WOI", false,-1, 31,0);
    tracep->declBus(c+154,"WOF", false,-1, 31,0);
    tracep->declBus(c+163,"ROUND", false,-1, 31,0);
    tracep->declBus(c+81,"in", false,-1, 15,0);
    tracep->declBus(c+85,"out", false,-1, 15,0);
    tracep->declBit(c+8,"overflow", false,-1);
    tracep->declBus(c+87,"inr", false,-1, 15,0);
    tracep->declBus(c+88,"ini", false,-1, 7,0);
    tracep->declBus(c+89,"outi", false,-1, 7,0);
    tracep->declBus(c+90,"outf", false,-1, 7,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("inb_zoom ");
    tracep->declBus(c+154,"WII", false,-1, 31,0);
    tracep->declBus(c+154,"WIF", false,-1, 31,0);
    tracep->declBus(c+154,"WOI", false,-1, 31,0);
    tracep->declBus(c+154,"WOF", false,-1, 31,0);
    tracep->declBus(c+163,"ROUND", false,-1, 31,0);
    tracep->declBus(c+160,"in", false,-1, 15,0);
    tracep->declBus(c+7,"out", false,-1, 15,0);
    tracep->declBit(c+9,"overflow", false,-1);
    tracep->declBus(c+160,"inr", false,-1, 15,0);
    tracep->declBus(c+10,"ini", false,-1, 7,0);
    tracep->declBus(c+11,"outi", false,-1, 7,0);
    tracep->declBus(c+12,"outf", false,-1, 7,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("res_zoom ");
    tracep->declBus(c+162,"WII", false,-1, 31,0);
    tracep->declBus(c+154,"WIF", false,-1, 31,0);
    tracep->declBus(c+154,"WOI", false,-1, 31,0);
    tracep->declBus(c+154,"WOF", false,-1, 31,0);
    tracep->declBus(c+161,"ROUND", false,-1, 31,0);
    tracep->declBus(c+86,"in", false,-1, 16,0);
    tracep->declBus(c+84,"out", false,-1, 15,0);
    tracep->declBit(c+83,"overflow", false,-1);
    tracep->declBus(c+91,"inr", false,-1, 16,0);
    tracep->declBus(c+92,"ini", false,-1, 8,0);
    tracep->declBus(c+93,"outi", false,-1, 7,0);
    tracep->declBus(c+94,"outf", false,-1, 7,0);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("mult ");
    tracep->declBus(c+154,"WIIA", false,-1, 31,0);
    tracep->declBus(c+154,"WIFA", false,-1, 31,0);
    tracep->declBus(c+154,"WIIB", false,-1, 31,0);
    tracep->declBus(c+154,"WIFB", false,-1, 31,0);
    tracep->declBus(c+154,"WOI", false,-1, 31,0);
    tracep->declBus(c+154,"WOF", false,-1, 31,0);
    tracep->declBus(c+161,"ROUND", false,-1, 31,0);
    tracep->declBus(c+59,"ina", false,-1, 15,0);
    tracep->declBus(c+79,"inb", false,-1, 15,0);
    tracep->declBus(c+81,"out", false,-1, 15,0);
    tracep->declBit(c+82,"overflow", false,-1);
    tracep->declBus(c+153,"WRI", false,-1, 31,0);
    tracep->declBus(c+153,"WRF", false,-1, 31,0);
    tracep->declBus(c+95,"res", false,-1, 31,0);
    tracep->pushNamePrefix("res_zoom ");
    tracep->declBus(c+153,"WII", false,-1, 31,0);
    tracep->declBus(c+153,"WIF", false,-1, 31,0);
    tracep->declBus(c+154,"WOI", false,-1, 31,0);
    tracep->declBus(c+154,"WOF", false,-1, 31,0);
    tracep->declBus(c+161,"ROUND", false,-1, 31,0);
    tracep->declBus(c+95,"in", false,-1, 31,0);
    tracep->declBus(c+81,"out", false,-1, 15,0);
    tracep->declBit(c+82,"overflow", false,-1);
    tracep->declBus(c+96,"inr", false,-1, 23,0);
    tracep->declBus(c+97,"ini", false,-1, 15,0);
    tracep->declBus(c+98,"outi", false,-1, 7,0);
    tracep->declBus(c+99,"outf", false,-1, 7,0);
    tracep->popNamePrefix(3);
    tracep->pushNamePrefix("pe_21 ");
    tracep->declBus(c+153,"WIDTH", false,-1, 31,0);
    tracep->declBus(c+154,"F_BITS", false,-1, 31,0);
    tracep->declBit(c+136,"clk", false,-1);
    tracep->declBit(c+137,"rst_n", false,-1);
    tracep->declBus(c+139,"input_in", false,-1, 15,0);
    tracep->declBus(c+66,"input_out", false,-1, 15,0);
    tracep->declBit(c+141,"input_in_valid", false,-1);
    tracep->declBit(c+67,"input_out_valid", false,-1);
    tracep->declBus(c+56,"weight_in", false,-1, 15,0);
    tracep->declBus(c+64,"weight_out", false,-1, 15,0);
    tracep->declBit(c+148,"weight_valid", false,-1);
    tracep->declBus(c+57,"psum_in", false,-1, 15,0);
    tracep->declBus(c+142,"psum_out", false,-1, 15,0);
    tracep->declBit(c+58,"switch_in", false,-1);
    tracep->declBit(c+65,"switch_out", false,-1);
    tracep->declBit(c+71,"pe_enabled", false,-1);
    tracep->declBit(c+100,"overflow_out", false,-1);
    tracep->declBus(c+101,"weight_in_active", false,-1, 15,0);
    tracep->declBus(c+102,"weight_in_buffer", false,-1, 15,0);
    tracep->declBus(c+36,"mul_result", false,-1, 15,0);
    tracep->declBit(c+37,"mul_overflow", false,-1);
    tracep->declBit(c+38,"add_overflow", false,-1);
    tracep->declBus(c+39,"result", false,-1, 15,0);
    tracep->pushNamePrefix("adder ");
    tracep->declBus(c+154,"WIIA", false,-1, 31,0);
    tracep->declBus(c+154,"WIFA", false,-1, 31,0);
    tracep->declBus(c+154,"WIIB", false,-1, 31,0);
    tracep->declBus(c+154,"WIFB", false,-1, 31,0);
    tracep->declBus(c+154,"WOI", false,-1, 31,0);
    tracep->declBus(c+154,"WOF", false,-1, 31,0);
    tracep->declBus(c+161,"ROUND", false,-1, 31,0);
    tracep->declBus(c+36,"ina", false,-1, 15,0);
    tracep->declBus(c+57,"inb", false,-1, 15,0);
    tracep->declBus(c+39,"out", false,-1, 15,0);
    tracep->declBit(c+38,"overflow", false,-1);
    tracep->declBus(c+154,"WII", false,-1, 31,0);
    tracep->declBus(c+154,"WIF", false,-1, 31,0);
    tracep->declBus(c+162,"WRI", false,-1, 31,0);
    tracep->declBus(c+154,"WRF", false,-1, 31,0);
    tracep->declBus(c+40,"inaz", false,-1, 15,0);
    tracep->declBus(c+103,"inbz", false,-1, 15,0);
    tracep->declBus(c+41,"res", false,-1, 16,0);
    tracep->pushNamePrefix("ina_zoom ");
    tracep->declBus(c+154,"WII", false,-1, 31,0);
    tracep->declBus(c+154,"WIF", false,-1, 31,0);
    tracep->declBus(c+154,"WOI", false,-1, 31,0);
    tracep->declBus(c+154,"WOF", false,-1, 31,0);
    tracep->declBus(c+163,"ROUND", false,-1, 31,0);
    tracep->declBus(c+36,"in", false,-1, 15,0);
    tracep->declBus(c+40,"out", false,-1, 15,0);
    tracep->declBit(c+13,"overflow", false,-1);
    tracep->declBus(c+42,"inr", false,-1, 15,0);
    tracep->declBus(c+43,"ini", false,-1, 7,0);
    tracep->declBus(c+44,"outi", false,-1, 7,0);
    tracep->declBus(c+45,"outf", false,-1, 7,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("inb_zoom ");
    tracep->declBus(c+154,"WII", false,-1, 31,0);
    tracep->declBus(c+154,"WIF", false,-1, 31,0);
    tracep->declBus(c+154,"WOI", false,-1, 31,0);
    tracep->declBus(c+154,"WOF", false,-1, 31,0);
    tracep->declBus(c+163,"ROUND", false,-1, 31,0);
    tracep->declBus(c+57,"in", false,-1, 15,0);
    tracep->declBus(c+103,"out", false,-1, 15,0);
    tracep->declBit(c+14,"overflow", false,-1);
    tracep->declBus(c+104,"inr", false,-1, 15,0);
    tracep->declBus(c+105,"ini", false,-1, 7,0);
    tracep->declBus(c+106,"outi", false,-1, 7,0);
    tracep->declBus(c+107,"outf", false,-1, 7,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("res_zoom ");
    tracep->declBus(c+162,"WII", false,-1, 31,0);
    tracep->declBus(c+154,"WIF", false,-1, 31,0);
    tracep->declBus(c+154,"WOI", false,-1, 31,0);
    tracep->declBus(c+154,"WOF", false,-1, 31,0);
    tracep->declBus(c+161,"ROUND", false,-1, 31,0);
    tracep->declBus(c+41,"in", false,-1, 16,0);
    tracep->declBus(c+39,"out", false,-1, 15,0);
    tracep->declBit(c+38,"overflow", false,-1);
    tracep->declBus(c+46,"inr", false,-1, 16,0);
    tracep->declBus(c+47,"ini", false,-1, 8,0);
    tracep->declBus(c+48,"outi", false,-1, 7,0);
    tracep->declBus(c+49,"outf", false,-1, 7,0);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("mult ");
    tracep->declBus(c+154,"WIIA", false,-1, 31,0);
    tracep->declBus(c+154,"WIFA", false,-1, 31,0);
    tracep->declBus(c+154,"WIIB", false,-1, 31,0);
    tracep->declBus(c+154,"WIFB", false,-1, 31,0);
    tracep->declBus(c+154,"WOI", false,-1, 31,0);
    tracep->declBus(c+154,"WOF", false,-1, 31,0);
    tracep->declBus(c+161,"ROUND", false,-1, 31,0);
    tracep->declBus(c+139,"ina", false,-1, 15,0);
    tracep->declBus(c+101,"inb", false,-1, 15,0);
    tracep->declBus(c+36,"out", false,-1, 15,0);
    tracep->declBit(c+37,"overflow", false,-1);
    tracep->declBus(c+153,"WRI", false,-1, 31,0);
    tracep->declBus(c+153,"WRF", false,-1, 31,0);
    tracep->declBus(c+50,"res", false,-1, 31,0);
    tracep->pushNamePrefix("res_zoom ");
    tracep->declBus(c+153,"WII", false,-1, 31,0);
    tracep->declBus(c+153,"WIF", false,-1, 31,0);
    tracep->declBus(c+154,"WOI", false,-1, 31,0);
    tracep->declBus(c+154,"WOF", false,-1, 31,0);
    tracep->declBus(c+161,"ROUND", false,-1, 31,0);
    tracep->declBus(c+50,"in", false,-1, 31,0);
    tracep->declBus(c+36,"out", false,-1, 15,0);
    tracep->declBit(c+37,"overflow", false,-1);
    tracep->declBus(c+51,"inr", false,-1, 23,0);
    tracep->declBus(c+52,"ini", false,-1, 15,0);
    tracep->declBus(c+53,"outi", false,-1, 7,0);
    tracep->declBus(c+54,"outf", false,-1, 7,0);
    tracep->popNamePrefix(3);
    tracep->pushNamePrefix("pe_22 ");
    tracep->declBus(c+153,"WIDTH", false,-1, 31,0);
    tracep->declBus(c+154,"F_BITS", false,-1, 31,0);
    tracep->declBit(c+136,"clk", false,-1);
    tracep->declBit(c+137,"rst_n", false,-1);
    tracep->declBus(c+66,"input_in", false,-1, 15,0);
    tracep->declBus(c+108,"input_out", false,-1, 15,0);
    tracep->declBit(c+67,"input_in_valid", false,-1);
    tracep->declBit(c+70,"input_out_valid", false,-1);
    tracep->declBus(c+61,"weight_in", false,-1, 15,0);
    tracep->declBus(c+68,"weight_out", false,-1, 15,0);
    tracep->declBit(c+149,"weight_valid", false,-1);
    tracep->declBus(c+62,"psum_in", false,-1, 15,0);
    tracep->declBus(c+143,"psum_out", false,-1, 15,0);
    tracep->declBit(c+63,"switch_in", false,-1);
    tracep->declBit(c+69,"switch_out", false,-1);
    tracep->declBit(c+77,"pe_enabled", false,-1);
    tracep->declBit(c+109,"overflow_out", false,-1);
    tracep->declBus(c+110,"weight_in_active", false,-1, 15,0);
    tracep->declBus(c+111,"weight_in_buffer", false,-1, 15,0);
    tracep->declBus(c+112,"mul_result", false,-1, 15,0);
    tracep->declBit(c+113,"mul_overflow", false,-1);
    tracep->declBit(c+114,"add_overflow", false,-1);
    tracep->declBus(c+115,"result", false,-1, 15,0);
    tracep->pushNamePrefix("adder ");
    tracep->declBus(c+154,"WIIA", false,-1, 31,0);
    tracep->declBus(c+154,"WIFA", false,-1, 31,0);
    tracep->declBus(c+154,"WIIB", false,-1, 31,0);
    tracep->declBus(c+154,"WIFB", false,-1, 31,0);
    tracep->declBus(c+154,"WOI", false,-1, 31,0);
    tracep->declBus(c+154,"WOF", false,-1, 31,0);
    tracep->declBus(c+161,"ROUND", false,-1, 31,0);
    tracep->declBus(c+112,"ina", false,-1, 15,0);
    tracep->declBus(c+62,"inb", false,-1, 15,0);
    tracep->declBus(c+115,"out", false,-1, 15,0);
    tracep->declBit(c+114,"overflow", false,-1);
    tracep->declBus(c+154,"WII", false,-1, 31,0);
    tracep->declBus(c+154,"WIF", false,-1, 31,0);
    tracep->declBus(c+162,"WRI", false,-1, 31,0);
    tracep->declBus(c+154,"WRF", false,-1, 31,0);
    tracep->declBus(c+116,"inaz", false,-1, 15,0);
    tracep->declBus(c+117,"inbz", false,-1, 15,0);
    tracep->declBus(c+118,"res", false,-1, 16,0);
    tracep->pushNamePrefix("ina_zoom ");
    tracep->declBus(c+154,"WII", false,-1, 31,0);
    tracep->declBus(c+154,"WIF", false,-1, 31,0);
    tracep->declBus(c+154,"WOI", false,-1, 31,0);
    tracep->declBus(c+154,"WOF", false,-1, 31,0);
    tracep->declBus(c+163,"ROUND", false,-1, 31,0);
    tracep->declBus(c+112,"in", false,-1, 15,0);
    tracep->declBus(c+116,"out", false,-1, 15,0);
    tracep->declBit(c+15,"overflow", false,-1);
    tracep->declBus(c+119,"inr", false,-1, 15,0);
    tracep->declBus(c+120,"ini", false,-1, 7,0);
    tracep->declBus(c+121,"outi", false,-1, 7,0);
    tracep->declBus(c+122,"outf", false,-1, 7,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("inb_zoom ");
    tracep->declBus(c+154,"WII", false,-1, 31,0);
    tracep->declBus(c+154,"WIF", false,-1, 31,0);
    tracep->declBus(c+154,"WOI", false,-1, 31,0);
    tracep->declBus(c+154,"WOF", false,-1, 31,0);
    tracep->declBus(c+163,"ROUND", false,-1, 31,0);
    tracep->declBus(c+62,"in", false,-1, 15,0);
    tracep->declBus(c+117,"out", false,-1, 15,0);
    tracep->declBit(c+16,"overflow", false,-1);
    tracep->declBus(c+123,"inr", false,-1, 15,0);
    tracep->declBus(c+124,"ini", false,-1, 7,0);
    tracep->declBus(c+125,"outi", false,-1, 7,0);
    tracep->declBus(c+126,"outf", false,-1, 7,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("res_zoom ");
    tracep->declBus(c+162,"WII", false,-1, 31,0);
    tracep->declBus(c+154,"WIF", false,-1, 31,0);
    tracep->declBus(c+154,"WOI", false,-1, 31,0);
    tracep->declBus(c+154,"WOF", false,-1, 31,0);
    tracep->declBus(c+161,"ROUND", false,-1, 31,0);
    tracep->declBus(c+118,"in", false,-1, 16,0);
    tracep->declBus(c+115,"out", false,-1, 15,0);
    tracep->declBit(c+114,"overflow", false,-1);
    tracep->declBus(c+127,"inr", false,-1, 16,0);
    tracep->declBus(c+128,"ini", false,-1, 8,0);
    tracep->declBus(c+129,"outi", false,-1, 7,0);
    tracep->declBus(c+130,"outf", false,-1, 7,0);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("mult ");
    tracep->declBus(c+154,"WIIA", false,-1, 31,0);
    tracep->declBus(c+154,"WIFA", false,-1, 31,0);
    tracep->declBus(c+154,"WIIB", false,-1, 31,0);
    tracep->declBus(c+154,"WIFB", false,-1, 31,0);
    tracep->declBus(c+154,"WOI", false,-1, 31,0);
    tracep->declBus(c+154,"WOF", false,-1, 31,0);
    tracep->declBus(c+161,"ROUND", false,-1, 31,0);
    tracep->declBus(c+66,"ina", false,-1, 15,0);
    tracep->declBus(c+110,"inb", false,-1, 15,0);
    tracep->declBus(c+112,"out", false,-1, 15,0);
    tracep->declBit(c+113,"overflow", false,-1);
    tracep->declBus(c+153,"WRI", false,-1, 31,0);
    tracep->declBus(c+153,"WRF", false,-1, 31,0);
    tracep->declBus(c+131,"res", false,-1, 31,0);
    tracep->pushNamePrefix("res_zoom ");
    tracep->declBus(c+153,"WII", false,-1, 31,0);
    tracep->declBus(c+153,"WIF", false,-1, 31,0);
    tracep->declBus(c+154,"WOI", false,-1, 31,0);
    tracep->declBus(c+154,"WOF", false,-1, 31,0);
    tracep->declBus(c+161,"ROUND", false,-1, 31,0);
    tracep->declBus(c+131,"in", false,-1, 31,0);
    tracep->declBus(c+112,"out", false,-1, 15,0);
    tracep->declBit(c+113,"overflow", false,-1);
    tracep->declBus(c+132,"inr", false,-1, 23,0);
    tracep->declBus(c+133,"ini", false,-1, 15,0);
    tracep->declBus(c+134,"outi", false,-1, 7,0);
    tracep->declBus(c+135,"outf", false,-1, 7,0);
    tracep->popNamePrefix(4);
}

VL_ATTR_COLD void Vsystolic___024root__trace_init_top(Vsystolic___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsystolic___024root__trace_init_top\n"); );
    // Body
    Vsystolic___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vsystolic___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vsystolic___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vsystolic___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vsystolic___024root__trace_register(Vsystolic___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsystolic___024root__trace_register\n"); );
    // Body
    tracep->addFullCb(&Vsystolic___024root__trace_full_top_0, vlSelf);
    tracep->addChgCb(&Vsystolic___024root__trace_chg_top_0, vlSelf);
    tracep->addCleanupCb(&Vsystolic___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vsystolic___024root__trace_full_sub_0(Vsystolic___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vsystolic___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsystolic___024root__trace_full_top_0\n"); );
    // Init
    Vsystolic___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vsystolic___024root*>(voidSelf);
    Vsystolic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vsystolic___024root__trace_full_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vsystolic___024root__trace_full_sub_0(Vsystolic___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsystolic___024root__trace_full_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullSData(oldp+1,((((IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__inb_zoom__DOT__outi) 
                              << 8U) | (IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__inb_zoom__DOT__outf))),16);
    bufp->fullBit(oldp+2,(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__overflow));
    bufp->fullBit(oldp+3,(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__inb_zoom__DOT__overflow));
    bufp->fullCData(oldp+4,(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__inb_zoom__DOT__ini),8);
    bufp->fullCData(oldp+5,(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__inb_zoom__DOT__outi),8);
    bufp->fullCData(oldp+6,(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__inb_zoom__DOT__outf),8);
    bufp->fullSData(oldp+7,((((IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__inb_zoom__DOT__outi) 
                              << 8U) | (IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__inb_zoom__DOT__outf))),16);
    bufp->fullBit(oldp+8,(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__overflow));
    bufp->fullBit(oldp+9,(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__inb_zoom__DOT__overflow));
    bufp->fullCData(oldp+10,(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__inb_zoom__DOT__ini),8);
    bufp->fullCData(oldp+11,(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__inb_zoom__DOT__outi),8);
    bufp->fullCData(oldp+12,(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__inb_zoom__DOT__outf),8);
    bufp->fullBit(oldp+13,(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__overflow));
    bufp->fullBit(oldp+14,(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__overflow));
    bufp->fullBit(oldp+15,(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__overflow));
    bufp->fullBit(oldp+16,(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__overflow));
    bufp->fullSData(oldp+17,((((IData)(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outi) 
                               << 8U) | (IData)(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outf))),16);
    bufp->fullBit(oldp+18,(vlSelf->systolic__DOT__pe_11__DOT__mul_overflow));
    bufp->fullBit(oldp+19,(vlSelf->systolic__DOT__pe_11__DOT__add_overflow));
    bufp->fullSData(oldp+20,((((IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outi) 
                               << 8U) | (IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outf))),16);
    bufp->fullSData(oldp+21,((((IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__outi) 
                               << 8U) | (IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__outf))),16);
    bufp->fullIData(oldp+22,((0x1ffffU & (VL_EXTENDS_II(17,16, 
                                                        (((IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__outi) 
                                                          << 8U) 
                                                         | (IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__outf))) 
                                          + VL_EXTENDS_II(17,16, 
                                                          (((IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__inb_zoom__DOT__outi) 
                                                            << 8U) 
                                                           | (IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__inb_zoom__DOT__outf)))))),17);
    bufp->fullSData(oldp+23,(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__inr),16);
    bufp->fullCData(oldp+24,(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__ini),8);
    bufp->fullCData(oldp+25,(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__outi),8);
    bufp->fullCData(oldp+26,(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__outf),8);
    bufp->fullIData(oldp+27,(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__inr),17);
    bufp->fullSData(oldp+28,(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__ini),9);
    bufp->fullCData(oldp+29,(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outi),8);
    bufp->fullCData(oldp+30,(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outf),8);
    bufp->fullIData(oldp+31,(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res),32);
    bufp->fullIData(oldp+32,(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__inr),24);
    bufp->fullSData(oldp+33,(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__ini),16);
    bufp->fullCData(oldp+34,(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outi),8);
    bufp->fullCData(oldp+35,(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outf),8);
    bufp->fullSData(oldp+36,((((IData)(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outi) 
                               << 8U) | (IData)(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outf))),16);
    bufp->fullBit(oldp+37,(vlSelf->systolic__DOT__pe_21__DOT__mul_overflow));
    bufp->fullBit(oldp+38,(vlSelf->systolic__DOT__pe_21__DOT__add_overflow));
    bufp->fullSData(oldp+39,((((IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outi) 
                               << 8U) | (IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outf))),16);
    bufp->fullSData(oldp+40,((((IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__outi) 
                               << 8U) | (IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__outf))),16);
    bufp->fullIData(oldp+41,((0x1ffffU & (VL_EXTENDS_II(17,16, 
                                                        (((IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__outi) 
                                                          << 8U) 
                                                         | (IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__outf))) 
                                          + VL_EXTENDS_II(17,16, 
                                                          (((IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__outi) 
                                                            << 8U) 
                                                           | (IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__outf)))))),17);
    bufp->fullSData(oldp+42,(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__inr),16);
    bufp->fullCData(oldp+43,(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__ini),8);
    bufp->fullCData(oldp+44,(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__outi),8);
    bufp->fullCData(oldp+45,(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__outf),8);
    bufp->fullIData(oldp+46,(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__inr),17);
    bufp->fullSData(oldp+47,(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__ini),9);
    bufp->fullCData(oldp+48,(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outi),8);
    bufp->fullCData(oldp+49,(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outf),8);
    bufp->fullIData(oldp+50,(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res),32);
    bufp->fullIData(oldp+51,(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__inr),24);
    bufp->fullSData(oldp+52,(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__ini),16);
    bufp->fullCData(oldp+53,(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outi),8);
    bufp->fullCData(oldp+54,(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outf),8);
    bufp->fullCData(oldp+55,(vlSelf->systolic__DOT__pe_enabled),2);
    bufp->fullSData(oldp+56,(vlSelf->systolic__DOT__weight_out_11),16);
    bufp->fullSData(oldp+57,(vlSelf->systolic__DOT__psum_out_11),16);
    bufp->fullBit(oldp+58,(vlSelf->systolic__DOT__switch_out_11));
    bufp->fullSData(oldp+59,(vlSelf->systolic__DOT__input_out_11),16);
    bufp->fullBit(oldp+60,(vlSelf->systolic__DOT__input_out_valid_11));
    bufp->fullSData(oldp+61,(vlSelf->systolic__DOT__weight_out_12),16);
    bufp->fullSData(oldp+62,(vlSelf->systolic__DOT__psum_out_12),16);
    bufp->fullBit(oldp+63,(vlSelf->systolic__DOT__switch_out_12));
    bufp->fullSData(oldp+64,(vlSelf->systolic__DOT__weight_out_21),16);
    bufp->fullBit(oldp+65,(vlSelf->systolic__DOT__switch_out_21));
    bufp->fullSData(oldp+66,(vlSelf->systolic__DOT__input_out_21),16);
    bufp->fullBit(oldp+67,(vlSelf->systolic__DOT__input_out_valid_21));
    bufp->fullSData(oldp+68,(vlSelf->systolic__DOT__weight_out_22),16);
    bufp->fullBit(oldp+69,(vlSelf->systolic__DOT__switch_out_22));
    bufp->fullBit(oldp+70,(vlSelf->systolic__DOT__input_out_valid_22));
    bufp->fullBit(oldp+71,((1U & (IData)(vlSelf->systolic__DOT__pe_enabled))));
    bufp->fullBit(oldp+72,(vlSelf->systolic__DOT__pe_11__DOT__overflow_out));
    bufp->fullSData(oldp+73,(vlSelf->systolic__DOT__pe_11__DOT__weight_in_active),16);
    bufp->fullSData(oldp+74,(vlSelf->systolic__DOT__pe_11__DOT__weight_in_buffer),16);
    bufp->fullSData(oldp+75,(vlSelf->systolic__DOT__pe_12__DOT__input_out),16);
    bufp->fullBit(oldp+76,(vlSelf->systolic__DOT__pe_12__DOT__input_out_valid));
    bufp->fullBit(oldp+77,((1U & ((IData)(vlSelf->systolic__DOT__pe_enabled) 
                                  >> 1U))));
    bufp->fullBit(oldp+78,(vlSelf->systolic__DOT__pe_12__DOT__overflow_out));
    bufp->fullSData(oldp+79,(vlSelf->systolic__DOT__pe_12__DOT__weight_in_active),16);
    bufp->fullSData(oldp+80,(vlSelf->systolic__DOT__pe_12__DOT__weight_in_buffer),16);
    bufp->fullSData(oldp+81,((((IData)(vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__outi) 
                               << 8U) | (IData)(vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__outf))),16);
    bufp->fullBit(oldp+82,(vlSelf->systolic__DOT__pe_12__DOT__mul_overflow));
    bufp->fullBit(oldp+83,(vlSelf->systolic__DOT__pe_12__DOT__add_overflow));
    bufp->fullSData(oldp+84,((((IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__outi) 
                               << 8U) | (IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__outf))),16);
    bufp->fullSData(oldp+85,((((IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__outi) 
                               << 8U) | (IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__outf))),16);
    bufp->fullIData(oldp+86,((0x1ffffU & (VL_EXTENDS_II(17,16, 
                                                        (((IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__outi) 
                                                          << 8U) 
                                                         | (IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__outf))) 
                                          + VL_EXTENDS_II(17,16, 
                                                          (((IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__inb_zoom__DOT__outi) 
                                                            << 8U) 
                                                           | (IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__inb_zoom__DOT__outf)))))),17);
    bufp->fullSData(oldp+87,(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__inr),16);
    bufp->fullCData(oldp+88,(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__ini),8);
    bufp->fullCData(oldp+89,(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__outi),8);
    bufp->fullCData(oldp+90,(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__outf),8);
    bufp->fullIData(oldp+91,(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__inr),17);
    bufp->fullSData(oldp+92,(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__ini),9);
    bufp->fullCData(oldp+93,(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__outi),8);
    bufp->fullCData(oldp+94,(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__outf),8);
    bufp->fullIData(oldp+95,(vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res),32);
    bufp->fullIData(oldp+96,(vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__inr),24);
    bufp->fullSData(oldp+97,(vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__ini),16);
    bufp->fullCData(oldp+98,(vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__outi),8);
    bufp->fullCData(oldp+99,(vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__outf),8);
    bufp->fullBit(oldp+100,(vlSelf->systolic__DOT__pe_21__DOT__overflow_out));
    bufp->fullSData(oldp+101,(vlSelf->systolic__DOT__pe_21__DOT__weight_in_active),16);
    bufp->fullSData(oldp+102,(vlSelf->systolic__DOT__pe_21__DOT__weight_in_buffer),16);
    bufp->fullSData(oldp+103,((((IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__outi) 
                                << 8U) | (IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__outf))),16);
    bufp->fullSData(oldp+104,(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__inr),16);
    bufp->fullCData(oldp+105,(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__ini),8);
    bufp->fullCData(oldp+106,(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__outi),8);
    bufp->fullCData(oldp+107,(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__outf),8);
    bufp->fullSData(oldp+108,(vlSelf->systolic__DOT__pe_22__DOT__input_out),16);
    bufp->fullBit(oldp+109,(vlSelf->systolic__DOT__pe_22__DOT__overflow_out));
    bufp->fullSData(oldp+110,(vlSelf->systolic__DOT__pe_22__DOT__weight_in_active),16);
    bufp->fullSData(oldp+111,(vlSelf->systolic__DOT__pe_22__DOT__weight_in_buffer),16);
    bufp->fullSData(oldp+112,((((IData)(vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__outi) 
                                << 8U) | (IData)(vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__outf))),16);
    bufp->fullBit(oldp+113,(vlSelf->systolic__DOT__pe_22__DOT__mul_overflow));
    bufp->fullBit(oldp+114,(vlSelf->systolic__DOT__pe_22__DOT__add_overflow));
    bufp->fullSData(oldp+115,((((IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__outi) 
                                << 8U) | (IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__outf))),16);
    bufp->fullSData(oldp+116,((((IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__outi) 
                                << 8U) | (IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__outf))),16);
    bufp->fullSData(oldp+117,((((IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__outi) 
                                << 8U) | (IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__outf))),16);
    bufp->fullIData(oldp+118,((0x1ffffU & (VL_EXTENDS_II(17,16, 
                                                         (((IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__outi) 
                                                           << 8U) 
                                                          | (IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__outf))) 
                                           + VL_EXTENDS_II(17,16, 
                                                           (((IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__outi) 
                                                             << 8U) 
                                                            | (IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__outf)))))),17);
    bufp->fullSData(oldp+119,(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__inr),16);
    bufp->fullCData(oldp+120,(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__ini),8);
    bufp->fullCData(oldp+121,(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__outi),8);
    bufp->fullCData(oldp+122,(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__outf),8);
    bufp->fullSData(oldp+123,(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__inr),16);
    bufp->fullCData(oldp+124,(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__ini),8);
    bufp->fullCData(oldp+125,(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__outi),8);
    bufp->fullCData(oldp+126,(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__outf),8);
    bufp->fullIData(oldp+127,(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__inr),17);
    bufp->fullSData(oldp+128,(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__ini),9);
    bufp->fullCData(oldp+129,(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__outi),8);
    bufp->fullCData(oldp+130,(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__outf),8);
    bufp->fullIData(oldp+131,(vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res),32);
    bufp->fullIData(oldp+132,(vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__inr),24);
    bufp->fullSData(oldp+133,(vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__ini),16);
    bufp->fullCData(oldp+134,(vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__outi),8);
    bufp->fullCData(oldp+135,(vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__outf),8);
    bufp->fullBit(oldp+136,(vlSelf->clk));
    bufp->fullBit(oldp+137,(vlSelf->rst_n));
    bufp->fullSData(oldp+138,(vlSelf->x_11),16);
    bufp->fullSData(oldp+139,(vlSelf->x_21),16);
    bufp->fullBit(oldp+140,(vlSelf->x_valid_11));
    bufp->fullBit(oldp+141,(vlSelf->x_valid_21));
    bufp->fullSData(oldp+142,(vlSelf->z_21),16);
    bufp->fullSData(oldp+143,(vlSelf->z_22),16);
    bufp->fullBit(oldp+144,(vlSelf->z_valid_21));
    bufp->fullBit(oldp+145,(vlSelf->z_valid_22));
    bufp->fullSData(oldp+146,(vlSelf->w_11),16);
    bufp->fullSData(oldp+147,(vlSelf->w_12),16);
    bufp->fullBit(oldp+148,(vlSelf->weight_valid_col_1));
    bufp->fullBit(oldp+149,(vlSelf->weight_valid_col_2));
    bufp->fullBit(oldp+150,(vlSelf->switch_in));
    bufp->fullSData(oldp+151,(vlSelf->col_num),16);
    bufp->fullBit(oldp+152,(vlSelf->col_num_valid));
    bufp->fullIData(oldp+153,(0x10U),32);
    bufp->fullIData(oldp+154,(8U),32);
    bufp->fullSData(oldp+155,(vlSelf->systolic__DOT__input_out_12),16);
    bufp->fullBit(oldp+156,(vlSelf->systolic__DOT__input_out_valid_12));
    bufp->fullSData(oldp+157,(vlSelf->systolic__DOT__psum_out_21),16);
    bufp->fullSData(oldp+158,(vlSelf->systolic__DOT__psum_out_22),16);
    bufp->fullSData(oldp+159,(vlSelf->systolic__DOT__input_out_22),16);
    bufp->fullSData(oldp+160,(0U),16);
    bufp->fullIData(oldp+161,(1U),32);
    bufp->fullIData(oldp+162,(9U),32);
    bufp->fullIData(oldp+163,(0U),32);
}
