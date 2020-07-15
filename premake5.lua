
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
IncludeDir["glad"] = "./Ember/vendor/glad/include/"
IncludeDir["glfw"] = "./Ember/vendor/GLFW/include/"
IncludeDir["imgui"] = "./Ember/vendor/imgui/"
IncludeDir["spdlog"] = "./Ember/vendor/spdlog/include/"

LibDir = {}
LibDir["glfw"] = "./Ember/vendor/GLFW/lib-mingw-w64/"
LibDir["spdlog"] = "./Ember/vendor/spdlog/lib/"
LibDir["imgui"] = "./Ember/vendor/imgui/lib/"

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
        "./%{prj.name}/src/vendor/glad/src/glad.c",
        -- GUI implementation for OpenGl
        "./%{prj.name}/src/vendor/imgui/examples/imgui_impl_opengl3.cpp"
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
        "./%{prj.name}/vendor/GLFW/lib-mingw-w64/",
        "./%{prj.name}/vendor/spdlog/lib/",
        "./%{prj.name}/vendor/imgui/lib/"
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
        "Spdlog"
    }

    libdirs 
    {
        "./Ember/vendor/spdlog/lib/"
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


