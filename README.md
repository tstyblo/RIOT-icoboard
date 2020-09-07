
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

These features are working already:

* kernel threads, messages and mutexes
* newlib (libc for embedded systems)
* VFS filesystem layer
* littlefs2 filesystem - all operations, using the onboard FLASH memory starting at 1 MByte
* MTD block device for the FLASH memory - mtd\_spi\_nor
* SPI for the FLASH memory
* UART for the console interface (RX callbacks/interrupts are not supported)
* STDIO via UART
* timer (core clock frequency)
* GPIO
* shell
* the build process
* the standard programming mechanism (FLASH only - using icoprog - but the binaries run fine from both FLASH and SRAM)
* the following examples have been tested: default, hello-world, filesystem, ...
* the following tests have been tested: thread\_basic, thread\_cooperation, thread\_msg, mutex\_order, periph\_timer, ...

The following may be implemented in the future:

* PWM
* programming mechanism - SRAM (using icoprog)
* support for alternative icoSoC configurations (alternative mod addresses etc.)
* tests

## Documentation

All the new code is in the "icosoc" branch.

You will have to patch the icosoc.py configuration generator and add a new "progaddr\_irq" option to icosoc.cfg,
otherwise the interrupt handler and threads won't work.

You can find more info in the [boards/icosoc/doc.txt](boards/icosoc/doc.txt) file.

## Links

* RIOT OS - the official repository - https://github.com/RIOT-OS/RIOT
* icoBoard - Lattice iCE40HX8K FPGA, IS61WV51216BLL 8 MBit SRAM, S25FL127S 16 MByte FLASH - https://shop.trenz-electronic.de/en/TE0887-03M-icoBoard-Version-1.1-with-8-MBit-SRAM
* icoUSBaseBoard - for connecting the icoBoard to a normal PC via USB - https://shop.trenz-electronic.de/en/TE0889-02-icoUSBaseboard-FTDI-Interfacebasis-for-icoBoard
* icoBoard.org - project homepage and open source tools - http://icoboard.org/
* picorv32 - RISC-V RV32IMC softcore CPU - https://github.com/cliffordwolf/picorv32
* icoSoC - SoC peripherals for picorv32 - https://github.com/cliffordwolf/icotools/tree/master/icosoc
* IceStorm - Lattice iCE40 FPGA open source tools - http://www.clifford.at/icestorm/
* RISC-V GNU Compiler Toolchain - https://github.com/riscv/riscv-gnu-toolchain
* RISC-V Instruction Set Manual 2.2 - https://content.riscv.org/wp-content/uploads/2017/05/riscv-spec-v2.2.pdf
* Jupiter - RISC-V assembler and runtime simulator - https://github.com/andrescv/Jupiter

## License

The new code is licenced under the same conditions as RIOT OS (GNU LGPL version 2.1 as published by the Free Software Foundation).
The new code is maintained by Tomas Styblo (tstyblo AT gmail.com).

