

-- workspace settings

workspace_settings = {}
workspace_settings.workspace_name 		= "Bunting"
workspace_settings.bundle_identifier	= "com.deifickle"

-- Output files directories signature for bin and int-bin
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- external dependencies
include 'build_scripts/external_dependencies.lua'

-- Current root directory where the global premake file is located
-- TODO: Use a fixed installation directory in program files insted of an arbitrary thing/ infact use this to verify the proper installation directory
root_dir = os.getcwd()
-- Add this as the installation directory to the engine config file
-- print("Generating Engine Config File...")
-- config_file = io.open( root_dir .. "/Engine/content/config/razix_engine.config", "w+")
-- io.output(config_file)
-- io.write("installation_dir=" .. root_dir)
-- run_as_admin = "runas /user:administrator"
-- set_env = run_as_admin .. "SETX RAZIX_SDK" .. root_dir .. " /m"
-- set_env_tools = run_as_admin .. "SETX RAZIX_SDK" .. root_dir .. "/Tools /m"
-- -- Set some Razix SDK env variables
-- os.execute(set_env)
-- os.execute(set_env_tools)

InternalLibs = {}
InternalLibs["BuntingEditor"] = "BuntingEditor"

workspace (workspace_settings.workspace_name)
	location "VsProjFiles"
	startproject "EngineCore"
	
    -- Output directory path based on build config
    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    -- Complete locatoin
    workspace_location = "%{wks.location}"
    -- Binaries Output directory
    targetdir ("bin/%{outputdir}/")
    -- Intermediate files Output directory
    objdir ("bin-int/%{outputdir}/obj/")
    -- Debugging directory = where the main premake5.lua is located
    debugdir "%{wks.location}../"
    --symbolspath "bin-int/%{outputdir}/pdb/"
	
    print("Generating Project files for Architecture = ", Arch)

    -- Various build configuration for the engine
    configurations
    {
        "Debug",
        "Release"
    }

    --apply_engine_global_config()
	
project "EngineCore"
    kind "ConsoleApp"
	architecture "x64"
   
	dependson 
	{ 
		"BuntingEditor" 
	}
	
	defines 
	{
		"ENABLE_RAYGUI_IMPLEMENTATION"
	}
	
    files
    {
        "EngineCore/**.hpp"
        ,"EngineCore/**.h"
        ,"EngineCore/**.cpp"
    }
	
	includedirs
	{
		"%{ExternalIncludeDir.raylib5_64}"
		,"%{ExternalIncludeDir.raygui}"
	}
	
	
	libdirs
	{
		"%{ExternalLibraryDir.raylib5_64}"
		,"bin/%{outputdir}/"
	}
	
	links
	{
		"%{ExternalLib.raylib5_64}"
		,"%{ExternalLib.winmm}"
		,"%{InternalLibs.BuntingEditor}"
	}

project "BuntingEditor"
    kind "StaticLib"
	architecture "x64"
	   
    files
    {
        "BuntingEditor/**.hpp"
        ,"BuntingEditor/**.h"
        ,"BuntingEditor/**.cpp"
    }
	
	includedirs
	{
		"%{ExternalIncludeDir.raylib5_64}"
		,"%{ExternalIncludeDir.raygui}"
	}