# ==========================================
# 脉动阵列 Verilator 仿真 Makefile
# ==========================================

# 1. 定义变量
V_SRCS   = systolic.v
CPP_SRCS = main.cpp
TOP      = systolic
WAVE     = systolic.vcd

# Verilator 编译参数 (开启所有警告, 开启波形追踪, 编译为C++, 指定可执行文件并自动build)
VFLAGS   = -Wall --trace --cc $(V_SRCS) --exe $(CPP_SRCS) --build

# 声明伪目标 (防止与同名文件冲突)
.PHONY: all build run wave clean

# ==========================================
# 2. 目标规则
# ==========================================

# 默认目标: 直接敲 `make` 就会执行 build 和 run
all: build run

# 编译阶段: 调用 Verilator 将 Verilog 翻译为 C++ 并编译出可执行文件
build:
	verilator $(VFLAGS)

# 运行阶段: 执行生成的二进制文件，产生波形
run:
	./obj_dir/V$(TOP)

# 查看波形: 后台打开 GTKWave
wave:
	gtkwave $(WAVE) &

# 清理阶段: 核心需求，删掉编译产生的文件夹和波形文件
clean:
	rm -rf obj_dir
	rm -f *.vcd