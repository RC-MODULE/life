#!lua

-- A solution contains projects, and defines the available configurations
solution "life-x86"
	configurations { "Debug", "Release" }
	--platforms{"x64","x86"}
   -- A project defines one build target
   project "life-x86-host"
      
      kind "ConsoleApp"
      language "C++"
      files { "**.h", "../src_pc/*.cpp" }
	  libdirs { "$(VSHELL32)/lib", "$(NMPP)/lib","$(HAL)/lib" }
	  includedirs { "$(HAL)/include", "$(VSHELL32)/include", "$(NMPP)/include" }
	  links { "vshell32.lib", "nmpp-x86.lib", "hal-virtual-x86.lib" }

      configuration "Debug"
         defines { "DEBUG" }
         symbols  "On" 
		 

      configuration "Release"
         defines { "NDEBUG" }
         symbols  "Off" 
		 
		 
		 
solution "life-x86-target"
   configurations { "Debug", "Release" }
   --platforms{"x64","x86"}

   -- A project defines one build target
   project "life-x86-target"
      kind "ConsoleApp"
      language "C++"
      files { "../src_life_common/*.h", "../src_nm/*.cpp", "../src_life_pc/*.cpp", "../src_life_common/*.cpp"}
	  libdirs { "$(VSHELL32)/lib", "$(NMPP)/lib","$(HAL)/lib" }
	  includedirs { "../src_life_common", "$(HAL)/include", "$(VSHELL32)/include", "$(NMPP)/include"  }
	  links { "nmpp-x86.lib", "hal-virtual-x86.lib" }

      configuration "Debug"
         defines { "DEBUG" }
         symbols  "On" 
		 

      configuration "Release"
         defines { "NDEBUG" }
         symbols  "Off" 
		 
		 
