/*
 * Copyright (C) 2020 Tomas Styblo
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include "newlib.h"

#=========================================================================
# crt0.S : Entry point for RISC-V user programs (newlib)
#  - modified for picorv32 / icoSoC
#=========================================================================

#define regnum_x0   0
#define regnum_zero 0

#define r_type_insn(_f7, _rs2, _rs1, _f3, _rd, _opc) \
.word (((_f7) << 25) | ((_rs2) << 20) | ((_rs1) << 15) | ((_f3) << 12) | ((_rd) << 7) | ((_opc) << 0))

#define picorv32_maskirq_insn(_rd, _rs) \
r_type_insn(0b0000011, 0, regnum_ ## _rs, 0b110, regnum_ ## _rd, 0b0001011)

.section .init 
.global _start

_start:
/*
    li t0, 0x30000000
    srli t1, sp, 24
    sw t1, 0(t0)
    li t0, 0x30000000
    srli t1, sp, 16
    sw t1, 0(t0)
    li t0, 0x30000000
    srli t1, sp, 8
    sw t1, 0(t0)
    li t0, 0x30000000
    mv t1, sp
    sw t1, 0(t0)

    li t1, 0x0A
    sw t1, 0(t0)
*/

  # Initialize global pointer
.option push
.option norelax
1:auipc gp, %pcrel_hi(__global_pointer$)
  addi  gp, gp, %pcrel_lo(1b)
.option pop

  # initialize interrupt vector
  picorv32_maskirq_insn(x0, x0)
  la      t1, trap_entry
  sw      t1, 8(zero)

  # Clear the bss segment
  la      a0, _edata
  la      a2, _end
  sub     a2, a2, a0
  li      a1, 0
  call    memset
#ifdef _LITE_EXIT
  # Make reference to atexit weak to avoid unconditionally pulling in
  # support code.  Refer to comments in __atexit.c for more details.
  .weak   atexit
  la      a0, atexit
  beqz    a0, .Lweak_atexit
  .weak   __libc_fini_array
#endif

  la      a0, __libc_fini_array   # Register global termination functions
  call    atexit                  #  to be called upon exit
#ifdef _LITE_EXIT
.Lweak_atexit:
#endif
  call    __libc_init_array       # Run global initialization functions

  //lw      a0, 0(sp)                  # a0 = argc
  //addi    a1, sp, __SIZEOF_POINTER__ # a1 = argv
  //li      a2, 0                      # a2 = envp = NULL

  call    board_init
  tail    exit
