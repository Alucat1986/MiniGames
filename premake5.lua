-- premake5.lua
workspace "MiniGames"
	architecture "x64"
	configurations { "Debug", "Release", "Dist" }
	startproject "Pong"

	-- Workspace-wide build options for MSVC
	filter "system:windows"
		buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus", "/w44365" }

	warnings "Extra"

	OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

	include "Pong/Build-Pong.lua"
	include "Snake/Build-Snake.lua"