

project "Spdlog"
    kind "StaticLib"
    language "C++"
    targetdir "./lib"
    objdir "./obj"
    location "./build"

    files
    {
        "./src/**.cpp",
        "./include/**.h"
    }

    includedirs
    {
        "./include"
    }

    filter "system:Windows"
        cppdialect "C++11"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "SPDLOG_COMPILED_LIB",
            "SPDLOG_ENABLE_PCH"
        }
        
    filter "configurations:Debug"
        defines "DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "NDEBUG"
        optimize "On"
