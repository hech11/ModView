workspace "ModView"
	architecture "x86"
	configurations {"Debug", "Release"}
	startproject "Sandbox"

	flags { "MultiProcessorCompile" }


outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"



IncludeDir = {}
IncludeDir["GLFW"] = "ModView-Core/vendor/GLFW"
IncludeDir["GLAD"] = "Pixelate/vendor/GLAD"
IncludeDir["ImGui"] = "Pixelate/vendor/ImGui"
IncludeDir["glm"] = "Pixelate/vendor/glm"



group "Dependencies/Rendering"
	include "ModView-Core/vendor/GLFW"
	include "ModView-Core/vendor/GLAD"
group ""


project "ModView-Core"
	location "ModView-Core"
	kind "StaticLib"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/%{prj.name}-" .. outputdir)
	objdir ("bin/%{prj.name}-" .. outputdir)

	pchheader "mvpch.h"
	pchsource "ModView-Core/src/mvpch.cpp"

	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",

		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",


		"%{prj.name}/vendor/ImGui/*.cpp",
		"%{prj.name}/vendor/ImGui/*.h",

		"%{prj.name}/vendor/ImGui/examples/imgui_impl_glfw.cpp",
		"%{prj.name}/vendor/ImGui/examples/imgui_impl_glfw.h",
		"%{prj.name}/vendor/ImGui/examples/imgui_impl_opengl3.cpp",
		"%{prj.name}/vendor/ImGui/examples/imgui_impl_opengl3.h",


		"%{prj.name}/vendor/glm/**.hpp",
		"%{prj.name}/vendor/glm/**.inl"

	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor",
		"%{IncludeDir.GLFW}/include",
		"%{IncludeDir.GLAD}/include",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
	}

	links 
	{
		"GLAD",
		"GLFW"
	}


	filter "system:windows"
		systemversion "latest"

		defines {
			"GLFW_INCLUDE_NONE",
			"_CRT_SECURE_NO_WARNINGS"
		}


	filter "configurations:Debug"
		
		defines
		{
			"MV_DEBUG",
			"MV_PLATFORM_WIN32"
		}
		runtime "Debug"
		symbols "on"



	filter "configurations:Release"
		
		defines
		{
			"MV_RELEASE",
			"MV_PLATFORM_WIN32"
		}
		runtime "Release"
		optimize "on"




project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/%{prj.name}-" .. outputdir)
	objdir ("bin/%{prj.name}-" .. outputdir)

	files
	{
		"%{prj.name}/src/*.cpp",
		"%{prj.name}/src/*.c",
		"%{prj.name}/src/*.h",
		"%{prj.name}/src/*.hpp",


	
	}

	includedirs
	{
		"%{prj.name}/src",
		"ModView-Core/src",
		"ModView-Core/vendor",

		"%{IncludeDir.GLFW}/include",
		"%{IncludeDir.GLAD}/include",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
	}

	links 
	{
		"ModView-Core"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		
		defines
		{
			"MV_DEBUG",
			"MV_PLATFORM_WIN32"
		}
		runtime "Debug"
		symbols "on"



	filter "configurations:Release"
		
		defines
		{
			"MV_RELEASE",
			"MV_PLATFORM_WIN32"
		}
		runtime "Release"
		optimize "on"
