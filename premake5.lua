workspace "SodaEngine"
architecture "x64"
startproject "SodaCan"

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
IncludeDirs["glad"] = "Soda/submodules/glad/include"
IncludeDirs["imgui"] = "Soda/submodules/imgui"
IncludeDirs["glm"] = "Soda/submodules/glm"

group "dependencies"
    include "Soda/submodules/glfw"
    include "Soda/submodules/glad"
    include "Soda/submodules/imgui"
group ""
-- {{ /VARS DIRECTORY }}--


--{{ SODA PROJECT }}--
project "Soda"
    location "Soda"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-objs/" .. outputdir .. "/%{prj.name}")

    pchheader "SD_PCH.h"
    pchsource "%{prj.name}/src/SD_PCH.cpp"
    
    
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/submodules/glm/glm/**.hpp",
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/submodules/spdlog/include",
        "%{IncludeDirs.glm}",
        "%{IncludeDirs.glfw}",
        "%{IncludeDirs.glad}",
        "%{IncludeDirs.imgui}",
    }

    links
    {
        "glfw",
        "glad",
        "imgui",
        "opengl32"
    }
    
    filter "system:windows"
    cppdialect "C++17"
    systemversion "latest"
    
    defines
    {
        "SD_PLATFORM_WIN",
        "SD_DLL_BUILD",
        "GLFW_INCLUDE_NONE"
    }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SodaCan")
        }
    
    filter "configurations:Debug"
        defines "SD_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "SD_RELEASE"
        runtime "Release"
        optimize "On"
    
    filter "configurations:Dist"
        defines "SD_DIST"
        runtime "Release"
        optimize "On"
-- {{ /SODA PROJECT }}--


--{{ SODACAN PROJECT }}--
project "SodaCan"
    location "SodaCan"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-objs/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "Soda/submodules/glm/glm/**.hpp"
    }

    includedirs
    {
        "Soda/submodules/spdlog/include",
        "Soda/src",
        "Soda/submodules/glm",

    }

    links
    {
        "Soda"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "SD_PLATFORM_WIN"
        }

    filter "configurations:Debug"
        defines "SD_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "SD_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "SD_DIST"
        runtime "Release"
        optimize "On"
-- {{ /SODACAN PROJECT }}--