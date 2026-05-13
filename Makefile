# ==========================================
# DE1-SoC tiny TPU XOR Verilator simulation
# ==========================================

TOP      = de1_soc_tiny_tpu_xor_top
CPP_SRCS = main.cpp
WAVE     = de1_soc_tiny_tpu_xor_top.vcd

V_SRCS = \
	de1_soc_tiny_tpu_xor_top.v \
	tpu.v \
	unified_buffer.sv \
	gradient_descent.sv \
	vpu.v \
	systolic.v \
	pe.v \
	bias_centre.v \
	bias_unit.v \
	leaky_relu_centre.v \
	leaky_relu_unit.v \
	loss_centre.v \
	loss_unit.v \
	leaky_relu_derivative_centre.v \
	leaky_relu_derivative_unit.v \
	fxp_add.v \
	fxp_addsub.v \
	fxp_mul.v \
	fxp_zoom.v

ISA_TOP      = tpu_isa_confreg
ISA_CPP_SRCS = tpu_isa_confreg_sim.cpp
ISA_WAVE     = tpu_isa_confreg_sim.vcd

ISA_V_SRCS = \
	tpu_isa_confreg.v \
	decode.v \
	tpu.v \
	unified_buffer.sv \
	gradient_descent.sv \
	vpu.v \
	systolic.v \
	pe.v \
	bias_centre.v \
	bias_unit.v \
	leaky_relu_centre.v \
	leaky_relu_unit.v \
	loss_centre.v \
	loss_unit.v \
	leaky_relu_derivative_centre.v \
	leaky_relu_derivative_unit.v \
	fxp_add.v \
	fxp_addsub.v \
	fxp_mul.v \
	fxp_zoom.v

VFLAGS = -Wall --trace --cc $(V_SRCS) --top-module $(TOP) \
	-GDEBOUNCE_LIMIT=4 \
	-Wno-WIDTHTRUNC -Wno-WIDTHEXPAND -Wno-BLKLOOPINIT \
	-Wno-EOFNEWLINE -Wno-PINCONNECTEMPTY -Wno-VARHIDDEN \
	-Wno-UNUSEDSIGNAL -Wno-BLKSEQ -Wno-SYNCASYNCNET\
	--exe $(CPP_SRCS) --build

ISA_VFLAGS = -Wall --trace --cc $(ISA_V_SRCS) --top-module $(ISA_TOP) \
	-Wno-WIDTHTRUNC -Wno-WIDTHEXPAND -Wno-BLKLOOPINIT \
	-Wno-EOFNEWLINE -Wno-PINCONNECTEMPTY -Wno-VARHIDDEN \
	-Wno-UNUSEDSIGNAL -Wno-BLKSEQ -Wno-SYNCASYNCNET \
	-Wno-TIMESCALEMOD \
	--exe $(ISA_CPP_SRCS) --build

.PHONY: all build run wave isa-build isa-run isa-wave isa clean

all: build run

build:
	verilator $(VFLAGS)

run:
	./obj_dir/V$(TOP)

wave:
	gtkwave $(WAVE) &

isa-build:
	verilator $(ISA_VFLAGS)

isa-run:
	./obj_dir/V$(ISA_TOP)

isa-wave:
	gtkwave $(ISA_WAVE) &

isa: isa-build isa-run

clean:
	rm -rf obj_dir
	rm -f *.vcd
