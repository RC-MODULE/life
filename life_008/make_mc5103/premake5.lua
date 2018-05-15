#!lua

-- A solution contains projects, and defines the available configurations
solution "life-mc5103"
   configurations { "Debug", "Release" }

   -- A project defines one build target
   project "life-mc5103-x86"
      kind "ConsoleApp"
      language "C++"
      files { "**.h", "../src_pc/*.cpp"}
	  libdirs {   "$(MC5103)/libload", "$(VSHELL32)/lib", "$(NMPP)/lib","$(HAL)/lib"  }
	  includedirs { "$(MC5103)/libload", "$(HAL)/include", "$(VSHELL32)/include", "$(NMPP)/include"  }
	  links { "mc5103load.lib", "vshell32.lib", "hal-mc5103-x86.lib", "nmpp-x86.lib", "life-mc5103-nmc3" }

      configuration "Debug"
         defines { "DEBUG" }
         symbols  "On" 

      configuration "Release"
         defines { "NDEBUG" }
         symbols  "Off" 
		 
		 
	project "life-mc5103-nmc3"
      kind "Makefile"
      files { "../src_nm/*.cpp", "../src_life_nm/*.asm", "../src_life_common/*.cpp", "../src_life_common/*.h" }
	 
	  configuration "Debug"
		   buildcommands {"make DEBUG=y"}
		   rebuildcommands {"make -B DEBUG=y"}
		   cleancommands {"make clean"}
		   
	  configuration "Release"
		   buildcommands {"make"}
		   rebuildcommands {"make -B"}
		   cleancommands {"make clean"}		   