workspace "SodaEngine"
architecture "x64"

configurations
{
    "Debug",
    "Release",
    "Dist"
}


--{{ VARS DIRECTORY }}--
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- include dirs
IncludeDirs = {}
IncludeDirs["glfw"] = "Soda/submodules/glfw/include"

include "Soda/submodules/glfw"
-- {{ /VARS DIRECTORY }}--


--{{ SODA PROJECT }}--
project "Soda"
    location "Soda"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-objs/" .. outputdir .. "/%{prj.name}")

    pchheader "SD_PCH.h"
    pchsource "%{prj.name}/src/SD_PCH.cpp"
    
    
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/submodules/spdlog/include",
        "%{IncludeDirs.glfw}"
    }

    links
    {
        "glfw",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "SD_PLATFORM_WIN",
            "SD_DLL_BUILD"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SodaCan")
        }
    
    filter "configurations:Debug"
        defines "SD_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines { "SD_RELEASE", "SD_ENABLE_ASSERTS" }
        optimize "On"
    
    filter "configurations:Dist"
        defines "SD_DIST"
        optimize "On"
-- {{ /SODA PROJECT }}--


--{{ SODACAN PROJECT }}--
project "SodaCan"
    location "SodaCan"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-objs/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Soda/submodules/spdlog/include",
        "Soda/src"
    }

    links
    {
        "Soda"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "SD_PLATFORM_WIN"
        }

    filter "configurations:Debug"
        defines "SD_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "SD_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "SD_DIST"
        optimize "On"
-- {{ /SODACAN PROJECT }}--

