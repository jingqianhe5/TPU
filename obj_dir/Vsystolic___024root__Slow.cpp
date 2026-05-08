// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsystolic.h for the primary calling header

#include "verilated.h"

#include "Vsystolic__Syms.h"
#include "Vsystolic___024root.h"

void Vsystolic___024root___ctor_var_reset(Vsystolic___024root* vlSelf);

Vsystolic___024root::Vsystolic___024root(Vsystolic__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vsystolic___024root___ctor_var_reset(this);
}

void Vsystolic___024root::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vsystolic___024root::~Vsystolic___024root() {
}
