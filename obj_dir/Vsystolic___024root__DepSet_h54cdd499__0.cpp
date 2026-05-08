// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsystolic.h for the primary calling header

#include "verilated.h"

#include "Vsystolic___024root.h"

VL_INLINE_OPT void Vsystolic___024root___ico_sequent__TOP__0(Vsystolic___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsystolic___024root___ico_sequent__TOP__0\n"); );
    // Body
    vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res 
        = VL_MULS_III(32, VL_EXTENDS_II(32,16, (IData)(vlSelf->x_11)), 
                      VL_EXTENDS_II(32,16, (IData)(vlSelf->systolic__DOT__pe_11__DOT__weight_in_active)));
    vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res 
        = VL_MULS_III(32, VL_EXTENDS_II(32,16, (IData)(vlSelf->x_21)), 
                      VL_EXTENDS_II(32,16, (IData)(vlSelf->systolic__DOT__pe_21__DOT__weight_in_active)));
    vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__inr 
        = (vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res 
           >> 8U);
    if ((1U & ((vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res 
                >> 7U) & (~ (IData)((0x7fffffU == vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__inr)))))) {
        vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__inr 
            = (0xffffffU & ((IData)(1U) + vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__inr));
    }
    vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__inr 
        = (vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res 
           >> 8U);
    if ((1U & ((vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res 
                >> 7U) & (~ (IData)((0x7fffffU == vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__inr)))))) {
        vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__inr 
            = (0xffffffU & ((IData)(1U) + vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__inr));
    }
    vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__ini 
        = (0xffffU & (vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__inr 
                      >> 8U));
    vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outf 
        = (0xffU & vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__inr);
    if (((~ ((IData)(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__ini) 
             >> 0xfU)) & (0U != (0xffU & ((IData)(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__ini) 
                                          >> 7U))))) {
        vlSelf->systolic__DOT__pe_11__DOT__mul_overflow = 1U;
        vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outi = 0xffU;
        vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outf = 0xffU;
        vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outi 
            = (0x7fU & (IData)(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outi));
    } else if ((IData)((((IData)(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__ini) 
                         >> 0xfU) & (~ (IData)((0xffU 
                                                == 
                                                (0xffU 
                                                 & ((IData)(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__ini) 
                                                    >> 7U)))))))) {
        vlSelf->systolic__DOT__pe_11__DOT__mul_overflow = 1U;
        vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outi = 0U;
        vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outf = 0U;
        vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outi 
            = (0x80U | (IData)(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outi));
    } else {
        vlSelf->systolic__DOT__pe_11__DOT__mul_overflow = 0U;
        vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outi 
            = (0xffU & (IData)(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__ini));
    }
    vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__ini 
        = (0xffffU & (vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__inr 
                      >> 8U));
    vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outf 
        = (0xffU & vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__inr);
    if (((~ ((IData)(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__ini) 
             >> 0xfU)) & (0U != (0xffU & ((IData)(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__ini) 
                                          >> 7U))))) {
        vlSelf->systolic__DOT__pe_21__DOT__mul_overflow = 1U;
        vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outi = 0xffU;
        vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outf = 0xffU;
        vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outi 
            = (0x7fU & (IData)(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outi));
    } else if ((IData)((((IData)(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__ini) 
                         >> 0xfU) & (~ (IData)((0xffU 
                                                == 
                                                (0xffU 
                                                 & ((IData)(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__ini) 
                                                    >> 7U)))))))) {
        vlSelf->systolic__DOT__pe_21__DOT__mul_overflow = 1U;
        vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outi = 0U;
        vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outf = 0U;
        vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outi 
            = (0x80U | (IData)(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outi));
    } else {
        vlSelf->systolic__DOT__pe_21__DOT__mul_overflow = 0U;
        vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outi 
            = (0xffU & (IData)(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__ini));
    }
    vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__inr 
        = (((IData)(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outi) 
            << 8U) | (IData)(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outf));
    vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__inr 
        = (((IData)(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outi) 
            << 8U) | (IData)(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outf));
    vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__outf 
        = (0xffU & (IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__inr));
    vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__ini 
        = (0xffU & ((IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__inr) 
                    >> 8U));
    vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__outi 
        = vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__ini;
    vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__outf 
        = (0xffU & (IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__inr));
    vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__ini 
        = (0xffU & ((IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__inr) 
                    >> 8U));
    vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__outi 
        = vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__ini;
    vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__inr 
        = (0x1ffffU & (VL_EXTENDS_II(17,16, (((IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__outi) 
                                              << 8U) 
                                             | (IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__outf))) 
                       + VL_EXTENDS_II(17,16, (((IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__inb_zoom__DOT__outi) 
                                                << 8U) 
                                               | (IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__inb_zoom__DOT__outf)))));
    vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__inr 
        = (0x1ffffU & (VL_EXTENDS_II(17,16, (((IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__outi) 
                                              << 8U) 
                                             | (IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__outf))) 
                       + VL_EXTENDS_II(17,16, (((IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__outi) 
                                                << 8U) 
                                               | (IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__outf)))));
    vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__ini 
        = (0x1ffU & (vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__inr 
                     >> 8U));
    vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outf 
        = (0xffU & vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__inr);
    if ((IData)((0x80U == (0x180U & (IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__ini))))) {
        vlSelf->systolic__DOT__pe_11__DOT__add_overflow = 1U;
        vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outi = 0xffU;
        vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outf = 0xffU;
        vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outi 
            = (0x7fU & (IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outi));
    } else if ((IData)((0x100U == (0x180U & (IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__ini))))) {
        vlSelf->systolic__DOT__pe_11__DOT__add_overflow = 1U;
        vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outi = 0U;
        vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outf = 0U;
        vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outi 
            = (0x80U | (IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outi));
    } else {
        vlSelf->systolic__DOT__pe_11__DOT__add_overflow = 0U;
        vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outi 
            = (0xffU & (IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__ini));
    }
    vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__ini 
        = (0x1ffU & (vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__inr 
                     >> 8U));
    vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outf 
        = (0xffU & vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__inr);
    if ((IData)((0x80U == (0x180U & (IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__ini))))) {
        vlSelf->systolic__DOT__pe_21__DOT__add_overflow = 1U;
        vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outi = 0xffU;
        vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outf = 0xffU;
        vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outi 
            = (0x7fU & (IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outi));
    } else if ((IData)((0x100U == (0x180U & (IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__ini))))) {
        vlSelf->systolic__DOT__pe_21__DOT__add_overflow = 1U;
        vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outi = 0U;
        vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outf = 0U;
        vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outi 
            = (0x80U | (IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outi));
    } else {
        vlSelf->systolic__DOT__pe_21__DOT__add_overflow = 0U;
        vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outi 
            = (0xffU & (IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__ini));
    }
}

