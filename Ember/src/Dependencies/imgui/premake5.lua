-- All paths relative to this premake5 file.
local buildDir = "./build/"
local targetDir = "./lib/"
local objDir = "./obj/"

project "ImGui"
    location (buildDir)
    kind "StaticLib"
    language "C++"
    targetdir (targetDir)
    objdir (objDir)
    toolset "gcc"

    files
    {
        "./*.cpp",
        "./*.h"
    }

    filter "system:Windows"
        cppdialect "C++11"
        staticruntime "On"
        systemversion "latest"

    filter "configurations:Debug"
        defines "DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "NDEBUG"
        optimize "On"