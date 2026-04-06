PROJECT = blink
CHIBIOS = ../ChibiOS
CONFDIR = ./cfg
BUILDDIR = ./build
DEPDIR = ./.dep

USE_OPT = -O2 -ggdb --specs=nano.specs
USE_COPT =
USE_CPPOPT = -fno-rtti
USE_LINK_GC = yes
USE_LTO = yes
USE_VERBOSE_COMPILE = no
USE_SMART_BUILD = yes

USE_PROCESS_STACKSIZE = 0x400
USE_EXCEPTIONS_STACKSIZE = 0x400

MCU = cortex-m33
USE_FPU = hard
USE_FPU_OPT = -mfloat-abi=$(USE_FPU) -mfpu=fpv5-sp-d16

include $(CHIBIOS)/os/license/license.mk
include $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC/mk/startup_stm32h5xx.mk
include $(CHIBIOS)/os/common/oop/oop.mk
include $(CHIBIOS)/os/common/utils/utils.mk
include $(CHIBIOS)/os/xhal/xhal.mk
include $(CHIBIOS)/os/xhal/ports/STM32/STM32H5xx/platform.mk
include $(CHIBIOS)/os/hal/boards/ST_NUCLEO144_H563ZI/board.mk
include $(CHIBIOS)/os/hal/osal/rt-nil/osal.mk
include $(CHIBIOS)/os/rt/rt.mk
include $(CHIBIOS)/os/common/ports/ARMv8-M-ML-ALT/compilers/GCC/mk/port.mk

LDSCRIPT = $(STARTUPLD)/STM32H563xI.ld

CSRC = $(ALLCSRC) main.c
CPPSRC = $(ALLCPPSRC)
ASMSRC = $(ALLASMSRC)
ASMXSRC = $(ALLXASMSRC)

INCDIR = $(CONFDIR) $(ALLINC)

CWARN = -Wall -Wextra -Wundef -Wstrict-prototypes -Wcast-align=strict
CPPWARN = -Wall -Wextra -Wundef

UDEFS = -DOOP_USE_LEGACY
UADEFS =
UINCDIR =
ULIBDIR =
ULIBS =

RULESPATH = $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC/mk
include $(RULESPATH)/arm-none-eabi.mk
include $(RULESPATH)/rules.mk
