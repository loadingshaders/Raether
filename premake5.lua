workspace "Raether"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

	startproject "Raether"

arch = "%{cfg.architecture}"
config = "%{cfg.buildcfg}"

project "Raether"
	location "Raether"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	files {"%{prj.name}/assets/icon/Raether.ico"}

	targetdir ("bin/" .. arch .. "/" .. config)
	objdir ("bin/intermediates/" .. arch .. "/" .. config )

	rcfiles = {
		"%{prj.name}/Resources/resources.rc"
	}

	rcheaderfiles = {
		"%{prj.name}/Resources/resource.h"
	}

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",

		rcfiles,
		rcheaderfiles
	}

	includedirs
	{
		"deps/include"
	}
	
	libdirs
	{
		"deps/lib"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines { "DEBUG" }
		runtime "Debug"
		symbols "On"
		optimize "Off"
		buildoptions "/MTd"
		links
		{
			"SDL2.lib",
			"SDL2main.lib",
			"SDL2test.lib"
		}

	filter "configurations:Release"
		defines { "RELEASE" }
		runtime "Release"
		symbols "Off"
		optimize "On"
		buildoptions "/MT"
		links
		{
			"SDL2.lib",
			"SDL2main.lib",
		}

	vstudio = {  }

	vstudio.toolset = "msc-v143"

	vstudio.vc2022 = {
		includeDirs = { 
			"deps/include"
		}
	}

	vstudio.vc2022["Debug"] = {
		libDirs = { 
			"deps/lib"
		},
		links = { 
			"SDL2.lib",
			"SDL2main.lib",
			"SDL2test.lib"
		}
	}

	vstudio.vc2022["Release"] = {
		libDirs = { 
			"deps/lib"
		},
		links = { 
			"SDL2.lib",
			"SDL2main.lib"
		}
	}