workspace "SodaEngine3D"
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
IncludeDirs["stb_image"] = "Soda/submodules/stb_image"

group "dependencies"
    include "Soda/submodules/glfw"
    include "Soda/submodules/glad"
    include "Soda/submodules/imgui"
group ""
-- {{ /VARS DIRECTORY }}--


--{{ SODA PROJECT }}--
project "Soda"
    location "Soda"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-objs/" .. outputdir .. "/%{prj.name}")

    pchheader "SD_PCH.h"
    pchsource "%{prj.name}/src/SD_PCH.cpp"
    
    
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/submodules/stb_image/**.h",
        "%{prj.name}/submodules/stb_image/**.cpp",
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
        "%{IncludeDirs.stb_image}",
    }

    links
    {
        "glfw",
        "glad",
        "imgui",
        "opengl32"
    }
    
    defines
    {
        "GLFW_INCLUDE_NONE",
        "_CRT_SECURE_NO_WARNINGS"
    }

    filter "system:windows"
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
-- {{ /SODA PROJECT }}--


--{{ SODACAN PROJECT }}--
project "SodaCan"
    location "SodaCan"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

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
        "Soda/submodules/imgui"

    }

    links
    {
        "Soda"
    }

    filter "system:windows"
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