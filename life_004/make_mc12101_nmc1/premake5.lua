#!lua

-- A solution contains projects, and defines the available configurations
solution "life-mc12101"
   configurations { "Debug", "Release" }

   -- A project defines one build target
   project "life-mc12101-x86"
      kind "ConsoleApp"
      language "C++"
      files { "**.h", "../src_pc/*.cpp"}
	  libdirs { "$(MC12101)/lib", "$(VSHELL32)/lib", "$(NMPP)/lib","$(HAL)/lib"  }
	  includedirs { "$(MC12101)/include", "$(HAL)/include", "$(VSHELL32)/include", "$(NMPP)/include" }
	  links { "mc12101load.lib", "vshell32.lib", "hal-mc12101-x86.lib", "nmpp-x86.lib", "life-mc12101-nmc4" }

      configuration "Debug"
         defines { "DEBUG","NMPU1" }
         symbols  "On" 

      configuration "Release"
         defines { "NDEBUG","NMPU1" }
         symbols  "Off" 
		 
		 
	project "life-mc12101-nmc4"
      kind "Makefile"
      files {  "../src_nm/*.cpp", "../src_life_nm/*.asm", "../src_life_common/*.cpp", "../src_life_common/*.h",  "**.asm"  }
	  includedirs { "$(HAL)/include", "$(NMPP)/include","../src_life_common" }
	 
	  configuration "Debug"
		   buildcommands {"make DEBUG=y"}
		   rebuildcommands {"make -B DEBUG=y"}
		   cleancommands {"make clean"}
		   
	  configuration "Release"
		   buildcommands {"make"}
		   rebuildcommands {"make -B"}
		   cleancommands {"make clean"}		   