void Vsystolic___024root___eval_ico(Vsystolic___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsystolic___024root___eval_ico\n"); );
    // Body
    if (vlSelf->__VicoTriggered.at(0U)) {
        Vsystolic___024root___ico_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[1U] = 1U;
    }
}

void Vsystolic___024root___eval_act(Vsystolic___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsystolic___024root___eval_act\n"); );
}

VL_INLINE_OPT void Vsystolic___024root___nba_sequent__TOP__0(Vsystolic___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsystolic___024root___nba_sequent__TOP__0\n"); );
    // Init
    CData/*0:0*/ __Vdly__systolic__DOT__pe_11__DOT__overflow_out;
    __Vdly__systolic__DOT__pe_11__DOT__overflow_out = 0;
    CData/*0:0*/ __Vdly__systolic__DOT__pe_12__DOT__overflow_out;
    __Vdly__systolic__DOT__pe_12__DOT__overflow_out = 0;
    CData/*0:0*/ __Vdly__systolic__DOT__pe_21__DOT__overflow_out;
    __Vdly__systolic__DOT__pe_21__DOT__overflow_out = 0;
    CData/*0:0*/ __Vdly__systolic__DOT__pe_22__DOT__overflow_out;
    __Vdly__systolic__DOT__pe_22__DOT__overflow_out = 0;
    // Body
    __Vdly__systolic__DOT__pe_21__DOT__overflow_out 
        = vlSelf->systolic__DOT__pe_21__DOT__overflow_out;
    __Vdly__systolic__DOT__pe_11__DOT__overflow_out 
        = vlSelf->systolic__DOT__pe_11__DOT__overflow_out;
    __Vdly__systolic__DOT__pe_12__DOT__overflow_out 
        = vlSelf->systolic__DOT__pe_12__DOT__overflow_out;
    __Vdly__systolic__DOT__pe_22__DOT__overflow_out 
        = vlSelf->systolic__DOT__pe_22__DOT__overflow_out;
    if ((1U & ((~ (IData)(vlSelf->rst_n)) | (~ ((IData)(vlSelf->systolic__DOT__pe_enabled) 
                                                >> 1U))))) {
        __Vdly__systolic__DOT__pe_12__DOT__overflow_out = 0U;
        __Vdly__systolic__DOT__pe_22__DOT__overflow_out = 0U;
        vlSelf->systolic__DOT__weight_out_22 = 0U;
        vlSelf->z_22 = 0U;
        vlSelf->systolic__DOT__psum_out_12 = 0U;
        vlSelf->systolic__DOT__pe_12__DOT__weight_in_active = 0U;
        vlSelf->systolic__DOT__pe_12__DOT__input_out = 0U;
        vlSelf->systolic__DOT__pe_22__DOT__input_out = 0U;
    } else {
        if (vlSelf->systolic__DOT__input_out_valid_11) {
            __Vdly__systolic__DOT__pe_12__DOT__overflow_out 
                = ((IData)(vlSelf->systolic__DOT__pe_12__DOT__overflow_out) 
                   | ((IData)(vlSelf->systolic__DOT__pe_12__DOT__mul_overflow) 
                      | (IData)(vlSelf->systolic__DOT__pe_12__DOT__add_overflow)));
            vlSelf->systolic__DOT__psum_out_12 = (((IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__outi) 
                                                   << 8U) 
                                                  | (IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__outf));
            vlSelf->systolic__DOT__pe_12__DOT__input_out 
                = vlSelf->systolic__DOT__input_out_11;
        } else {
            vlSelf->systolic__DOT__psum_out_12 = 0U;
            vlSelf->systolic__DOT__pe_12__DOT__input_out = 0U;
        }
        if (vlSelf->systolic__DOT__input_out_valid_21) {
            __Vdly__systolic__DOT__pe_22__DOT__overflow_out 
                = ((IData)(vlSelf->systolic__DOT__pe_22__DOT__overflow_out) 
                   | ((IData)(vlSelf->systolic__DOT__pe_22__DOT__mul_overflow) 
                      | (IData)(vlSelf->systolic__DOT__pe_22__DOT__add_overflow)));
            vlSelf->z_22 = (((IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__outi) 
                             << 8U) | (IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__outf));
            vlSelf->systolic__DOT__pe_22__DOT__input_out 
                = vlSelf->systolic__DOT__input_out_21;
        } else {
            vlSelf->z_22 = 0U;
            vlSelf->systolic__DOT__pe_22__DOT__input_out = 0U;
        }
        vlSelf->systolic__DOT__weight_out_22 = ((IData)(vlSelf->weight_valid_col_2)
                                                 ? (IData)(vlSelf->systolic__DOT__weight_out_12)
                                                 : 0U);
        if (vlSelf->systolic__DOT__switch_out_11) {
            vlSelf->systolic__DOT__pe_12__DOT__weight_in_active 
                = vlSelf->systolic__DOT__pe_12__DOT__weight_in_buffer;
        }
    }
    if ((1U & ((~ (IData)(vlSelf->rst_n)) | (~ (IData)(vlSelf->systolic__DOT__pe_enabled))))) {
        __Vdly__systolic__DOT__pe_21__DOT__overflow_out = 0U;
        __Vdly__systolic__DOT__pe_11__DOT__overflow_out = 0U;
        vlSelf->z_21 = 0U;
        vlSelf->systolic__DOT__psum_out_11 = 0U;
        vlSelf->systolic__DOT__weight_out_21 = 0U;
        vlSelf->systolic__DOT__pe_11__DOT__weight_in_active = 0U;
        vlSelf->systolic__DOT__pe_21__DOT__weight_in_active = 0U;
        vlSelf->systolic__DOT__pe_11__DOT__weight_in_buffer = 0U;
        vlSelf->systolic__DOT__input_out_11 = 0U;
        vlSelf->systolic__DOT__input_out_21 = 0U;
        vlSelf->systolic__DOT__pe_21__DOT__weight_in_buffer = 0U;
        vlSelf->systolic__DOT__weight_out_11 = 0U;
    } else {
        if (vlSelf->x_valid_21) {
            __Vdly__systolic__DOT__pe_21__DOT__overflow_out 
                = ((IData)(vlSelf->systolic__DOT__pe_21__DOT__overflow_out) 
                   | ((IData)(vlSelf->systolic__DOT__pe_21__DOT__mul_overflow) 
                      | (IData)(vlSelf->systolic__DOT__pe_21__DOT__add_overflow)));
            vlSelf->z_21 = (((IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outi) 
                             << 8U) | (IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outf));
            vlSelf->systolic__DOT__input_out_21 = vlSelf->x_21;
        } else {
            vlSelf->z_21 = 0U;
            vlSelf->systolic__DOT__input_out_21 = 0U;
        }
        if (vlSelf->x_valid_11) {
            __Vdly__systolic__DOT__pe_11__DOT__overflow_out 
                = ((IData)(vlSelf->systolic__DOT__pe_11__DOT__overflow_out) 
                   | ((IData)(vlSelf->systolic__DOT__pe_11__DOT__mul_overflow) 
                      | (IData)(vlSelf->systolic__DOT__pe_11__DOT__add_overflow)));
            vlSelf->systolic__DOT__psum_out_11 = (((IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outi) 
                                                   << 8U) 
                                                  | (IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outf));
            vlSelf->systolic__DOT__input_out_11 = vlSelf->x_11;
        } else {
            vlSelf->systolic__DOT__psum_out_11 = 0U;
            vlSelf->systolic__DOT__input_out_11 = 0U;
        }
        if (vlSelf->switch_in) {
            vlSelf->systolic__DOT__pe_11__DOT__weight_in_active 
                = vlSelf->systolic__DOT__pe_11__DOT__weight_in_buffer;
        }
        if (vlSelf->systolic__DOT__switch_out_11) {
            vlSelf->systolic__DOT__pe_21__DOT__weight_in_active 
                = vlSelf->systolic__DOT__pe_21__DOT__weight_in_buffer;
        }
        if (vlSelf->weight_valid_col_1) {
            vlSelf->systolic__DOT__weight_out_21 = vlSelf->systolic__DOT__weight_out_11;
            vlSelf->systolic__DOT__pe_11__DOT__weight_in_buffer 
                = vlSelf->w_11;
            vlSelf->systolic__DOT__pe_21__DOT__weight_in_buffer 
                = vlSelf->systolic__DOT__weight_out_11;
            vlSelf->systolic__DOT__weight_out_11 = vlSelf->w_11;
        } else {
            vlSelf->systolic__DOT__weight_out_21 = 0U;
            vlSelf->systolic__DOT__weight_out_11 = 0U;
        }
    }
    if ((1U & ((~ (IData)(vlSelf->rst_n)) | (~ ((IData)(vlSelf->systolic__DOT__pe_enabled) 
                                                >> 1U))))) {
        vlSelf->systolic__DOT__pe_22__DOT__weight_in_active = 0U;
        vlSelf->systolic__DOT__pe_12__DOT__weight_in_buffer = 0U;
        vlSelf->systolic__DOT__pe_22__DOT__weight_in_buffer = 0U;
        vlSelf->systolic__DOT__weight_out_12 = 0U;
    } else {
        if (vlSelf->systolic__DOT__switch_out_12) {
            vlSelf->systolic__DOT__pe_22__DOT__weight_in_active 
                = vlSelf->systolic__DOT__pe_22__DOT__weight_in_buffer;
        }
        if (vlSelf->weight_valid_col_2) {
            vlSelf->systolic__DOT__pe_12__DOT__weight_in_buffer 
                = vlSelf->w_12;
            vlSelf->systolic__DOT__pe_22__DOT__weight_in_buffer 
                = vlSelf->systolic__DOT__weight_out_12;
            vlSelf->systolic__DOT__weight_out_12 = vlSelf->w_12;
        } else {
            vlSelf->systolic__DOT__weight_out_12 = 0U;
        }
    }
    vlSelf->systolic__DOT__switch_out_21 = ((~ ((~ (IData)(vlSelf->rst_n)) 
                                                | (~ (IData)(vlSelf->systolic__DOT__pe_enabled)))) 
                                            & (IData)(vlSelf->systolic__DOT__switch_out_11));
    vlSelf->systolic__DOT__pe_12__DOT__input_out_valid 
        = ((~ ((~ (IData)(vlSelf->rst_n)) | (~ ((IData)(vlSelf->systolic__DOT__pe_enabled) 
                                                >> 1U)))) 
           & (IData)(vlSelf->systolic__DOT__input_out_valid_11));
    vlSelf->systolic__DOT__input_out_valid_22 = ((~ 
                                                  ((~ (IData)(vlSelf->rst_n)) 
                                                   | (~ 
                                                      ((IData)(vlSelf->systolic__DOT__pe_enabled) 
                                                       >> 1U)))) 
                                                 & (IData)(vlSelf->systolic__DOT__input_out_valid_21));
    vlSelf->systolic__DOT__switch_out_22 = ((~ ((~ (IData)(vlSelf->rst_n)) 
                                                | (~ 
                                                   ((IData)(vlSelf->systolic__DOT__pe_enabled) 
                                                    >> 1U)))) 
                                            & (IData)(vlSelf->systolic__DOT__switch_out_12));
    vlSelf->systolic__DOT__pe_21__DOT__overflow_out 
        = __Vdly__systolic__DOT__pe_21__DOT__overflow_out;
    vlSelf->systolic__DOT__pe_11__DOT__overflow_out 
        = __Vdly__systolic__DOT__pe_11__DOT__overflow_out;
    vlSelf->systolic__DOT__pe_12__DOT__overflow_out 
        = __Vdly__systolic__DOT__pe_12__DOT__overflow_out;
    vlSelf->systolic__DOT__pe_22__DOT__overflow_out 
        = __Vdly__systolic__DOT__pe_22__DOT__overflow_out;
    vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__inr 
        = vlSelf->systolic__DOT__psum_out_11;
    vlSelf->z_valid_22 = vlSelf->systolic__DOT__input_out_valid_22;
    vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__inr 
        = vlSelf->systolic__DOT__psum_out_12;
    vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res 
        = VL_MULS_III(32, VL_EXTENDS_II(32,16, (IData)(vlSelf->x_11)), 
                      VL_EXTENDS_II(32,16, (IData)(vlSelf->systolic__DOT__pe_11__DOT__weight_in_active)));
    vlSelf->systolic__DOT__input_out_valid_11 = ((~ 
                                                  ((~ (IData)(vlSelf->rst_n)) 
                                                   | (~ (IData)(vlSelf->systolic__DOT__pe_enabled)))) 
                                                 & (IData)(vlSelf->x_valid_11));
    vlSelf->systolic__DOT__input_out_valid_21 = ((~ 
                                                  ((~ (IData)(vlSelf->rst_n)) 
                                                   | (~ (IData)(vlSelf->systolic__DOT__pe_enabled)))) 
                                                 & (IData)(vlSelf->x_valid_21));
    vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res 
        = VL_MULS_III(32, VL_EXTENDS_II(32,16, (IData)(vlSelf->x_21)), 
                      VL_EXTENDS_II(32,16, (IData)(vlSelf->systolic__DOT__pe_21__DOT__weight_in_active)));
    vlSelf->systolic__DOT__switch_out_12 = ((~ ((~ (IData)(vlSelf->rst_n)) 
                                                | (~ 
                                                   ((IData)(vlSelf->systolic__DOT__pe_enabled) 
                                                    >> 1U)))) 
                                            & (IData)(vlSelf->systolic__DOT__switch_out_11));
    vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__outf 
        = (0xffU & (IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__inr));
    vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__ini 
        = (0xffU & ((IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__inr) 
                    >> 8U));
    vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__outi 
        = vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__ini;
    vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__outf 
        = (0xffU & (IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__inr));
    vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__ini 
        = (0xffU & ((IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__inr) 
                    >> 8U));
    vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__outi 
        = vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__ini;
    vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__inr 
        = (vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res 
           >> 8U);
    if ((1U & ((vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res 
                >> 7U) & (~ (IData)((0x7fffffU == vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__inr)))))) {
        vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__inr 
            = (0xffffffU & ((IData)(1U) + vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__inr));
    }
    vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__inr 
        = (vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res 
           >> 8U);
    if ((1U & ((vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res 
                >> 7U) & (~ (IData)((0x7fffffU == vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__inr)))))) {
        vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__inr 
            = (0xffffffU & ((IData)(1U) + vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__inr));
    }
    vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__ini 
        = (0xffffU & (vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__inr 
                      >> 8U));
    vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outf 
        = (0xffU & vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__inr);
    if (((~ ((IData)(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__ini) 
             >> 0xfU)) & (0U != (0xffU & ((IData)(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__ini) 
                                          >> 7U))))) {
        vlSelf->systolic__DOT__pe_11__DOT__mul_overflow = 1U;
        vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outi = 0xffU;
        vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outf = 0xffU;
        vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outi 
            = (0x7fU & (IData)(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outi));
    } else if ((IData)((((IData)(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__ini) 
                         >> 0xfU) & (~ (IData)((0xffU 
                                                == 
                                                (0xffU 
                                                 & ((IData)(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__ini) 
                                                    >> 7U)))))))) {
        vlSelf->systolic__DOT__pe_11__DOT__mul_overflow = 1U;
        vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outi = 0U;
        vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outf = 0U;
        vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outi 
            = (0x80U | (IData)(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outi));
    } else {
        vlSelf->systolic__DOT__pe_11__DOT__mul_overflow = 0U;
        vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outi 
            = (0xffU & (IData)(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__ini));
    }
    vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res 
        = VL_MULS_III(32, VL_EXTENDS_II(32,16, (IData)(vlSelf->systolic__DOT__input_out_11)), 
                      VL_EXTENDS_II(32,16, (IData)(vlSelf->systolic__DOT__pe_12__DOT__weight_in_active)));
    vlSelf->z_valid_21 = vlSelf->systolic__DOT__input_out_valid_21;
    vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res 
        = VL_MULS_III(32, VL_EXTENDS_II(32,16, (IData)(vlSelf->systolic__DOT__input_out_21)), 
                      VL_EXTENDS_II(32,16, (IData)(vlSelf->systolic__DOT__pe_22__DOT__weight_in_active)));
    vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__ini 
        = (0xffffU & (vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__inr 
                      >> 8U));
    vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outf 
        = (0xffU & vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__inr);
    if (((~ ((IData)(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__ini) 
             >> 0xfU)) & (0U != (0xffU & ((IData)(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__ini) 
                                          >> 7U))))) {
        vlSelf->systolic__DOT__pe_21__DOT__mul_overflow = 1U;
        vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outi = 0xffU;
        vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outf = 0xffU;
        vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outi 
            = (0x7fU & (IData)(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outi));
    } else if ((IData)((((IData)(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__ini) 
                         >> 0xfU) & (~ (IData)((0xffU 
                                                == 
                                                (0xffU 
                                                 & ((IData)(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__ini) 
                                                    >> 7U)))))))) {
        vlSelf->systolic__DOT__pe_21__DOT__mul_overflow = 1U;
        vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outi = 0U;
        vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outf = 0U;
        vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outi 
            = (0x80U | (IData)(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outi));
    } else {
        vlSelf->systolic__DOT__pe_21__DOT__mul_overflow = 0U;
        vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outi 
            = (0xffU & (IData)(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__ini));
    }
    vlSelf->systolic__DOT__switch_out_11 = ((~ ((~ (IData)(vlSelf->rst_n)) 
                                                | (~ (IData)(vlSelf->systolic__DOT__pe_enabled)))) 
                                            & (IData)(vlSelf->switch_in));
    vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__inr 
        = (((IData)(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outi) 
            << 8U) | (IData)(vlSelf->systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outf));
    vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__inr 
        = (vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res 
           >> 8U);
    if ((1U & ((vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res 
                >> 7U) & (~ (IData)((0x7fffffU == vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__inr)))))) {
        vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__inr 
            = (0xffffffU & ((IData)(1U) + vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__inr));
    }
    vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__inr 
        = (vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res 
           >> 8U);
    if ((1U & ((vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res 
                >> 7U) & (~ (IData)((0x7fffffU == vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__inr)))))) {
        vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__inr 
            = (0xffffffU & ((IData)(1U) + vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__inr));
    }
    vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__inr 
        = (((IData)(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outi) 
            << 8U) | (IData)(vlSelf->systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outf));
    vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__outf 
        = (0xffU & (IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__inr));
    vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__ini 
        = (0xffU & ((IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__inr) 
                    >> 8U));
    vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__outi 
        = vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__ini;
    vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__ini 
        = (0xffffU & (vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__inr 
                      >> 8U));
    vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__outf 
        = (0xffU & vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__inr);
    if (((~ ((IData)(vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__ini) 
             >> 0xfU)) & (0U != (0xffU & ((IData)(vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__ini) 
                                          >> 7U))))) {
        vlSelf->systolic__DOT__pe_12__DOT__mul_overflow = 1U;
        vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__outi = 0xffU;
        vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__outf = 0xffU;
        vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__outi 
            = (0x7fU & (IData)(vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__outi));
    } else if ((IData)((((IData)(vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__ini) 
                         >> 0xfU) & (~ (IData)((0xffU 
                                                == 
                                                (0xffU 
                                                 & ((IData)(vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__ini) 
                                                    >> 7U)))))))) {
        vlSelf->systolic__DOT__pe_12__DOT__mul_overflow = 1U;
        vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__outi = 0U;
        vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__outf = 0U;
        vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__outi 
            = (0x80U | (IData)(vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__outi));
    } else {
        vlSelf->systolic__DOT__pe_12__DOT__mul_overflow = 0U;
        vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__outi 
            = (0xffU & (IData)(vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__ini));
    }
    vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__ini 
        = (0xffffU & (vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__inr 
                      >> 8U));
    vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__outf 
        = (0xffU & vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__inr);
    if (((~ ((IData)(vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__ini) 
             >> 0xfU)) & (0U != (0xffU & ((IData)(vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__ini) 
                                          >> 7U))))) {
        vlSelf->systolic__DOT__pe_22__DOT__mul_overflow = 1U;
        vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__outi = 0xffU;
        vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__outf = 0xffU;
        vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__outi 
            = (0x7fU & (IData)(vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__outi));
    } else if ((IData)((((IData)(vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__ini) 
                         >> 0xfU) & (~ (IData)((0xffU 
                                                == 
                                                (0xffU 
                                                 & ((IData)(vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__ini) 
                                                    >> 7U)))))))) {
        vlSelf->systolic__DOT__pe_22__DOT__mul_overflow = 1U;
        vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__outi = 0U;
        vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__outf = 0U;
        vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__outi 
            = (0x80U | (IData)(vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__outi));
    } else {
        vlSelf->systolic__DOT__pe_22__DOT__mul_overflow = 0U;
        vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__outi 
            = (0xffU & (IData)(vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__ini));
    }
    vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__outf 
        = (0xffU & (IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__inr));
    vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__ini 
        = (0xffU & ((IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__inr) 
                    >> 8U));
    vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__outi 
        = vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__ini;
    if (vlSelf->rst_n) {
        if (vlSelf->col_num_valid) {
            vlSelf->systolic__DOT__pe_enabled = ((1U 
                                                  == 
                                                  (3U 
                                                   & (IData)(vlSelf->col_num)))
                                                  ? 1U
                                                  : 
                                                 ((2U 
                                                   == 
                                                   (3U 
                                                    & (IData)(vlSelf->col_num)))
                                                   ? 3U
                                                   : 0U));
        }
    } else {
        vlSelf->systolic__DOT__pe_enabled = 3U;
    }
    vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__inr 
        = (0x1ffffU & (VL_EXTENDS_II(17,16, (((IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__outi) 
                                              << 8U) 
                                             | (IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__outf))) 
                       + VL_EXTENDS_II(17,16, (((IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__inb_zoom__DOT__outi) 
                                                << 8U) 
                                               | (IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__inb_zoom__DOT__outf)))));
    vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__inr 
        = (((IData)(vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__outi) 
            << 8U) | (IData)(vlSelf->systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__outf));
    vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__inr 
        = (((IData)(vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__outi) 
            << 8U) | (IData)(vlSelf->systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__outf));
    vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__inr 
        = (0x1ffffU & (VL_EXTENDS_II(17,16, (((IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__outi) 
                                              << 8U) 
                                             | (IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__outf))) 
                       + VL_EXTENDS_II(17,16, (((IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__outi) 
                                                << 8U) 
                                               | (IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__outf)))));
    vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__ini 
        = (0x1ffU & (vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__inr 
                     >> 8U));
    vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outf 
        = (0xffU & vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__inr);
    if ((IData)((0x80U == (0x180U & (IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__ini))))) {
        vlSelf->systolic__DOT__pe_11__DOT__add_overflow = 1U;
        vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outi = 0xffU;
        vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outf = 0xffU;
        vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outi 
            = (0x7fU & (IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outi));
    } else if ((IData)((0x100U == (0x180U & (IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__ini))))) {
        vlSelf->systolic__DOT__pe_11__DOT__add_overflow = 1U;
        vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outi = 0U;
        vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outf = 0U;
        vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outi 
            = (0x80U | (IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outi));
    } else {
        vlSelf->systolic__DOT__pe_11__DOT__add_overflow = 0U;
        vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outi 
            = (0xffU & (IData)(vlSelf->systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__ini));
    }
    vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__outf 
        = (0xffU & (IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__inr));
    vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__ini 
        = (0xffU & ((IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__inr) 
                    >> 8U));
    vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__outi 
        = vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__ini;
    vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__outf 
        = (0xffU & (IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__inr));
    vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__ini 
        = (0xffU & ((IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__inr) 
                    >> 8U));
    vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__outi 
        = vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__ini;
    vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__ini 
        = (0x1ffU & (vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__inr 
                     >> 8U));
    vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outf 
        = (0xffU & vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__inr);
    if ((IData)((0x80U == (0x180U & (IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__ini))))) {
        vlSelf->systolic__DOT__pe_21__DOT__add_overflow = 1U;
        vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outi = 0xffU;
        vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outf = 0xffU;
        vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outi 
            = (0x7fU & (IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outi));
    } else if ((IData)((0x100U == (0x180U & (IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__ini))))) {
        vlSelf->systolic__DOT__pe_21__DOT__add_overflow = 1U;
        vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outi = 0U;
        vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outf = 0U;
        vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outi 
            = (0x80U | (IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outi));
    } else {
        vlSelf->systolic__DOT__pe_21__DOT__add_overflow = 0U;
        vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outi 
            = (0xffU & (IData)(vlSelf->systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__ini));
    }
    vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__inr 
        = (0x1ffffU & (VL_EXTENDS_II(17,16, (((IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__outi) 
                                              << 8U) 
                                             | (IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__outf))) 
                       + VL_EXTENDS_II(17,16, (((IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__inb_zoom__DOT__outi) 
                                                << 8U) 
                                               | (IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__inb_zoom__DOT__outf)))));
    vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__inr 
        = (0x1ffffU & (VL_EXTENDS_II(17,16, (((IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__outi) 
                                              << 8U) 
                                             | (IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__outf))) 
                       + VL_EXTENDS_II(17,16, (((IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__outi) 
                                                << 8U) 
                                               | (IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__outf)))));
    vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__ini 
        = (0x1ffU & (vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__inr 
                     >> 8U));
    vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__outf 
        = (0xffU & vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__inr);
    if ((IData)((0x80U == (0x180U & (IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__ini))))) {
        vlSelf->systolic__DOT__pe_12__DOT__add_overflow = 1U;
        vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__outi = 0xffU;
        vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__outf = 0xffU;
        vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__outi 
            = (0x7fU & (IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__outi));
    } else if ((IData)((0x100U == (0x180U & (IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__ini))))) {
        vlSelf->systolic__DOT__pe_12__DOT__add_overflow = 1U;
        vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__outi = 0U;
        vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__outf = 0U;
        vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__outi 
            = (0x80U | (IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__outi));
    } else {
        vlSelf->systolic__DOT__pe_12__DOT__add_overflow = 0U;
        vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__outi 
            = (0xffU & (IData)(vlSelf->systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__ini));
    }
    vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__ini 
        = (0x1ffU & (vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__inr 
                     >> 8U));
    vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__outf 
        = (0xffU & vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__inr);
    if ((IData)((0x80U == (0x180U & (IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__ini))))) {
        vlSelf->systolic__DOT__pe_22__DOT__add_overflow = 1U;
        vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__outi = 0xffU;
        vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__outf = 0xffU;
        vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__outi 
            = (0x7fU & (IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__outi));
    } else if ((IData)((0x100U == (0x180U & (IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__ini))))) {
        vlSelf->systolic__DOT__pe_22__DOT__add_overflow = 1U;
        vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__outi = 0U;
        vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__outf = 0U;
        vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__outi 
            = (0x80U | (IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__outi));
    } else {
        vlSelf->systolic__DOT__pe_22__DOT__add_overflow = 0U;
        vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__outi 
            = (0xffU & (IData)(vlSelf->systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__ini));
    }
}

