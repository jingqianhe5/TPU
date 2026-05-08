// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vsystolic__Syms.h"


void Vsystolic___024root__trace_chg_sub_0(Vsystolic___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vsystolic___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsystolic___024root__trace_chg_top_0\n"); );
    // Init
    Vsystolic___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vsystolic___024root*>(voidSelf);
    Vsystolic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vsystolic___024root__trace_chg_sub_0((&vlSymsp->TOP), bufp);
}

void Vsystolic___024root__trace_chg_sub_0(Vsystolic___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsystolic___024root__trace_chg_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[0U])) {
        bufp->chgSData(oldp+0,((((IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__inb_zoom__DOT__outi) 
                                 << 8U) | (IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__inb_zoom__DOT__outf))),16);
        bufp->chgBit(oldp+1,(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__overflow));
        bufp->chgBit(oldp+2,(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__inb_zoom__DOT__overflow));
        bufp->chgCData(oldp+3,(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__inb_zoom__DOT__ini),8);
        bufp->chgCData(oldp+4,(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__inb_zoom__DOT__outi),8);
        bufp->chgCData(oldp+5,(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__inb_zoom__DOT__outf),8);
        bufp->chgSData(oldp+6,((((IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__inb_zoom__DOT__outi) 
                                 << 8U) | (IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__inb_zoom__DOT__outf))),16);
        bufp->chgBit(oldp+7,(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__overflow));
        bufp->chgBit(oldp+8,(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__inb_zoom__DOT__overflow));
        bufp->chgCData(oldp+9,(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__inb_zoom__DOT__ini),8);
        bufp->chgCData(oldp+10,(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__inb_zoom__DOT__outi),8);
        bufp->chgCData(oldp+11,(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__inb_zoom__DOT__outf),8);
        bufp->chgBit(oldp+12,(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__overflow));
        bufp->chgBit(oldp+13,(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__overflow));
        bufp->chgBit(oldp+14,(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__overflow));
        bufp->chgBit(oldp+15,(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__overflow));
    }
    if (VL_UNLIKELY((vlSelf->__Vm_traceActivity[1U] 
                     | vlSelf->__Vm_traceActivity[2U]))) {
        bufp->chgSData(oldp+16,((((IData)(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outi) 
                                  << 8U) | (IData)(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outf))),16);
        bufp->chgBit(oldp+17,(vlSelf->systolic__DOT__pe_11__DOT__mul_overflow));
        bufp->chgBit(oldp+18,(vlSelf->systolic__DOT__pe_11__DOT__add_overflow));
        bufp->chgSData(oldp+19,((((IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outi) 
                                  << 8U) | (IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outf))),16);
        bufp->chgSData(oldp+20,((((IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__outi) 
                                  << 8U) | (IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__outf))),16);
        bufp->chgIData(oldp+21,((0x1ffffU & (VL_EXTENDS_II(17,16, 
                                                           (((IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__outi) 
                                                             << 8U) 
                                                            | (IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__outf))) 
                                             + VL_EXTENDS_II(17,16, 
                                                             (((IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__inb_zoom__DOT__outi) 
                                                               << 8U) 
                                                              | (IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__inb_zoom__DOT__outf)))))),17);
        bufp->chgSData(oldp+22,(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__inr),16);
        bufp->chgCData(oldp+23,(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__ini),8);
        bufp->chgCData(oldp+24,(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__outi),8);
        bufp->chgCData(oldp+25,(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__outf),8);
        bufp->chgIData(oldp+26,(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__inr),17);
        bufp->chgSData(oldp+27,(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__ini),9);
        bufp->chgCData(oldp+28,(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outi),8);
        bufp->chgCData(oldp+29,(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outf),8);
        bufp->chgIData(oldp+30,(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res),32);
        bufp->chgIData(oldp+31,(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__inr),24);
        bufp->chgSData(oldp+32,(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__ini),16);
        bufp->chgCData(oldp+33,(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outi),8);
        bufp->chgCData(oldp+34,(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outf),8);
        bufp->chgSData(oldp+35,((((IData)(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outi) 
                                  << 8U) | (IData)(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outf))),16);
        bufp->chgBit(oldp+36,(vlSelf->systolic__DOT__pe_21__DOT__mul_overflow));
        bufp->chgBit(oldp+37,(vlSelf->systolic__DOT__pe_21__DOT__add_overflow));
        bufp->chgSData(oldp+38,((((IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outi) 
                                  << 8U) | (IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outf))),16);
        bufp->chgSData(oldp+39,((((IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__outi) 
                                  << 8U) | (IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__outf))),16);
        bufp->chgIData(oldp+40,((0x1ffffU & (VL_EXTENDS_II(17,16, 
                                                           (((IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__outi) 
                                                             << 8U) 
                                                            | (IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__outf))) 
                                             + VL_EXTENDS_II(17,16, 
                                                             (((IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__outi) 
                                                               << 8U) 
                                                              | (IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__outf)))))),17);
        bufp->chgSData(oldp+41,(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__inr),16);
        bufp->chgCData(oldp+42,(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__ini),8);
        bufp->chgCData(oldp+43,(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__outi),8);
        bufp->chgCData(oldp+44,(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__outf),8);
        bufp->chgIData(oldp+45,(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__inr),17);
        bufp->chgSData(oldp+46,(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__ini),9);
        bufp->chgCData(oldp+47,(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outi),8);
        bufp->chgCData(oldp+48,(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outf),8);
        bufp->chgIData(oldp+49,(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res),32);
        bufp->chgIData(oldp+50,(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__inr),24);
        bufp->chgSData(oldp+51,(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__ini),16);
        bufp->chgCData(oldp+52,(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outi),8);
        bufp->chgCData(oldp+53,(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outf),8);
    }
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[2U])) {
        bufp->chgCData(oldp+54,(vlSelf->systolic__DOT__pe_enabled),2);
        bufp->chgSData(oldp+55,(vlSelf->systolic__DOT__weight_out_11),16);
        bufp->chgSData(oldp+56,(vlSelf->systolic__DOT__psum_out_11),16);
        bufp->chgBit(oldp+57,(vlSelf->systolic__DOT__switch_out_11));
        bufp->chgSData(oldp+58,(vlSelf->systolic__DOT__input_out_11),16);
        bufp->chgBit(oldp+59,(vlSelf->systolic__DOT__input_out_valid_11));
        bufp->chgSData(oldp+60,(vlSelf->systolic__DOT__weight_out_12),16);
        bufp->chgSData(oldp+61,(vlSelf->systolic__DOT__psum_out_12),16);
        bufp->chgBit(oldp+62,(vlSelf->systolic__DOT__switch_out_12));
        bufp->chgSData(oldp+63,(vlSelf->systolic__DOT__weight_out_21),16);
        bufp->chgBit(oldp+64,(vlSelf->systolic__DOT__switch_out_21));
        bufp->chgSData(oldp+65,(vlSelf->systolic__DOT__input_out_21),16);
        bufp->chgBit(oldp+66,(vlSelf->systolic__DOT__input_out_valid_21));
        bufp->chgSData(oldp+67,(vlSelf->systolic__DOT__weight_out_22),16);
        bufp->chgBit(oldp+68,(vlSelf->systolic__DOT__switch_out_22));
        bufp->chgBit(oldp+69,(vlSelf->systolic__DOT__input_out_valid_22));
        bufp->chgBit(oldp+70,((1U & (IData)(vlSelf->systolic__DOT__pe_enabled))));
        bufp->chgBit(oldp+71,(vlSelf->systolic__DOT__pe_11__DOT__overflow_out));
        bufp->chgSData(oldp+72,(vlSelf->systolic__DOT__pe_11__DOT__weight_in_active),16);
        bufp->chgSData(oldp+73,(vlSelf->systolic__DOT__pe_11__DOT__weight_in_buffer),16);
        bufp->chgSData(oldp+74,(vlSelf->systolic__DOT__pe_12__DOT__input_out),16);
        bufp->chgBit(oldp+75,(vlSelf->systolic__DOT__pe_12__DOT__input_out_valid));
        bufp->chgBit(oldp+76,((1U & ((IData)(vlSelf->systolic__DOT__pe_enabled) 
                                     >> 1U))));
        bufp->chgBit(oldp+77,(vlSelf->systolic__DOT__pe_12__DOT__overflow_out));
        bufp->chgSData(oldp+78,(vlSelf->systolic__DOT__pe_12__DOT__weight_in_active),16);
        bufp->chgSData(oldp+79,(vlSelf->systolic__DOT__pe_12__DOT__weight_in_buffer),16);
        bufp->chgSData(oldp+80,((((IData)(vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__outi) 
                                  << 8U) | (IData)(vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__outf))),16);
        bufp->chgBit(oldp+81,(vlSelf->systolic__DOT__pe_12__DOT__mul_overflow));
        bufp->chgBit(oldp+82,(vlSelf->systolic__DOT__pe_12__DOT__add_overflow));
        bufp->chgSData(oldp+83,((((IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__outi) 
                                  << 8U) | (IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__outf))),16);
        bufp->chgSData(oldp+84,((((IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__outi) 
                                  << 8U) | (IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__outf))),16);
        bufp->chgIData(oldp+85,((0x1ffffU & (VL_EXTENDS_II(17,16, 
                                                           (((IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__outi) 
                                                             << 8U) 
                                                            | (IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__outf))) 
                                             + VL_EXTENDS_II(17,16, 
                                                             (((IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__inb_zoom__DOT__outi) 
                                                               << 8U) 
                                                              | (IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__inb_zoom__DOT__outf)))))),17);
        bufp->chgSData(oldp+86,(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__inr),16);
        bufp->chgCData(oldp+87,(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__ini),8);
        bufp->chgCData(oldp+88,(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__outi),8);
        bufp->chgCData(oldp+89,(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__outf),8);
        bufp->chgIData(oldp+90,(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__inr),17);
        bufp->chgSData(oldp+91,(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__ini),9);
        bufp->chgCData(oldp+92,(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__outi),8);
        bufp->chgCData(oldp+93,(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__outf),8);
        bufp->chgIData(oldp+94,(vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res),32);
        bufp->chgIData(oldp+95,(vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__inr),24);
        bufp->chgSData(oldp+96,(vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__ini),16);
        bufp->chgCData(oldp+97,(vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__outi),8);
        bufp->chgCData(oldp+98,(vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__outf),8);
        bufp->chgBit(oldp+99,(vlSelf->systolic__DOT__pe_21__DOT__overflow_out));
        bufp->chgSData(oldp+100,(vlSelf->systolic__DOT__pe_21__DOT__weight_in_active),16);
        bufp->chgSData(oldp+101,(vlSelf->systolic__DOT__pe_21__DOT__weight_in_buffer),16);
        bufp->chgSData(oldp+102,((((IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__outi) 
                                   << 8U) | (IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__outf))),16);
        bufp->chgSData(oldp+103,(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__inr),16);
        bufp->chgCData(oldp+104,(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__ini),8);
        bufp->chgCData(oldp+105,(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__outi),8);
        bufp->chgCData(oldp+106,(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__outf),8);
        bufp->chgSData(oldp+107,(vlSelf->systolic__DOT__pe_22__DOT__input_out),16);
        bufp->chgBit(oldp+108,(vlSelf->systolic__DOT__pe_22__DOT__overflow_out));
        bufp->chgSData(oldp+109,(vlSelf->systolic__DOT__pe_22__DOT__weight_in_active),16);
        bufp->chgSData(oldp+110,(vlSelf->systolic__DOT__pe_22__DOT__weight_in_buffer),16);
        bufp->chgSData(oldp+111,((((IData)(vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__outi) 
                                   << 8U) | (IData)(vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__outf))),16);
        bufp->chgBit(oldp+112,(vlSelf->systolic__DOT__pe_22__DOT__mul_overflow));
        bufp->chgBit(oldp+113,(vlSelf->systolic__DOT__pe_22__DOT__add_overflow));
        bufp->chgSData(oldp+114,((((IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__outi) 
                                   << 8U) | (IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__outf))),16);
        bufp->chgSData(oldp+115,((((IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__outi) 
                                   << 8U) | (IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__outf))),16);
        bufp->chgSData(oldp+116,((((IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__outi) 
                                   << 8U) | (IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__outf))),16);
        bufp->chgIData(oldp+117,((0x1ffffU & (VL_EXTENDS_II(17,16, 
                                                            (((IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__outi) 
                                                              << 8U) 
                                                             | (IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__outf))) 
                                              + VL_EXTENDS_II(17,16, 
                                                              (((IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__outi) 
                                                                << 8U) 
                                                               | (IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__outf)))))),17);
        bufp->chgSData(oldp+118,(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__inr),16);
        bufp->chgCData(oldp+119,(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__ini),8);
        bufp->chgCData(oldp+120,(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__outi),8);
        bufp->chgCData(oldp+121,(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__outf),8);
        bufp->chgSData(oldp+122,(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__inr),16);
        bufp->chgCData(oldp+123,(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__ini),8);
        bufp->chgCData(oldp+124,(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__outi),8);
        bufp->chgCData(oldp+125,(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__outf),8);
        bufp->chgIData(oldp+126,(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__inr),17);
        bufp->chgSData(oldp+127,(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__ini),9);
        bufp->chgCData(oldp+128,(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__outi),8);
        bufp->chgCData(oldp+129,(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__outf),8);
        bufp->chgIData(oldp+130,(vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res),32);
        bufp->chgIData(oldp+131,(vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__inr),24);
        bufp->chgSData(oldp+132,(vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__ini),16);
        bufp->chgCData(oldp+133,(vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__outi),8);
        bufp->chgCData(oldp+134,(vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__outf),8);
    }
    bufp->chgBit(oldp+135,(vlSelf->clk));
    bufp->chgBit(oldp+136,(vlSelf->rst_n));
    bufp->chgSData(oldp+137,(vlSelf->x_11),16);
    bufp->chgSData(oldp+138,(vlSelf->x_21),16);
    bufp->chgBit(oldp+139,(vlSelf->x_valid_11));
    bufp->chgBit(oldp+140,(vlSelf->x_valid_21));
    bufp->chgSData(oldp+141,(vlSelf->z_21),16);
    bufp->chgSData(oldp+142,(vlSelf->z_22),16);
    bufp->chgBit(oldp+143,(vlSelf->z_valid_21));
    bufp->chgBit(oldp+144,(vlSelf->z_valid_22));
    bufp->chgSData(oldp+145,(vlSelf->w_11),16);
    bufp->chgSData(oldp+146,(vlSelf->w_12),16);
    bufp->chgBit(oldp+147,(vlSelf->weight_valid_col_1));
    bufp->chgBit(oldp+148,(vlSelf->weight_valid_col_2));
    bufp->chgBit(oldp+149,(vlSelf->switch_in));
    bufp->chgSData(oldp+150,(vlSelf->col_num),16);
    bufp->chgBit(oldp+151,(vlSelf->col_num_valid));
}

void Vsystolic___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsystolic___024root__trace_cleanup\n"); );
    // Init
    Vsystolic___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vsystolic___024root*>(voidSelf);
    Vsystolic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
}
