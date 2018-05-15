#!lua

-- A solution contains projects, and defines the available configurations
solution "life-x86"
	configurations { "Debug", "Release" }
	--platforms{"x64","x86"}
   -- A project defines one build target
   project "life-x86"
      
      kind "ConsoleApp"
      language "C++"
      files { "../*.h", "../*.cpp" }
	  includedirs {  "$(VSHELL32)/include" }
	  libdirs { "$(VSHELL32)/lib" }
	  links { "vshell32.lib" }

      configuration "Debug"
         defines { "DEBUG" }
         symbols  "On" 
		 

      configuration "Release"
         defines { "NDEBUG" }
         symbols  "Off" 
		 

		 
		 
