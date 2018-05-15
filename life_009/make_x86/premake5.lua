#!lua

-- A solution contains projects, and defines the available configurations
solution "life-board-host"
	configurations { "Debug", "Release" }
	--platforms{"x64","x86"}
   -- A project defines one build target
   project "life-board-host"
      
      kind "ConsoleApp"
      language "C++"
      files { "**.h", "../src_pc/*.cpp" }
	  libdirs { "$(VSHELL32)/lib", "$(NMPP)/lib" }

      configuration "Debug"
         defines { "DEBUG" }
         symbols  "On" 
		 includedirs { "$(HAL)/include", "$(VSHELL32)/include", "$(NMPP)/include" }
		 links { "vshell32.lib", "nmpp-x86.lib" }
		 

      configuration "Release"
         defines { "NDEBUG" }
         symbols  "Off" 
		 includedirs { "$(HAL)/include", "$(VSHELL32)/include", "$(NMPP)/include" }
		 links { "vshell32.lib", "nmpp-x86.lib" }
		 
		 
		 
solution "life-board-target0"
   configurations { "Debug", "Release" }
   --platforms{"x64","x86"}

   -- A project defines one build target
   project "life-board-target0"
      kind "ConsoleApp"
      language "C++"
      files { "../src_life_common/*.h", "../src_nm0/*.cpp", "../src_life_pc/*.cpp", "../src_life_common/*.cpp",  "$(HAL)/src/x86/hal-x86target.cpp" }
	  libdirs { "$(VSHELL32)/lib", "$(NMPP)/lib" }

      configuration "Debug"
         defines { "DEBUG","PROCESSOR_ID=0" }
         symbols  "On" 
	 objdir("obj0")
		 includedirs { "../src_life_common", "$(HAL)/include", "$(VSHELL32)/include", "$(NMPP)/include"  }
		 links { "nmpp-x86.lib" }
		 

      configuration "Release"
         defines { "NDEBUG","PROCESSOR_ID=0" }
         symbols  "Off"
	 objdir("obj0") 
		 includedirs { "../src_life_common", "$(HAL)/include", "$(VSHELL32)/include", "$(NMPP)/include"  }
		 links { "nmpp-x86.lib"}
		 
solution "life-board-target1"
   configurations { "Debug", "Release" }
   --platforms{"x64","x86"}

   -- A project defines one build target
   project "life-board-target1"
      kind "ConsoleApp"
      language "C++"
      files { "../src_life_common/*.h", "../src_nm1/*.cpp", "../src_life_common/*.cpp", "../src_life_pc/*.cpp" , "$(HAL)/src/x86/hal-x86target.cpp"}
	  libdirs { "$(VSHELL32)/lib", "$(NMPP)/lib" }

      configuration "Debug"
         defines { "DEBUG","PROCESSOR_ID=1" }
         symbols  "On"
	 objdir("obj1") 
		 includedirs { "../src_life_common", "$(HAL)/include", "$(VSHELL32)/include", "$(NMPP)/include"  }
		 links { "nmpp-x86.lib" }
		 

      configuration "Release"
         defines { "NDEBUG","PROCESSOR_ID=1" }
         symbols  "Off"
	 objdir("obj1")
		 includedirs { "../src_life_common", "$(HAL)/include", "$(VSHELL32)/include", "$(NMPP)/include"  }
		 links { "nmpp-x86.lib"}
		 
		 
