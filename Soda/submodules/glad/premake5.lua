project "glad"
    kind "StaticLib"
    language "C"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-objs/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/glad.c",
        "include/glad/glad.h",
        "include/KHR/khrplatform.h"
    }

    includedirs
    {
        "include"
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "on"

    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"