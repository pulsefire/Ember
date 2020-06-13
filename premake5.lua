
local OutputDir = "/%{cfg.buildcfg}-%{cfg.architecture}"

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

    location ("./build")

------------------------------------------
-----------------EMBER--------------------
------------------------------------------

project "Ember"
    location "Ember"
    kind "SharedLib"
    language "C++"
    targetdir ("./bin/" .. OutputDir .. "/%{prj.name}/")
    objdir ("./obj/" .. OutputDir .. "/%{prj.name}/")
    location ("./build")

files
{
    "./%{prj.name}/src/**.cpp",
    "./%{prj.name}/vendor/glad/src/**.c"
}

includedirs
{
    "./%{prj.name}/vendor/",
    "./%{prj.name}/vendor/spdlog/include",
    "./%{prj.name}/vendor/glad/include",
    "./%{prj.name}/include"
}

links
{
    "glfw3dll",
    "spdlog"
}

libdirs
{
    "./%{prj.name}/lib/"
}

filter "system:Windows"
    cppdialect "C++11"
    staticruntime "On"
    systemversion "latest"

    defines 
    {
        "BUILD_EMBER_DLL"
    }

    postbuildcommands 
    {
        --- For cmd
        -- "{COPY} %{cfg.buildtarget.relpath} ../bin/" .. OutputDir .. "/Client"
        -- bash
        "cp %{cfg.buildtarget.relpath} ../bin/" .. OutputDir .. "/Client"
    }

filter "configurations:Debug"
    defines "ER_DEBUG"
    symbols "On"

filter "configurations:Release"
    defines "ER_RELEASE"
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
    "./%{prj.name}/include",
    "./Ember/include",
    "./Ember/vendor/",
    "./Ember/vendor/spdlog/include",
    -- "./Ember/vendor/glad/include"
}

links
{
    "Ember",
    "spdlog",
    -- "glfw3dll"
}

libdirs {
    "./%{prj.name}/lib"
}

filter "system:Windows"
    cppdialect "C++11"
    staticruntime "On"
    systemversion "latest"

filter "configurations:Debug"
    defines "ER_DEBUG"
    symbols "On"

filter "configurations:Release"
    defines "ER_RELEASE"
    optimize "On"


