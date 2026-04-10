MCU := cortex-m33

USE_PROCESS_STACKSIZE ?= 0x400
USE_EXCEPTIONS_STACKSIZE ?= 0x400

USE_FPU ?= hard
USE_FPU_OPT ?= -mfloat-abi=$(USE_FPU) -mfpu=fpv5-sp-d16

STARTUP_MK := $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC/mk/startup_stm32h5xx.mk
HAL_MK := $(CHIBIOS)/os/xhal/xhal.mk
PLATFORM_MK := $(CHIBIOS)/os/xhal/ports/STM32/STM32H5xx/platform.mk
BOARD_MK := $(CHIBIOS)/os/hal/boards/ST_NUCLEO144_H563ZI/board.mk
OSAL_MK := $(CHIBIOS)/os/hal/osal/rt-nil/osal.mk
RT_MK := $(CHIBIOS)/os/rt/rt.mk
PORT_MK := $(CHIBIOS)/os/common/ports/ARMv8-M-ML-ALT/compilers/GCC/mk/port.mk

LDSCRIPT_NAME := STM32H563xI.ld