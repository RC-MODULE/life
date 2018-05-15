ROOT = ../..
include $(ROOT)/global.mk
#-include ../local.mk
HEAP ?= -heap=16384 -heap1=16384 -heap2=16384 -heap3=16384
# BUILD AND RUN MAKEFILE
# This makefile builds simple nmc-application containing single cpp-file  
# Rule 'run' executes the application on MC5103 board and stores return code in ".exitcode"  file

.SUFFIXES:


ifndef MC5103
$(error ERROR: 'MC5103' environment variable is not defined!  )
endif 


BOARD    = life-mc5103
HOST     = $(BOARD)-x86


TARGET   = life.abs
INC_DIRS = -I"$(MC5103)/include" 	-I"$(NMPP)/include" -I$(HAL)/include -I"$(NEURO)/include" -I../src_life_common
LIB_DIRS = -L"$(MC5103)/lib" 		-L"$(NMPP)/lib"		-L$(HAL)/lib 	 -L"$(NEURO)/lib" 
LIBS     = nmpp-nmc3.lib mc5103lib.lib libint05.lib hal-mc5103.lib
CFG      = mc5103brd.cfg
SRC_CPP  = $(wildcard $(addsuffix /*.cpp,../src_nm))
SRC_CPP += $(wildcard $(addsuffix /*.cpp,../src_life_common))
SRC_ASM  = $(wildcard $(addsuffix /*.asm,../src_life_nm))


ALL: $(TARGET)   $(HOST)
$(TARGET): $(SRC_CPP) $(SRC_ASM) $(CFG) Makefile
	nmcc -o$(TARGET) -m.main.map $(SRC_CPP) $(SRC_ASM)  -nmc3 -g -O0 $(INC_DIRS) $(LIB_DIRS) $(LIBS) -c$(CFG) -heap=2000000 -heap1=32000 -heap2=32000 -heap3=32000

PATH:=$(MC5103)/bin;$(PATH)

VS ?= vs2005 

$(HOST): $(VS)


run: $(TARGET) $(HOST)
	bin\debug\$(HOST)
	

vs2005: $(HOST).vcproj 
	"$(VS80COMNTOOLS)vsvars32" && vcbuild $(HOST).vcproj

vs2015:	$(HOST).vcxproj
	"$(VS140COMNTOOLS)vsvars32" && msbuild $(HOST).vcxproj /p:Configuration=Debug

$(HOST).vcproj:
	premake5 vs2005

$(HOST).vcxproj:
	premake5 vs2015
	
include $(ROOT)/clean.mk