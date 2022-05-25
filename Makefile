
EXE = main

${EXE}: main.cpp computation.hpp accelerator.h system.h system.cpp fpga.h
	g++ --std=c++14 main.cpp system.cpp -o $@

clean:
	rm -rf ${EXE}
