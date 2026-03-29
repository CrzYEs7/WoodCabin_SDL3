require("export-compile-commands")

workspace("WoodCabin")
configurations({ "Debug", "Release" })

project("WoodCabin")
kind("ConsoleApp")
language("C++")
targetdir("bin/%{cfg.buildcfg}")

files({
	"**.h",
	"**.cpp",
})

includedirs({
	"Vendor/SDL3/include/",
	"src/Game",
	"src/Core",
})

links({
	"SDL3",
})

libdirs({
	"Vendor/SDL3/lib",
})

os.copyfile("Vendor/SDL3/bin/SDL3.dll", "bin/Debug")

filter("configurations:Debug")
defines({ "DEBUG" })
symbols("On")

filter("configurations:Release")
defines({ "NDEBUG" })
optimize("On")
