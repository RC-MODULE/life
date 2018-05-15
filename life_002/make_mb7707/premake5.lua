#!lua

-- A solution contains projects, and defines the available configurations
solution "life-mb7707"
   configurations { "Debug", "Release" }

   -- A project defines one build target
   project "life-mb7707-x86"
      kind "ConsoleApp"
      language "C++"
      files { "**.h", "../src_pc/*.cpp"}
	  includedirs { "$(MB7707)/include", "$(HAL)/include", "$(VSHELL32)/include", "$(NMPP)/include"  }
	  libdirs { "$(MB7707)/libload", "$(VSHELL32)/lib", "$(NMPP)/lib", "$(HAL)/lib"  }
	  links { "mb7707load.lib", "vshell32.lib", "nmpp-x86.lib", "hal-mb7707-x86.lib", "life-mb7707-nmc3" }

      configuration "Debug"
         defines { "DEBUG" }
         symbols  "On" 

      configuration "Release"
         defines { "NDEBUG" }
         symbols  "Off" 
		 
	project "life-mb7707-nmc3"
      kind "Makefile"
      files { "../src_nm/*.cpp", "../src_life_nm/*.asm", "../src_life_common/*.cpp", "../src_life_common/*.h"  }
	 
	  configuration "Debug"
		   buildcommands {"make DEBUG=y"}
		   rebuildcommands {"make -B DEBUG=y"}
		   cleancommands {"make clean"}
		   
	  configuration "Release"
		   buildcommands {"make"}
		   rebuildcommands {"make -B"}
		   cleancommands {"make clean"}		   