void Vsystolic___024root___eval_nba(Vsystolic___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsystolic___024root___eval_nba\n"); );
    // Body
    if (vlSelf->__VnbaTriggered.at(0U)) {
        Vsystolic___024root___nba_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
}

void Vsystolic___024root___eval_triggers__ico(Vsystolic___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vsystolic___024root___dump_triggers__ico(Vsystolic___024root* vlSelf);
#endif  // VL_DEBUG
void Vsystolic___024root___eval_triggers__act(Vsystolic___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vsystolic___024root___dump_triggers__act(Vsystolic___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vsystolic___024root___dump_triggers__nba(Vsystolic___024root* vlSelf);
#endif  // VL_DEBUG

void Vsystolic___024root___eval(Vsystolic___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsystolic___024root___eval\n"); );
    // Init
    CData/*0:0*/ __VicoContinue;
    VlTriggerVec<1> __VpreTriggered;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    vlSelf->__VicoIterCount = 0U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        __VicoContinue = 0U;
        Vsystolic___024root___eval_triggers__ico(vlSelf);
        if (vlSelf->__VicoTriggered.any()) {
            __VicoContinue = 1U;
            if (VL_UNLIKELY((0x64U < vlSelf->__VicoIterCount))) {
#ifdef VL_DEBUG
                Vsystolic___024root___dump_triggers__ico(vlSelf);
#endif
                VL_FATAL_MT("systolic.v", 7, "", "Input combinational region did not converge.");
            }
            vlSelf->__VicoIterCount = ((IData)(1U) 
                                       + vlSelf->__VicoIterCount);
            Vsystolic___024root___eval_ico(vlSelf);
        }
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        __VnbaContinue = 0U;
        vlSelf->__VnbaTriggered.clear();
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            vlSelf->__VactContinue = 0U;
            Vsystolic___024root___eval_triggers__act(vlSelf);
            if (vlSelf->__VactTriggered.any()) {
                vlSelf->__VactContinue = 1U;
                if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                    Vsystolic___024root___dump_triggers__act(vlSelf);
#endif
                    VL_FATAL_MT("systolic.v", 7, "", "Active region did not converge.");
                }
                vlSelf->__VactIterCount = ((IData)(1U) 
                                           + vlSelf->__VactIterCount);
                __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
                vlSelf->__VnbaTriggered.set(vlSelf->__VactTriggered);
                Vsystolic___024root___eval_act(vlSelf);
            }
        }
        if (vlSelf->__VnbaTriggered.any()) {
            __VnbaContinue = 1U;
            if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
                Vsystolic___024root___dump_triggers__nba(vlSelf);
#endif
                VL_FATAL_MT("systolic.v", 7, "", "NBA region did not converge.");
            }
            __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
            Vsystolic___024root___eval_nba(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
void Vsystolic___024root___eval_debug_assertions(Vsystolic___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsystolic___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->rst_n & 0xfeU))) {
        Verilated::overWidthError("rst_n");}
    if (VL_UNLIKELY((vlSelf->x_valid_11 & 0xfeU))) {
        Verilated::overWidthError("x_valid_11");}
    if (VL_UNLIKELY((vlSelf->x_valid_21 & 0xfeU))) {
        Verilated::overWidthError("x_valid_21");}
    if (VL_UNLIKELY((vlSelf->weight_valid_col_1 & 0xfeU))) {
        Verilated::overWidthError("weight_valid_col_1");}
    if (VL_UNLIKELY((vlSelf->weight_valid_col_2 & 0xfeU))) {
        Verilated::overWidthError("weight_valid_col_2");}
    if (VL_UNLIKELY((vlSelf->switch_in & 0xfeU))) {
        Verilated::overWidthError("switch_in");}
    if (VL_UNLIKELY((vlSelf->col_num_valid & 0xfeU))) {
        Verilated::overWidthError("col_num_valid");}
}
#endif  // VL_DEBUG
