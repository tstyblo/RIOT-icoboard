
> 
> **The official RIOT OS repositoy is at: https://github.com/RIOT-OS/RIOT**
>

# RIOT OS for icoBoard FPGA with picorv32 RISC-V core

## Overview

This experimental RIOT OS repository has been created in order to port the RIOT OS embedded operating system to the icoBoard FPGA board running the picorv32 RISC-V softcore CPU.

The FPGA board is based on the Lattice iCE40HX device, which is fully supported by open source tools.

The FPGA device must be programmed with the icoSoC platform. The platform provides the picorv32 RISC-V softcore CPU written in Verilog, plus some basic peripherals (interrupt controller, UART, GPIO, PWM, bootloader firmware). 

## Status

At the momemt this code is an alpha version intended for testing. It is written in C and RISC-V assembly.

As of September 2020 these features are already working:

* threads
* newlib (libc for embedded systems)
* VFS filesystem layer
* stdio-uart
* shell
* UART (RX is implemented without interrupts as the icoSoC UART does not currently support them)
* the build process
* the programming process (both SRAM and FLASH - using icoprog)
* the following examples have been tested: default, hello-world, filesystem

The following should be implemented in the near future:

* GPIO
* SAUL GPIO
* PWM
* SAUL PWM
* support for alternative icoSoC configurations (alternative mod addresses etc.)
* tests

## Links

* RIOT OS - the official repository (currently without any icoBoard or FPGA support) - https://github.com/RIOT-OS/RIOT
* icoBoard - Lattice iCE40HX FPGA board - http://icoboard.org/
* picorv32 - RISC-V RV32IMC softcore CPU - https://github.com/cliffordwolf/picorv32
* icoSoC - SoC peripherals for picorv32 - https://github.com/cliffordwolf/icotools/tree/master/icosoc
* IceStorm - Lattice iCE40 FPGA open source tools - http://www.clifford.at/icestorm/
* RISC-V GNU Compiler Toolchain - https://github.com/riscv/riscv-gnu-toolchain
* RISC-V Instruction Set Manual 2.2 - https://content.riscv.org/wp-content/uploads/2017/05/riscv-spec-v2.2.pdf
* Jupiter - RISC-V assembler and runtime simulator - https://github.com/andrescv/Jupiter
* SparkFun RED-V RedBoard - SiFive RISC-V FE310 SoC - https://www.sparkfun.com/products/15594

The new code is licenced under the same conditions as RIOT OS (GNU LGPL version 2.1 as published by the Free Software Foundation).

Created and maintained by Tomas Styblo (tstyblo@gmail.com).

