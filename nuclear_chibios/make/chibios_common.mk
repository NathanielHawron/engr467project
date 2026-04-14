##############################################################################
# Build global options
##############################################################################

USE_OPT ?= -Os -ggdb -fomit-frame-pointer -falign-functions=16
USE_COPT ?=
USE_CPPOPT ?= -fno-rtti
USE_LINK_GC ?= yes
USE_LDOPT ?= -lm
USE_LTO ?= yes
USE_VERBOSE_COMPILE ?= no
USE_SMART_BUILD ?= yes

CWARN ?= -Wall -Wextra -Wundef -Wstrict-prototypes
CPPWARN ?= -Wall -Wextra -Wundef

UADEFS ?=
ULIBDIR ?=
ULIBS ?=

##############################################################################
# Imported source files and paths
##############################################################################

include $(CHIBIOS)/os/license/license.mk
include $(STARTUP_MK)
include $(HAL_MK)
include $(PLATFORM_MK)
include $(BOARD_MK)
include $(OSAL_MK)
include $(RT_MK)
include $(PORT_MK)
include $(CHIBIOS)/tools/mk/autobuild.mk
include $(CHIBIOS)/os/common/oop/oop.mk

LDSCRIPT := $(STARTUPLD)/$(LDSCRIPT_NAME)

# Optional test framework.
# Uncomment if needed.
# include $(CHIBIOS)/os/test/test.mk
# include $(CHIBIOS)/test/rt/rt_test.mk
# include $(CHIBIOS)/test/oslib/oslib_test.mk

##############################################################################
# Final source lists
##############################################################################

CSRC += $(ALLCSRC)
CPPSRC += $(ALLCPPSRC)
ASMSRC := $(ALLASMSRC)
ASMXSRC := $(ALLXASMSRC)

INCDIR := $(CONFDIR) $(ALLINC) $(UINCDIR)

##############################################################################
# Toolchain rules
##############################################################################

RULESPATH = $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC/mk
include $(RULESPATH)/arm-none-eabi.mk
include $(RULESPATH)/rules.mk