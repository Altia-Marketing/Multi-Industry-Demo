################################################################################
#
# @copyright Copyright (c) 2022 Altia Inc.
#
# Permission to use, copy, and modify this software for any purpose is
# hereby granted, provided that this copyright notice appears in all
# copies and that the entity using, copying, or modifying this software
# has purchased an Altia Deep Screen license. Permission to sell or
# distribute this source code is denied.
#
# Altia makes no representations about the suitability of this software for any
# purpose.  It is provided "as is" without express or implied warranty.
#
# ALTIA INC. DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
# INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
# IN NO EVENT SHALL ALTIA INC. BE LIABLE FOR ANY SPECIAL, INDIRECT OR
# CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
# DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
# OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
# WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#
################################################################################

################################################################################
# Initial target configuration
################################################################################
DS_TARGET_NAME              := miniGL Software Render Target (GCC ARMEABI)
DS_CODE_GEN_BASE_PATH       := ./altia
DS_ENGINE_PATH              := $(DS_CODE_GEN_BASE_PATH)
DS_DRIVER_PATH              := $(DS_CODE_GEN_BASE_PATH)/miniGL

BUILD_TOOLS_PATH            := $(DS_CODE_GEN_BASE_PATH)/build_tools
BUILD_TOOLS_PROFILE         := deepscreen
BUILD_TOOLS_HOST_OS         := win32

TOOLCHAIN_NAME              := gcc
TOOLCHAIN_VERSION           := armeabi

BUILD_OUTPUT_ARTIFACT       := library


################################################################################
# Set the default TOOLCHAIN_BASE_PATH to:
# C:\tools\gcc-arm-none-eabi-rm-10-2020-q4-major
################################################################################
ifeq ($(strip $(TOOLCHAIN_BASE_PATH)),)
TOOLCHAIN_BASE_PATH := C:\tools\gcc-arm-none-eabi-rm-10-2020-q4-major
endif  # ifeq ($(strip $(TOOLCHAIN_BASE_PATH)),)


################################################################################
# Initial build setup  (includes some preliminary error checking)
################################################################################
$(info ================================================================================)
$(info Building for $(DS_TARGET_NAME))
$(info ================================================================================)

include $(BUILD_TOOLS_PATH)/config.mk


################################################################################
# Include the miniGL engine makefile
################################################################################
include $(DS_ENGINE_PATH)/engine.mk


################################################################################
# Include the miniGL software render target
################################################################################
include $(DS_DRIVER_PATH)/miniGL_software_render.mk


################################################################################
# Include the toolchain specific makefile
#
# :NOTE:
# This must come after all the source files, etc. are setup.  Otherwise, the
# simply expanded variables used in the toolchain makefile will not work
# correctly.
################################################################################
include $(TOOLCHAIN_MAKEFILE)


################################################################################
# Set the CPU, FPU, and OPTIONS environment variables based on the JSON
# settings.  Use environment variables so we can strip them below.
################################################################################
MINIGL_SRT_CPU     :=  arm926ej-s
MINIGL_SRT_FPU     :=
MINIGL_SRT_OPTIONS :=  -march=armv5te -mfloat-abi=soft -fno-short-enums


################################################################################
# Perform any target specific setup, config, source file list processing here.
# Examples may include:
#   - addition / removal of certain source files, libraries from the build
#   - addition / removal of toolchain options from various xxxFLAGS variables
################################################################################

CDEFINES += \
    MINIGL_INLINE=inline \
    FS_INLINE=inline

CFLAGS += \
    -mcpu=$(strip $(MINIGL_SRT_CPU)) \
    -mthumb

ifeq ($(strip $(MINIGL_SRT_FPU)),)
CFLAGS +=
else
CFLAGS += -mfloat-abi=hard -mfpu=$(strip $(MINIGL_SRT_FPU))
endif  # ifeq ($(strip $(MINIGL_SRT_FPU)),)

################################################################################
# :NOTE:
# For C++ we need to override __UINT32_TYPE__ and __INT32_TYPE__ to
# "unsigned int" and "int" respectively.
#
# The reason is the GCC version 4.9.3 20150529 (release)
# [ARM/embedded-4_9-branch revision 227977] (GNU Tools for ARM Embedded
# Processors) defines __UINT32_TYPE__ as "long unsigned int" and __INT32_TYPE__
# as "long int".  This causes the C++ based HarfBuzz text shaper to break during
# compilation.
################################################################################
CXXFLAGS += \
    -mcpu=$(strip $(MINIGL_SRT_CPU)) \
    -mthumb \
    -fno-exceptions

ifeq ($(strip $(MINIGL_SRT_FPU)),)
CXXFLAGS +=
else
CXXFLAGS += -mfloat-abi=hard -mfpu=$(strip $(MINIGL_SRT_FPU))
endif  # ifeq ($(strip $(MINIGL_SRT_FPU)),)

################################################################################
# :NOTE:
# The file toolchain_gcc_armeabi.mk adds -fshort_wchar to the CFLAGS to force
# wchar_t to 2 bytes instead of 4 bytes.  But doing so causes the following
# link warning: "uses 2-byte wchar_t yet the output is to use 4-byte wchar_t;
# use of wchar_t values across objects may fail".  Although this does not cause
# a problem in usage between altia code and user code, keeping this consistent
# to eliminate the warning is done so here (so flag gets reversed).
################################################################################
CFLAGS   += -fno-short-wchar
CXXFLAGS += -fno-short-wchar


################################################################################
# :NOTE:
# Enabling Runtime Font Engine during code generation results in the use of
# third party C source code.  Since Altia enables all warnings during compile,
# then there are a few warnings identified in this third party source compile
# which can be silenced.
################################################################################



################################################################################
# :NOTE:
# Enabling Text Shaping during code generation results in the use of third
# party C++ source code.  Since Altia enables all warnings during compile,
# then there are a few warnings identified in this third party source compile
# which can be silenced.
################################################################################



################################################################################
# Give the JSON 'MINIGL_SRT_OPTIONS' a last chance
################################################################################
CFLAGS += $(strip $(MINIGL_SRT_OPTIONS))
CXXFLAGS += $(strip $(MINIGL_SRT_OPTIONS))


################################################################################
# Make sure everything is copacetic
################################################################################
include $(CHECKS_MAKEFILE)


################################################################################
# Include build rules
################################################################################
include $(RULES_MAKEFILE)
