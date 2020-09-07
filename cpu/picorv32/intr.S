/*
 * Copyright (C) 2020 Tomas Styblo
 * Copyright (C) 2017, 2019 Ken Rabold, JP Bonn
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include "context_frame.h"
#define IOPORT_CONSOLE 0x30000000

.section      .text
.align 2
.global trap_entry
.global _picorv32_waitirq
.global _picorv32_maskirq
.global _asm_test

/* begin: custom PicoRV32 opcodes */

#define regnum_q0   0
#define regnum_q1   1
#define regnum_q2   2
#define regnum_q3   3

#define regnum_x0   0
#define regnum_x1   1
#define regnum_x2   2
#define regnum_x3   3
#define regnum_x4   4
#define regnum_x5   5
#define regnum_x6   6
#define regnum_x7   7
#define regnum_x8   8
#define regnum_x9   9
#define regnum_x10 10
#define regnum_x11 11
#define regnum_x12 12
#define regnum_x13 13
#define regnum_x14 14
#define regnum_x15 15
#define regnum_x16 16
#define regnum_x17 17
#define regnum_x18 18
#define regnum_x19 19
#define regnum_x20 20
#define regnum_x21 21
#define regnum_x22 22
#define regnum_x23 23
#define regnum_x24 24
#define regnum_x25 25
#define regnum_x26 26
#define regnum_x27 27
#define regnum_x28 28
#define regnum_x29 29
#define regnum_x30 30
#define regnum_x31 31

#define regnum_zero 0
#define regnum_ra   1
#define regnum_sp   2
#define regnum_gp   3
#define regnum_tp   4
#define regnum_t0   5
#define regnum_t1   6
#define regnum_t2   7
#define regnum_s0   8
#define regnum_s1   9
#define regnum_a0  10
#define regnum_a1  11
#define regnum_a2  12
#define regnum_a3  13
#define regnum_a4  14
#define regnum_a5  15
#define regnum_a6  16
#define regnum_a7  17
#define regnum_s2  18
#define regnum_s3  19
#define regnum_s4  20
#define regnum_s5  21
#define regnum_s6  22
#define regnum_s7  23
#define regnum_s8  24
#define regnum_s9  25
#define regnum_s10 26
#define regnum_s11 27
#define regnum_t3  28
#define regnum_t4  29
#define regnum_t5  30
#define regnum_t6  31

// x8 is s0 and also fp
#define regnum_fp   8

#define r_type_insn(_f7, _rs2, _rs1, _f3, _rd, _opc) \
.word (((_f7) << 25) | ((_rs2) << 20) | ((_rs1) << 15) | ((_f3) << 12) | ((_rd) << 7) | ((_opc) << 0))

