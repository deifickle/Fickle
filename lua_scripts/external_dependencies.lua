ExternalIncludeDir = {}

ExternalIncludeDir["raylib5_64"]	= "%{wks.location}/../external/raylib-5.0_win64_msvc16/include"
ExternalIncludeDir["raygui"]		= "%{wks.location}/../external/src/raygui-4.0/src"

ExternalLibraryDir = {}

ExternalLibraryDir["raylib5_64"] = "%{wks.location}/../external/raylib-5.0_win64_msvc16/lib"

ExternalLib = {}

ExternalLib["raylib5_64"] = "raylib"
ExternalLib["winmm"] = "winmm"