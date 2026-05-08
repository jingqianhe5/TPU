// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vsystolic.h"
#include "Vsystolic__Syms.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vsystolic::Vsystolic(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vsystolic__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst_n{vlSymsp->TOP.rst_n}
    , x_valid_11{vlSymsp->TOP.x_valid_11}
    , x_valid_21{vlSymsp->TOP.x_valid_21}
    , z_valid_21{vlSymsp->TOP.z_valid_21}
    , z_valid_22{vlSymsp->TOP.z_valid_22}
    , weight_valid_col_1{vlSymsp->TOP.weight_valid_col_1}
    , weight_valid_col_2{vlSymsp->TOP.weight_valid_col_2}
    , switch_in{vlSymsp->TOP.switch_in}
    , col_num_valid{vlSymsp->TOP.col_num_valid}
    , x_11{vlSymsp->TOP.x_11}
    , x_21{vlSymsp->TOP.x_21}
    , z_21{vlSymsp->TOP.z_21}
    , z_22{vlSymsp->TOP.z_22}
    , w_11{vlSymsp->TOP.w_11}
    , w_12{vlSymsp->TOP.w_12}
    , col_num{vlSymsp->TOP.col_num}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vsystolic::Vsystolic(const char* _vcname__)
    : Vsystolic(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vsystolic::~Vsystolic() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vsystolic___024root___eval_debug_assertions(Vsystolic___024root* vlSelf);
#endif  // VL_DEBUG
void Vsystolic___024root___eval_static(Vsystolic___024root* vlSelf);
void Vsystolic___024root___eval_initial(Vsystolic___024root* vlSelf);
void Vsystolic___024root___eval_settle(Vsystolic___024root* vlSelf);
void Vsystolic___024root___eval(Vsystolic___024root* vlSelf);

void Vsystolic::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vsystolic::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vsystolic___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vsystolic___024root___eval_static(&(vlSymsp->TOP));
        Vsystolic___024root___eval_initial(&(vlSymsp->TOP));
        Vsystolic___024root___eval_settle(&(vlSymsp->TOP));
    }
    // MTask 0 start
    VL_DEBUG_IF(VL_DBG_MSGF("MTask0 starting\n"););
    Verilated::mtaskId(0);
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vsystolic___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vsystolic::eventsPending() { return false; }

uint64_t Vsystolic::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vsystolic::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vsystolic___024root___eval_final(Vsystolic___024root* vlSelf);

VL_ATTR_COLD void Vsystolic::final() {
    Vsystolic___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vsystolic::hierName() const { return vlSymsp->name(); }
const char* Vsystolic::modelName() const { return "Vsystolic"; }
unsigned Vsystolic::threads() const { return 1; }
std::unique_ptr<VerilatedTraceConfig> Vsystolic::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vsystolic___024root__trace_init_top(Vsystolic___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vsystolic___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vsystolic___024root*>(voidSelf);
    Vsystolic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->scopeEscape(' ');
    tracep->pushNamePrefix(std::string{vlSymsp->name()} + ' ');
    Vsystolic___024root__trace_init_top(vlSelf, tracep);
    tracep->popNamePrefix();
    tracep->scopeEscape('.');
}

VL_ATTR_COLD void Vsystolic___024root__trace_register(Vsystolic___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vsystolic::trace(VerilatedVcdC* tfp, int levels, int options) {
    if (tfp->isOpen()) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vsystolic::trace()' shall not be called after 'VerilatedVcdC::open()'.");
    }
    if (false && levels && options) {}  // Prevent unused
    tfp->spTrace()->addModel(this);
    tfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    Vsystolic___024root__trace_register(&(vlSymsp->TOP), tfp->spTrace());
}
