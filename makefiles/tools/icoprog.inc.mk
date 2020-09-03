# Copyright (c) 2020 Tomas Styblo
#
# This file is subject to the terms and conditions of the GNU Lesser
# General Public License v2.1. See the file LICENSE in the top level
# directory for more details.
#

FLASHER = $(RIOTBASE)/boards/icosoc/dist/icoprog-tool.sh
RESET = $(RIOTBASE)/boards/icosoc/dist/icoprog-tool.sh
TERMPROG = $(RIOTBASE)/boards/icosoc/dist/icoprog-tool.sh
FFLAGS = flash
RESET_FLAGS = reset
FLASHFILE=$(ELFFILE)
TERMFLAGS = term

ICOPROG_FLASH_TARGETS = flash flash-only reset term
