
workspace "Ember"

    configurations
    {
        "Debug",
        "Release"
    }

    platforms 
    {
        "Windows"
    }

    architecture "x64"
    location "./"

------------------------------------------
-----------------EMBER--------------------
------------------------------------------

local OutputDir = "%{cfg.buildcfg}-%{cfg.architecture}"

-- These were only included once to be built in release mode.
-- include "./Ember/vendor/spdlog"
-- include "./Ember/vendor/imgui"

-- Include Paths
IncludeDir = {}
IncludeDir["glad"] = "./Ember/src/Dependencies/glad/include/"
IncludeDir["glfw"] = "./Ember/src/Dependencies/GLFW/include/"
IncludeDir["imgui"] = "./Ember/src/Dependencies/imgui/"
IncludeDir["spdlog"] = "./Ember/src/Dependencies/spdlog/include/"

LibDir = {}
LibDir["glfw"] = "./Ember/src/Dependencies/GLFW/lib-mingw-w64/"
LibDir["spdlog"] = "./Ember/src/Dependencies/spdlog/lib/"
LibDir["imgui"] = "./Ember/src/Dependencies/imgui/lib/"

project "Ember"
    kind "SharedLib"
    language "C++"
    targetdir ("./bin/" .. OutputDir .. "/%{prj.name}/")
    objdir ("./obj/" .. OutputDir .. "/%{prj.name}/")
    location ("./build")

    files
    {
        "./%{prj.name}/src/Ember/**.cpp",
        "./%{prj.name}/src/Ember/**.h",
        "./%{prj.name}/src/Dependencies/glad/src/glad.c"
    }

    includedirs
    {   
        "./%{prj.name}/src/",
        "%{IncludeDir.glad}",
        "%{IncludeDir.glfw}",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.imgui}"
    }

    links
    {
        "glfw3dll",
        "Spdlog",
        "ImGui"
    }

    libdirs
    {
        "./%{prj.name}/src/Dependencies/GLFW/lib-mingw-w64/",
        "./%{prj.name}/src/Dependencies/spdlog/lib/",
        "./%{prj.name}/src/Dependencies/imgui/lib/"
    }

    filter "system:Windows"
        cppdialect "C++11"
        staticruntime "On"
        systemversion "latest"

        defines 
        {
            "BUILD_EMBER_DLL",
            "ER_ASSERTIONS_ENABLED"
        }

        postbuildcommands 
        {
            --- For cmd
            -- "{COPY} %{cfg.buildtarget.relpath} ../bin/" .. OutputDir .. "/Client"
            -- bash
            "cp %{cfg.buildtarget.relpath} ../bin/" .. OutputDir .. "/Client"
        }

    filter "configurations:Debug"
        defines "DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "NDEBUG"
        optimize "On"

------------------------------------------
-----------------CLIENT-------------------
------------------------------------------

project "Client" 
    kind "ConsoleApp"
    language "C++"
    targetdir ("./bin/" .. OutputDir .. "/%{prj.name}/")
    objdir ("./obj/" .. OutputDir .. "/%{prj.name}")
    location ("./build")

    files
    {
        "./%{prj.name}/src/**.cpp",
        "./%{prj.name}/src/**.h"
    }

    includedirs
    {
        "./%{prj.name}/src/",
        "./Ember/include/",
        "./Ember/src",
        "%{IncludeDir.glad}",
        "%{IncludeDir.glfw}",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.imgui}"
    }

    links
    {
        "Ember",
        "Spdlog",
        "glfw3dll"
    }

    libdirs 
    {
        "./Ember/src/Dependencies/GLFW/lib-mingw-w64/",
        "./Ember/src/Dependencies/spdlog/lib/"
    }

    filter "system:Windows"
        cppdialect "C++11"
        staticruntime "On"
        systemversion "latest"

        defines 
        {
            "ER_ASSERTIONS_ENABLED"
        }

    filter "configurations:Debug"
        defines "DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "NDEBUG"
        optimize "On"


