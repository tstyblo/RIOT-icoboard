
> 
> **The official RIOT OS repositoy is at: https://github.com/RIOT-OS/RIOT**
>

# RIOT OS for icoBoard FPGA with picorv32 RISC-V core

## Overview

This experimental RIOT OS repository has been created in order to port the RIOT OS embedded operating system to the icoBoard FPGA board running the picorv32 RISC-V softcore CPU.

The board is based on the Lattice iCE40HX FPGA device, which is fully supported by open source tools. 

You'll also need the icoUSBaseBoard adapter board so that you can connect the icoBoard to a normal PC via USB (unless you want to program it manually using a Raspberry Pi).

The FPGA device must be programmed with the icoSoC platform. The platform provides the picorv32 RISC-V softcore CPU written in Verilog, plus some basic peripherals (interrupt controller, SRAM interface, UART, GPIO, PWM, bootloader firmware). 

## Status

At the momemt this code is an experimental alpha version intended for testing. It is written in C and RISC-V assembly.

As of September 2020 these features are already working:

* threads
* newlib (libc for embedded systems)
* VFS filesystem layer
* stdio-uart
* shell
* UART (RX is implemented without interrupts as the icoSoC UART does not currently support them)
* the build process
* the standard programming mechanism (FLASH only - using icoprog - but the binaries run fine from both FLASH and SRAM)
* the following examples have been tested: default, hello-world, filesystem
* the following tests have been tested: thread_basic, thread_cooperation, thread_msg

The following should be implemented in the near future:

* GPIO
* SAUL GPIO
* PWM
* SAUL PWM
* FLASH MTD device for VFS
* SRAM MTD device for VFS
* programming mechanism - SRAM (using icoprog)
* support for alternative icoSoC configurations (alternative mod addresses etc.)
* tests

## Links

* RIOT OS - the official repository (without any icoBoard support) - https://github.com/RIOT-OS/RIOT
* icoBoard - Lattice iCE40HX FPGA board - https://shop.trenz-electronic.de/en/TE0887-03M-icoBoard-Version-1.1-with-8-MBit-SRAM
* icoUSBaseBoard - for connecting the icoBoard to a normal PC via USB - https://shop.trenz-electronic.de/en/TE0889-02-icoUSBaseboard-FTDI-Interfacebasis-for-icoBoard
* icoBoard.org - project homepage and open source tools - http://icoboard.org/
* picorv32 - RISC-V RV32IMC softcore CPU - https://github.com/cliffordwolf/picorv32
* icoSoC - SoC peripherals for picorv32 - https://github.com/cliffordwolf/icotools/tree/master/icosoc
* IceStorm - Lattice iCE40 FPGA open source tools - http://www.clifford.at/icestorm/
* RISC-V GNU Compiler Toolchain - https://github.com/riscv/riscv-gnu-toolchain
* RISC-V Instruction Set Manual 2.2 - https://content.riscv.org/wp-content/uploads/2017/05/riscv-spec-v2.2.pdf
* Jupiter - RISC-V assembler and runtime simulator - https://github.com/andrescv/Jupiter
* SparkFun RED-V RedBoard - SiFive RISC-V FE310 MCU SoC - https://www.sparkfun.com/products/15594

## Documentation

You'll have to patch the icosoc firmware first, otherwise the interrupt handler and threads won't work.

You can find more info in the [boards/icosoc/doc.txt](boards/icosoc/doc.txt) file.

## License

The new code is licenced under the same conditions as RIOT OS (GNU LGPL version 2.1 as published by the Free Software Foundation).
The new code is maintained by Tomas Styblo (tstyblo@gmail.com).

