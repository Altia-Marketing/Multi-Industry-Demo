#
# Author:   Altia Incorporated
#
# Revision: Release 13.x - May, 2020
#
#           Copyright (c) 1995-2020, Altia Incorporated
#
# Description:
#
# Example linux command line tools make file that compiles and links C
# source code with the FLOAT version of the Altia C/C++ API library.
#
# This make file is executed from a bash shell.
#
# TO USE THIS MAKE FILE:
#
# By default, this make file compiles/links the C source code stress.c into
# an executable with the same name as the Altia Project file.
# To change the executable, modify the SCR1BASE line in this file:
#
#   SRC1BASE	= <new_filename>
#
# To add more C source files to compile into the executable, add more
# object file names to the OBJS line later in this file.  For example:
#
#   OBJS		= $(SRC1BASE).o next.o another.o last.o
#
# To execute this make file, run the build.bat shell script (located in the
# same folder as this Makefile).  By default this will build an executable
# by linking with the Altia DeepScreen libraries.
#

TOOLCHAIN_BASE_PATH = /opt/gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu/bin
SYSROOT             = /opt/iMX8ULP-6.1.22

FILENAME	= Makefile

ALTIAHOME	= ..

CX		= $(TOOLCHAIN_BASE_PATH)/aarch64-none-linux-gnu-gcc
LD		= $(TOOLCHAIN_BASE_PATH)/aarch64-none-linux-gnu-g++
MAKE		= make

EXTRAFLAGS	=

LIBTYPE		= float
UNITYPE		=
MDOPT		=

UNIFLAGS	= -DALTIAUNICODEAPI -DUNICODE -D_UNICODE


# Uncomment next 2 lines for debug compile and link.
#CDEBUG		= -g
#LDEBUG		= -g

DSCFLAGS	= $(MYCFLAGS) $(UNIFLAGS) -I../out/include -I../out/include/api/float -DDEEPSCREEN $(EXTRAFLAGS) $(CDEBUG)
CXFLAGS		= $(DSCFLAGS)

DSLFLAGS	= $(MYLDFLAGS) $(LDEBUG)
LDFLAGS		= $(DSLFLAGS)

DSLIBS		= ../out/libs/api/float/libaltiaAPIlibfloat.a ../out/libs/libaltiaWinLib.a
LIBS		= $(DSLIBS)

STDDSLIBS	=  -lpthread -lGLESv2 -lEGL -lgbm -ldrm -lpng -lz -lm
STDLIBS		= $(STDDSLIBS)

DSBASE		= ByteSizedDemo
SRC1BASE	= $(DSBASE)

OBJS		= main.o

EXEVSVER	=
EXETYPE		=

PROGRAM		= ../out/$(SRC1BASE)$(EXETYPE)

#
# Default action is to build an executable with all of the current macro
# settings.

default: $(PROGRAM)

#
# Link application objects into an executable program.
#

$(PROGRAM): $(OBJS) $(LIBS)
	$(LD) $(MYLDFLAGS) --sysroot=$(SYSROOT) -o $@ $(OBJS) $(LIBS) $(STDLIBS)
	@echo Done.

#
# Compile application source into objects.
#

%.o: %.c
	$(CX) $(MYCFLAGS) --sysroot=$(SYSROOT) -c -o $@ $< $(CXFLAGS) $(DSFLAGS)

#
# Remove application objects and executable program.
#

clean::
	@del $(OBJS)
	@del $(PROGRAM)
