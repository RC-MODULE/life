ROOT = ../..
include $(ROOT)/global.mk
#-include ../local.mk
HEAP ?= -heap=6384 -heap1=16384 -heap2=16384 -heap3=16384
# BUILD AND RUN MAKEFILE
# This makefile builds simple nmc-application containing single cpp-file  
# Rule 'run' executes the application on MC5103 board and stores return code in ".exitcode"  file

.SUFFIXES:


TARGET   = life-x86

ALL: $(TARGET)

$(TARGET): $(TARGET).vcproj
	"$(VS80COMNTOOLS)vsvars32" && vcbuild $(TARGET).vcproj
	

run: $(TARGET)
	bin\debug\$(TARGET)
	

clean:
	-$(OS_RM) *.abs *.elf *.ncb *.map *.elf *.suo *.user *.filters
	-$(OS_RD) bin obj
	
kill: clean
	-$(OS_RM) *.vcproj *.sln *.vcxproj
	
vs2005:	$(TARGET).vcproj


$(TARGET).vcproj   vs2015:	
	premake5 vs2005

