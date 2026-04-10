##############################################################################
# Project-only settings
##############################################################################

PROJECT := nuclear_chibios

# Select target here, or override from command line:
#   make TARGET=target_h563
TARGET ?= target_f042

CHIBIOS := ../ChibiOS
CONFDIR := ./cfg
BUILDDIR := ./build
DEPDIR := ./.dep

# Project source files only.
CSRC := main.c tasks.c
CPPSRC :=
UINCDIR := ./
UDEFS :=

##############################################################################
# ChibiOS + target selection
##############################################################################

include make/$(TARGET).mk
include make/chibios_common.mk