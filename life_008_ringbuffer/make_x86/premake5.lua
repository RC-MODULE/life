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
  	libdirs { "$(VSHELL)/lib", "$(NMPP)/lib","$(HAL)/lib" }
	includedirs { "$(HAL)/include", "$(VSHELL)/include", "$(NMPP)/include" }


      configuration "Debug"
         defines { "DEBUG" }
         symbols  "On" 
	  links { "vshell.lib", "nmpp-x86d.lib", "hal-virtual-x86d.lib" }
		 

      configuration "Release"
         defines { "NDEBUG" }
         symbols  "Off" 
	  links { "vshell.lib", "nmpp-x86.lib", "hal-virtual-x86.lib" }
		 
		 
		 
solution "life-x86-target"
   configurations { "Debug", "Release" }
   --platforms{"x64","x86"}

   -- A project defines one build target
   project "life-x86-target"
      kind "ConsoleApp"
      language "C++"
      files { "../src_life_common/*.h", "../src_nm/*.cpp", "../src_life_pc/*.cpp", "../src_life_common/*.cpp"}
	  libdirs { "$(NMPP)/lib","$(HAL)/lib" }
	  includedirs { "../src_life_common", "$(HAL)/include", "$(NMPP)/include"  }


      configuration "Debug"
         defines { "DEBUG" }
         symbols  "On" 
	  links { "nmpp-x86d.lib", "hal-virtual-x86d.lib" }
		 

      configuration "Release"
         defines { "NDEBUG" }
         symbols  "Off" 
	  links { "nmpp-x86.lib", "hal-virtual-x86.lib" }
		 
		 
