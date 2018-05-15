#!lua

-- A solution contains projects, and defines the available configurations
solution "life-mc7601"
   configurations { "Debug", "Release" }

   -- A project defines one build target
   project "life-mc7601-x86"
      kind "ConsoleApp"
      language "C++"
      files { "**.h", "../src_pc/*.cpp"}
	  libdirs {   "$(MC7601)/libload", "$(HAL)/lib", "$(VSHELL32)/lib", "$(NMPP)/lib" }
	  includedirs { "$(MC7601)/libload", "$(HAL)/include", "$(VSHELL32)/include", "$(NMPP)/include"  }
	  links { "mc7601_ll_pc.lib","hal-mc7601-x86.lib", "vshell32.lib", "nmpp-x86.lib", "life-mc7601-nmc3" }

      configuration "Debug"
         defines { "DEBUG" }
         symbols  "On" 

      configuration "Release"
         defines { "NDEBUG" }
         symbols  "Off" 
		 
		 
	project "life-mc7601-nmc3"
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