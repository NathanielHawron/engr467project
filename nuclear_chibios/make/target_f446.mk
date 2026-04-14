##############################################################################
# Target: STM32F446RE on ST_NUCLEO64_F446RE
##############################################################################

MCU := cortex-m4

USE_PROCESS_STACKSIZE ?= 0x400
USE_EXCEPTIONS_STACKSIZE ?= 0x400

# Matches the current ChibiOS F446RE demo defaults.
USE_FPU ?= no
USE_FPU_OPT ?= -mfloat-abi=$(USE_FPU) -mfpu=fpv4-sp-d16

STARTUP_MK := $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC/mk/startup_stm32f4xx.mk
HAL_MK     := $(CHIBIOS)/os/hal/hal.mk
PLATFORM_MK:= $(CHIBIOS)/os/hal/ports/STM32/STM32F4xx/platform.mk
BOARD_MK   := $(CHIBIOS)/os/hal/boards/ST_NUCLEO64_F446RE/board.mk
OSAL_MK    := $(CHIBIOS)/os/hal/osal/rt-nil/osal.mk
RT_MK      := $(CHIBIOS)/os/rt/rt.mk
PORT_MK    := $(CHIBIOS)/os/common/ports/ARMv7-M/compilers/GCC/mk/port.mk

LDSCRIPT_NAME := STM32F446xE.ld
