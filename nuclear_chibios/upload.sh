#!/bin/bash

PROGRAMMER_PATH=$HOME/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin/STM32_Programmer_CLI

PORT=SWD
PROGRAM_FILE=build/nuclear_chibios.elf

if [[ -f "$PROGRAM_FILE" ]]; then
    ls -l "$PROGRAM_FILE"
    set -x
    "$PROGRAMMER_PATH" -vb 2 -c port="$PORT" -w "$PROGRAM_FILE" 0x08000000 -v -rst
else
    echo "PROGRAM_FILE does not exist"
fi
