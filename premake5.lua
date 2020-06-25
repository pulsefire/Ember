
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

------------------------------------------
-----------------EMBER--------------------
------------------------------------------

local OutputDir = "%{cfg.buildcfg}-%{cfg.architecture}"

-- These were only included once to be build in release mode.
-- include "./Ember/vendor/spdlog"
-- include "./Ember/vendor/imgui"

-- Include Paths
IncludeDir = {}
IncludeDir["glad"] = "./Ember/vendor/glad/include/"
IncludeDir["GLFW"] = "./Ember/vendor/GLFW/include/"
IncludeDir["ImGui"] = "./Ember/vendor/imgui/"
IncludeDir["Spdlog"] = "./Ember/vendor/spdlog/include/"

project "Ember"
    location "Ember"
    kind "SharedLib"
    language "C++"
    targetdir ("./bin/" .. OutputDir .. "/%{prj.name}/")
    objdir ("./obj/" .. OutputDir .. "/%{prj.name}/")
    location ("./build")

    files
    {
        "./%{prj.name}/src/Ember/**.cpp",
        "./%{prj.name}/src/Ember/**.h",
        "./%{prj.name}/vendor/glad/src/glad.c"
    }

    includedirs
    {   
        "./%{prj.name}/src/",
        "%{IncludeDir.glad}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Spdlog}",
        "%{IncludeDir.ImGui}"
        -- "./%{prj.name}/vendor/GLFW/include",
        -- "./%{prj.name}/vendor/spdlog/include",
        -- "./%{prj.name}/vendor/glad/include"
        -- "./%{prj.name}/vendor/imgui"
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
    location "Client"
    kind "ConsoleApp"
    language "C++"
    targetdir ("./bin/" .. OutputDir .. "/%{prj.name}/")
    objdir ("./obj/" .. OutputDir .. "/%{prj.name}")
    location ("./build")

    files
    {
        "./%{prj.name}/src/**.cpp"
    }

    includedirs
    {


        "./%{prj.name}/src/",
        "./Ember/src",
        "%{IncludeDir.glad}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Spdlog}"
        -- "./Ember/vendor/GLFW/include",
        -- "./Ember/vendor/spdlog/include",
        -- "./Ember/vendor/glad/include"
    }

    links
    {
        "Ember",
        "Spdlog",
        "glfw3dll"
    }

    libdirs 
    {
        "./Ember/vendor/GLFW/lib-mingw-w64/",
        "./Ember/vendor/spdlog/lib/"
    }

    filter "system:Windows"
        cppdialect "C++11"
        staticruntime "On"
        systemversion "latest"

        defines {
            "ER_ASSERTIONS_ENABLED"
        }

    filter "configurations:Debug"
        defines "DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "NDEBUG"
        optimize "On"


