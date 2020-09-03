#!/bin/bash

# Copyright (c) 2020 Tomas Styblo
#
# This file is subject to the terms and conditions of the GNU Lesser
# General Public License v2.1. See the file LICENSE in the top level
# directory for more details.
#

#
# now comes the actual actions
#
do_flash() {
    echo "flasher.sh - ELFFILE: $ELFFILE"
    echo "flasher.sh - HEXFILE: $HEXFILE"
    echo "flasher.sh - BINFILE: $BINFILE"

    echo "Creating verilog HEX file: $ELFFILE -> $HEXFILE"
    /opt/riscv32ic/bin/riscv32-unknown-elf-objcopy -O verilog "$ELFFILE" "$HEXFILE"

    echo "Writing BIN file to SRAM: $BINFILE"
    icoprog -O8 -f < $BINFILE
}

#
# parameter dispatching
#
BINFILE=${ELFFILE/.elf/.bin}

ACTION="$1"
shift # pop $1 from $@

case "${ACTION}" in
  flash)
    echo "### Flashing Target ###"
    do_flash "$@"
    ;;
  reset)
    echo "### Resetting Target ###"
    icoprog -b
    sleep 5 # give it some time to boot after a reset
    ;;
  term)
    echo "### Connecting to the console ###"
    icoprog -c2
    ;;
  *)
    echo "Usage: $0 flash|reset|term"
    exit 2
    ;;
esac
