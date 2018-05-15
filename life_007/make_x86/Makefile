ROOT = ../..
include $(ROOT)/global.mk
#-include ../local.mk
HEAP ?= -heap=6384 -heap1=16384 -heap2=16384 -heap3=16384
# BUILD AND RUN MAKEFILE
# This makefile builds simple nmc-application containing single cpp-file  
# Rule 'run' executes the application on MC5103 board and stores return code in ".exitcode"  file

.SUFFIXES:


TARGET   = life-x86-target
HOST     = life-x86-host

ALL: $(TARGET) $(HOST)

$(TARGET): $(TARGET).vcproj
	"$(VS80COMNTOOLS)vsvars32" && vcbuild $(TARGET).vcproj
	
$(HOST): $(HOST).vcproj
	"$(VS80COMNTOOLS)vsvars32" && vcbuild $(HOST).vcproj

run:
	$(MAKE) -j4 runhost runtarget

runhost: $(HOST)
	bin\debug\$(HOST)
	
runtarget: $(TARGET) 
	bin\debug\$(TARGET)
	

include $(ROOT)/clean.mk
	
vs2005:	$(HOST).vcproj


$(HOST).vcproj $(TARGET).vcproj:	
	premake5 vs2005

