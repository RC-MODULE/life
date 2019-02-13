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
	  includedirs { "$(MC7601)/include", "$(HAL)/include", "$(VSHELL32)/include", "$(NMPP)/include"  }
	  links { "mc7601_ll_pc.lib","hal-mc7601-x86.lib", "vshell32.lib", "nmpp-x86.lib", "life-mc7601-nmc3-0","life-mc7601-nmc3-1" }

      configuration "Debug"
         defines { "DEBUG" }
         symbols  "On" 

      configuration "Release"
         defines { "NDEBUG" }
         symbols  "Off" 
		 
		 
	project "life-mc7601-nmc3-0"
      kind "Makefile"
      includedirs { "$(MC7601)/include", "$(HAL)/include", "$(NMPP)/include", "../src_life_common"  }
      files { "../src_nm0/*.cpp", "../src_life_nm/*.asm", "../src_life_common/*.cpp", "../src_life_common/*.h"  }
	 
	  configuration "Debug"
		   buildcommands {"make -f Makefile0 DEBUG=y"}
		   rebuildcommands {"make -f Makefile0 -B DEBUG=y"}
		   cleancommands {"make -f Makefile0 clean"}
		   
	  configuration "Release"
		   buildcommands {"make -f Makefile0"}
		   rebuildcommands {"make -f Makefile0 -B"}
		   cleancommands {"make -f Makefile0 clean"}		   
		   
	project "life-mc7601-nmc3-1"
      kind "Makefile"
      includedirs { "$(MC7601)/include", "$(HAL)/include", "$(NMPP)/include", "../src_life_common"  }
      files { "../src_nm1/*.cpp", "../src_life_nm/*.asm", "../src_life_common/*.cpp", "../src_life_common/*.h"  }
	 
	  configuration "Debug"
		   buildcommands {"make -f Makefile1 DEBUG=y"}
		   rebuildcommands {"make -f Makefile1 -B DEBUG=y"}
		   cleancommands {"make -f Makefile1 clean"}
		   
	  configuration "Release"
		   buildcommands {"make -f Makefile1"}
		   rebuildcommands {"make -f Makefile1 -B"}
		   cleancommands {"make -f Makefile1 clean"}		 