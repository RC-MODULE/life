ROOT = ../..
include $(ROOT)/global.mk
HEAP ?= -heap=16384 -heap1=16384 -heap2=16384 -heap3=16384
# BUILD AND RUN MAKEFILE
# This makefile builds simple nmc-application containing single cpp-file  
# Rule 'run' executes the application on MC12101 board and stores return code in ".exitcode"  file

.SUFFIXES:


ifndef MC12101
$(warning *** WARNING: 'MC12101' environment variable is not defined! Board SDK might not have installed correctly. )
endif 


BOARD    = life-mc12101
HOST     = $(BOARD)-x86


TARGET   = life.abs
INC_DIRS = -I"$(MC12101)/include"  	-I"$(NMPP)/include" -I"$(HAL)/include" -I"$(NEURO)/include" -I../src_life_common
LIB_DIRS = -L"$(MC12101)/lib"     	-L"$(NMPP)/lib"	    -L"$(HAL)/lib"     -L"$(NEURO)/lib" 	
LIBS     = mc12101lib_nm.lib libc4.lib nmpp-nmc4.lib hal-mc12101.lib
CFG      = mc12101brd-nmc1.cfg
#SRC_CPP  = $(wildcard $(addsuffix /*.cpp,../src_nm))
SRC_CPP  = $(wildcard $(addsuffix /*.cpp,../src_nm))
SRC_CPP += $(wildcard $(addsuffix /*.cpp,../src_life_common))
SRC_ASM  = $(wildcard $(addsuffix /*.asm,../src_life_nm))
SRC_ASM += $(wildcard $(addsuffix /*.asm,.))


ALL: $(TARGET) $(HOST)
$(TARGET): $(SRC_CPP) $(SRC_ASM) $(CFG) Makefile
	nmcc -o$(TARGET) -m.main.map $(SRC_CPP) $(SRC_ASM) -nmc4  -Wa,-split_sir  -g -O0 $(INC_DIRS) $(LIB_DIRS) $(LIBS) -c$(CFG) -heap=2000000 -heap1=32000 -heap2=32000 -heap3=32000

	
VS ?= vs2005
	
$(HOST): $(VS)

$(HOST).vcxproj :	premake5.lua 
	premake5 vs2015

$(HOST).vcproj :	premake5.lua 
	premake5 vs2005

vs2005:    	$(HOST).vcproj
	"$(VS80COMNTOOLS)vsvars32" && vcbuild $(HOST).vcproj
	
vs2015:    	$(HOST).vcxproj
	"$(VS140COMNTOOLS)vsvars32" && msbuild $(HOST).vcxproj
	"$(VS140COMNTOOLS)vsvars32" && msbuild $(HOST).vcxproj /p:Configuration=Release
#========================= test & run ===================



PATH:=$(MC12101)/bin;$(PATH)



run: $(TARGET) $(HOST)
	bin\debug\$(HOST)
	


include $(ROOT)/clean.mk
	