#define picorv32_getq_insn(_rd, _qs) \
r_type_insn(0b0000000, 0, regnum_ ## _qs, 0b100, regnum_ ## _rd, 0b0001011)

#define picorv32_setq_insn(_qd, _rs) \
r_type_insn(0b0000001, 0, regnum_ ## _rs, 0b010, regnum_ ## _qd, 0b0001011)

#define picorv32_retirq_insn() \
r_type_insn(0b0000010, 0, 0, 0b000, 0, 0b0001011)

#define picorv32_maskirq_insn(_rd, _rs) \
r_type_insn(0b0000011, 0, regnum_ ## _rs, 0b110, regnum_ ## _rd, 0b0001011)

#define picorv32_waitirq_insn(_rd) \
r_type_insn(0b0000100, 0, 0, 0b100, regnum_ ## _rd, 0b0001011)

#define picorv32_timer_insn(_rd, _rs) \
r_type_insn(0b0000101, 0, regnum_ ## _rs, 0b110, regnum_ ## _rd, 0b0001011)

/* end: custom PicoRV32 opcodes */

_asm_test:
    addi	sp,sp,-16
    sw	    ra,12(sp)
    sw	    s0,8(sp)
    addi    s0,sp,16
    
    auipc a0, 0
    mv a1, ra
    mv a2, sp
    
    call    _asm_test_c

    lw	    ra,12(sp)
    lw	    s0,8(sp)
    addi	sp,sp,16
    
    ret

_picorv32_waitirq:
    picorv32_waitirq_insn(a0)
    ret

_picorv32_maskirq:
    picorv32_maskirq_insn(a0, a0)
    ret

.balign 16
trap_entry:
    /* Restore t0 - overwritten in icosoc firmware.S by our mod.
       NO LONGER NEEDED as we use custom PROGADDR_IRQ now
    */
    // picorv32_getq_insn(t0, q2)

    /* Save registers to stack */
    addi sp, sp, -CONTEXT_FRAME_SIZE

    sw s0, s0_OFFSET(sp)
    sw s1, s1_OFFSET(sp)
    sw s2, s2_OFFSET(sp)
    sw s3, s3_OFFSET(sp)
    sw s4, s4_OFFSET(sp)
    sw s5, s5_OFFSET(sp)
    sw s6, s6_OFFSET(sp)
    sw s7, s7_OFFSET(sp)
    sw s8, s8_OFFSET(sp)
    sw s9, s9_OFFSET(sp)
    sw s10, s10_OFFSET(sp)
    sw s11, s11_OFFSET(sp)
    sw ra, ra_OFFSET(sp)
    sw t0, t0_OFFSET(sp)
    sw t1, t1_OFFSET(sp)
    sw t2, t2_OFFSET(sp)
    sw t3, t3_OFFSET(sp)
    sw t4, t4_OFFSET(sp)
    sw t5, t5_OFFSET(sp)
    sw t6, t6_OFFSET(sp)
    sw a0, a0_OFFSET(sp)
    sw a1, a1_OFFSET(sp)
    sw a2, a2_OFFSET(sp)
    sw a3, a3_OFFSET(sp)
    sw a4, a4_OFFSET(sp)
    sw a5, a5_OFFSET(sp)
    sw a6, a6_OFFSET(sp)
    sw a7, a7_OFFSET(sp)

/*
    li t0, IOPORT_CONSOLE
    li t1, 0x32
    sw t1, 0(t0)
    li t1, 0x0A
    sw t1, 0(t0)
*/

/*  Get the return PC and the pending interrupts mask. These arguments are then passed to handle_trap.

    "
    When the IRQ handler is called, the register q0 contains the return address and q1 contains a bitmask of all IRQs to be handled.
    This means one call to the interrupt handler needs to service more than one IRQ when more than one bit is set in q1.
    "
*/
	picorv32_getq_insn(a0, q0)
	picorv32_getq_insn(a1, q1)

    /* Save return PC in stack frame */
    sw a0, pc_OFFSET(sp)

    /*  Get the active thread (could be NULL) */
    lw tp, sched_active_thread

/*
    li t0, IOPORT_CONSOLE
    li t1, 0x33
    sw t1, 0(t0)
    li t1, 0x0A
    sw t1, 0(t0)
*/

    /* Is the active thread NULL? */
    beqz tp, null_thread

/*
    li t1, 0x34
    sw t1, 0(t0)
    li t1, 0x0A
    sw t1, 0(t0)
*/
    /* Save stack pointer of current thread */
    sw sp, SP_OFFSET_IN_THREAD(tp)

null_thread:
/*
    li t1, 0x36
    sw t1, 0(t0)
    li t1, 0x0A
    sw t1, 0(t0)
*/
    /* Switch to ISR stack.  Interrupts are not nested so use fixed
       starting address and just abandon stack when finished. */
    la  sp, _sp_isr

    /*  Call handle_trap with the return PC (a0) and the pending interrupts mask as arguments (a1). */
    call handle_trap

/*
    li t0, IOPORT_CONSOLE
    li t1, 0x37
    sw t1, 0(t0)
    li t1, 0x0A
    sw t1, 0(t0)
*/
    /*  Get the active thread (guaranteed to be non NULL) */
    lw tp, sched_active_thread

    /*  Load the thread SP of scheduled thread */
    lw sp, SP_OFFSET_IN_THREAD(tp)

    /*  Set return PC */
    lw a0, pc_OFFSET(sp)
	picorv32_setq_insn(q0, a0)

    /* Restore registers from stack */
    lw s0, s0_OFFSET(sp)
    lw s1, s1_OFFSET(sp)
    lw s2, s2_OFFSET(sp)
    lw s3, s3_OFFSET(sp)
    lw s4, s4_OFFSET(sp)
    lw s5, s5_OFFSET(sp)
    lw s6, s6_OFFSET(sp)
    lw s7, s7_OFFSET(sp)
    lw s8, s8_OFFSET(sp)
    lw s9, s9_OFFSET(sp)
    lw s10, s10_OFFSET(sp)
    lw s11, s11_OFFSET(sp)
    lw ra, ra_OFFSET(sp)
    lw t0, t0_OFFSET(sp)
    lw t1, t1_OFFSET(sp)
    lw t2, t2_OFFSET(sp)
    lw t3, t3_OFFSET(sp)
    lw t4, t4_OFFSET(sp)
    lw t5, t5_OFFSET(sp)
    lw t6, t6_OFFSET(sp)
    lw a0, a0_OFFSET(sp)
    lw a1, a1_OFFSET(sp)
    lw a2, a2_OFFSET(sp)
    lw a3, a3_OFFSET(sp)
    lw a4, a4_OFFSET(sp)
    lw a5, a5_OFFSET(sp)
    lw a6, a6_OFFSET(sp)
    lw a7, a7_OFFSET(sp)

    addi sp, sp, CONTEXT_FRAME_SIZE

    picorv32_retirq_insn()

