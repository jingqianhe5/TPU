// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vsystolic.h for the primary calling header

#ifndef VERILATED_VSYSTOLIC___024ROOT_H_
#define VERILATED_VSYSTOLIC___024ROOT_H_  // guard

#include "verilated.h"

class Vsystolic__Syms;

class Vsystolic___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(clk,0,0);
        VL_IN8(rst_n,0,0);
        VL_IN8(x_valid_11,0,0);
        VL_IN8(x_valid_21,0,0);
        VL_OUT8(z_valid_21,0,0);
        VL_OUT8(z_valid_22,0,0);
        VL_IN8(weight_valid_col_1,0,0);
        VL_IN8(weight_valid_col_2,0,0);
        VL_IN8(switch_in,0,0);
        VL_IN8(col_num_valid,0,0);
        CData/*1:0*/ systolic__DOT__pe_enabled;
        CData/*0:0*/ systolic__DOT__switch_out_11;
        CData/*0:0*/ systolic__DOT__input_out_valid_11;
        CData/*0:0*/ systolic__DOT__switch_out_12;
        CData/*0:0*/ systolic__DOT__input_out_valid_12;
        CData/*0:0*/ systolic__DOT__switch_out_21;
        CData/*0:0*/ systolic__DOT__input_out_valid_21;
        CData/*0:0*/ systolic__DOT__switch_out_22;
        CData/*0:0*/ systolic__DOT__input_out_valid_22;
        CData/*0:0*/ systolic__DOT__pe_11__DOT__overflow_out;
        CData/*0:0*/ systolic__DOT__pe_11__DOT__mul_overflow;
        CData/*0:0*/ systolic__DOT__pe_11__DOT__add_overflow;
        CData/*7:0*/ systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outi;
        CData/*7:0*/ systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__outf;
        CData/*0:0*/ systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__overflow;
        CData/*7:0*/ systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__ini;
        CData/*7:0*/ systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__outi;
        CData/*7:0*/ systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__outf;
        CData/*0:0*/ systolic__DOT__pe_11__DOT__adder__DOT__inb_zoom__DOT__overflow;
        CData/*7:0*/ systolic__DOT__pe_11__DOT__adder__DOT__inb_zoom__DOT__ini;
        CData/*7:0*/ systolic__DOT__pe_11__DOT__adder__DOT__inb_zoom__DOT__outi;
        CData/*7:0*/ systolic__DOT__pe_11__DOT__adder__DOT__inb_zoom__DOT__outf;
        CData/*7:0*/ systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outi;
        CData/*7:0*/ systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__outf;
        CData/*0:0*/ systolic__DOT__pe_12__DOT__input_out_valid;
        CData/*0:0*/ systolic__DOT__pe_12__DOT__overflow_out;
        CData/*0:0*/ systolic__DOT__pe_12__DOT__mul_overflow;
        CData/*0:0*/ systolic__DOT__pe_12__DOT__add_overflow;
        CData/*7:0*/ systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__outi;
        CData/*7:0*/ systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__outf;
        CData/*0:0*/ systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__overflow;
        CData/*7:0*/ systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__ini;
        CData/*7:0*/ systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__outi;
        CData/*7:0*/ systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__outf;
        CData/*0:0*/ systolic__DOT__pe_12__DOT__adder__DOT__inb_zoom__DOT__overflow;
        CData/*7:0*/ systolic__DOT__pe_12__DOT__adder__DOT__inb_zoom__DOT__ini;
        CData/*7:0*/ systolic__DOT__pe_12__DOT__adder__DOT__inb_zoom__DOT__outi;
        CData/*7:0*/ systolic__DOT__pe_12__DOT__adder__DOT__inb_zoom__DOT__outf;
        CData/*7:0*/ systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__outi;
        CData/*7:0*/ systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__outf;
        CData/*0:0*/ systolic__DOT__pe_21__DOT__overflow_out;
        CData/*0:0*/ systolic__DOT__pe_21__DOT__mul_overflow;
        CData/*0:0*/ systolic__DOT__pe_21__DOT__add_overflow;
        CData/*7:0*/ systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outi;
        CData/*7:0*/ systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__outf;
        CData/*0:0*/ systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__overflow;
        CData/*7:0*/ systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__ini;
        CData/*7:0*/ systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__outi;
        CData/*7:0*/ systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__outf;
        CData/*0:0*/ systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__overflow;
        CData/*7:0*/ systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__ini;
        CData/*7:0*/ systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__outi;
        CData/*7:0*/ systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__outf;
        CData/*7:0*/ systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outi;
    };
    struct {
        CData/*7:0*/ systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__outf;
        CData/*0:0*/ systolic__DOT__pe_22__DOT__overflow_out;
        CData/*0:0*/ systolic__DOT__pe_22__DOT__mul_overflow;
        CData/*0:0*/ systolic__DOT__pe_22__DOT__add_overflow;
        CData/*7:0*/ systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__outi;
        CData/*7:0*/ systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__outf;
        CData/*0:0*/ systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__overflow;
        CData/*7:0*/ systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__ini;
        CData/*7:0*/ systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__outi;
        CData/*7:0*/ systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__outf;
        CData/*0:0*/ systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__overflow;
        CData/*7:0*/ systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__ini;
        CData/*7:0*/ systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__outi;
        CData/*7:0*/ systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__outf;
        CData/*7:0*/ systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__outi;
        CData/*7:0*/ systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__outf;
        CData/*0:0*/ __Vtrigrprev__TOP__clk;
        CData/*0:0*/ __Vtrigrprev__TOP__rst_n;
        CData/*0:0*/ __VactContinue;
        VL_IN16(x_11,15,0);
        VL_IN16(x_21,15,0);
        VL_OUT16(z_21,15,0);
        VL_OUT16(z_22,15,0);
        VL_IN16(w_11,15,0);
        VL_IN16(w_12,15,0);
        VL_IN16(col_num,15,0);
        SData/*15:0*/ systolic__DOT__weight_out_11;
        SData/*15:0*/ systolic__DOT__psum_out_11;
        SData/*15:0*/ systolic__DOT__input_out_11;
        SData/*15:0*/ systolic__DOT__weight_out_12;
        SData/*15:0*/ systolic__DOT__psum_out_12;
        SData/*15:0*/ systolic__DOT__input_out_12;
        SData/*15:0*/ systolic__DOT__weight_out_21;
        SData/*15:0*/ systolic__DOT__psum_out_21;
        SData/*15:0*/ systolic__DOT__input_out_21;
        SData/*15:0*/ systolic__DOT__weight_out_22;
        SData/*15:0*/ systolic__DOT__psum_out_22;
        SData/*15:0*/ systolic__DOT__input_out_22;
        SData/*15:0*/ systolic__DOT__pe_11__DOT__weight_in_active;
        SData/*15:0*/ systolic__DOT__pe_11__DOT__weight_in_buffer;
        SData/*15:0*/ systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__ini;
        SData/*15:0*/ systolic__DOT__pe_11__DOT__adder__DOT__ina_zoom__DOT__inr;
        SData/*8:0*/ systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__ini;
        SData/*15:0*/ systolic__DOT__pe_12__DOT__input_out;
        SData/*15:0*/ systolic__DOT__pe_12__DOT__weight_in_active;
        SData/*15:0*/ systolic__DOT__pe_12__DOT__weight_in_buffer;
        SData/*15:0*/ systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__ini;
        SData/*15:0*/ systolic__DOT__pe_12__DOT__adder__DOT__ina_zoom__DOT__inr;
        SData/*8:0*/ systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__ini;
        SData/*15:0*/ systolic__DOT__pe_21__DOT__weight_in_active;
        SData/*15:0*/ systolic__DOT__pe_21__DOT__weight_in_buffer;
        SData/*15:0*/ systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__ini;
        SData/*15:0*/ systolic__DOT__pe_21__DOT__adder__DOT__ina_zoom__DOT__inr;
        SData/*15:0*/ systolic__DOT__pe_21__DOT__adder__DOT__inb_zoom__DOT__inr;
        SData/*8:0*/ systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__ini;
        SData/*15:0*/ systolic__DOT__pe_22__DOT__input_out;
        SData/*15:0*/ systolic__DOT__pe_22__DOT__weight_in_active;
        SData/*15:0*/ systolic__DOT__pe_22__DOT__weight_in_buffer;
        SData/*15:0*/ systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__ini;
        SData/*15:0*/ systolic__DOT__pe_22__DOT__adder__DOT__ina_zoom__DOT__inr;
        SData/*15:0*/ systolic__DOT__pe_22__DOT__adder__DOT__inb_zoom__DOT__inr;
        SData/*8:0*/ systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__ini;
        IData/*31:0*/ systolic__DOT__pe_11__DOT__mult__DOT__res;
        IData/*23:0*/ systolic__DOT__pe_11__DOT__mult__DOT__res_zoom__DOT__inr;
    };
    struct {
        IData/*16:0*/ systolic__DOT__pe_11__DOT__adder__DOT__res_zoom__DOT__inr;
        IData/*31:0*/ systolic__DOT__pe_12__DOT__mult__DOT__res;
        IData/*23:0*/ systolic__DOT__pe_12__DOT__mult__DOT__res_zoom__DOT__inr;
        IData/*16:0*/ systolic__DOT__pe_12__DOT__adder__DOT__res_zoom__DOT__inr;
        IData/*31:0*/ systolic__DOT__pe_21__DOT__mult__DOT__res;
        IData/*23:0*/ systolic__DOT__pe_21__DOT__mult__DOT__res_zoom__DOT__inr;
        IData/*16:0*/ systolic__DOT__pe_21__DOT__adder__DOT__res_zoom__DOT__inr;
        IData/*31:0*/ systolic__DOT__pe_22__DOT__mult__DOT__res;
        IData/*23:0*/ systolic__DOT__pe_22__DOT__mult__DOT__res_zoom__DOT__inr;
        IData/*16:0*/ systolic__DOT__pe_22__DOT__adder__DOT__res_zoom__DOT__inr;
        IData/*31:0*/ __VstlIterCount;
        IData/*31:0*/ __VicoIterCount;
        IData/*31:0*/ __VactIterCount;
        VlUnpacked<CData/*0:0*/, 3> __Vm_traceActivity;
    };
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vsystolic__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vsystolic___024root(Vsystolic__Syms* symsp, const char* v__name);
    ~Vsystolic___024root();
    VL_UNCOPYABLE(Vsystolic___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);


#endif  // guard
