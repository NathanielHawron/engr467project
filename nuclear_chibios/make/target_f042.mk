MCU := cortex-m0

USE_PROCESS_STACKSIZE ?= 0x200
USE_EXCEPTIONS_STACKSIZE ?= 0x200

USE_FPU ?= no
USE_FPU_OPT ?= -mfloat-abi=$(USE_FPU)

STARTUP_MK := $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC/mk/startup_stm32f0xx.mk
HAL_MK := $(CHIBIOS)/os/hal/hal.mk
PLATFORM_MK := $(CHIBIOS)/os/hal/ports/STM32/STM32F0xx/platform.mk
BOARD_MK := $(CHIBIOS)/os/hal/boards/ST_NUCLEO32_F042K6/board.mk
OSAL_MK := $(CHIBIOS)/os/hal/osal/rt-nil/osal.mk
RT_MK := $(CHIBIOS)/os/rt/rt.mk
PORT_MK := $(CHIBIOS)/os/common/ports/ARMv6-M/compilers/GCC/mk/port.mk

LDSCRIPT_NAME := STM32F042x6.ld