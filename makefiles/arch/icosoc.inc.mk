# Copyright (c) 2020 Tomas Styblo
#
# This file is subject to the terms and conditions of the GNU Lesser
# General Public License v2.1. See the file LICENSE in the top level
# directory for more details.
#

# Target architecture for the build.
TARGET_ARCH ?= riscv32-unknown-elf

# define build specific options
CFLAGS_CPU   = -Os -march=rv32i --std=gnu99 -Os -Wall -Wno-error -ffreestanding -lgcc
CFLAGS_LINK  = -nostartfiles
CFLAGS_DBG  ?= 
CFLAGS_OPT  ?= -Os

LINKFLAGS += -L$(RIOTCPU)/$(CPU)/ldscripts
LINKER_SCRIPT ?= $(CPU_MODEL).ld
LINKFLAGS += -T$(LINKER_SCRIPT)

CFLAGS += $(CFLAGS_CPU) $(CFLAGS_DBG) $(CFLAGS_OPT) $(CFLAGS_LINK)
ASFLAGS += $(CFLAGS_CPU) $(CFLAGS_DBG)
# export linker flags
LINKFLAGS += $(CFLAGS_CPU) $(CFLAGS_LINK) $(CFLAGS_DBG) $(CFLAGS_OPT) -Wl,-Bstatic -lgcc
