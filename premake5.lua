
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
    "./%{prj.name}/include/**.h"
}

includedirs
{
    "./%{prj.name}/vendor/spdlog/include",
    "./%{prj.name}/include"
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
        -- "cd ../bin/" .. OutputDir .. "&& mkdir -p Client",
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
    "./%{prj.name}/src/**.cpp",
    "./%{prj.name}/include/**.h"
}

includedirs
{
    "./%{prj.name}/include",
    "./Ember/",
    "./Ember/include",
    "./Ember/vendor/spdlog/include",
}

links
{
    "Ember"
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


