workspace "gpucore"
    location "output/build"

    targetdir   ("output/bin/"      .. "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")
    objdir      ("output/bin-int/"  .. "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")

    configurations {
        "debug", "release"
    }

    filter "configurations:debug"
        runtime "Debug"
        symbols "On"
    filter "configurations:release"
        runtime "Release"
        optimize "Speed"

        defines {
            "NDEBUG"
        }
    filter {}

    architecture "x86_64"

    includedirs {
        "source", "source/public", "extlib/include"
    }

    libdirs {
        "extlib/%{cfg.system}"
    }

    project "gpucore"
        kind "SharedLib"

        warnings   "Extra"
        language   "C++"
        cppdialect "C++14"
        staticruntime "On"
        systemversion "latest"

        files {
            "source/private/%{prj.name}/**.hpp", "source/public/%{prj.name}/**.hpp",
            "source/private/%{prj.name}/**.cpp", "source/public/%{prj.name}/**.cpp"
        }

        defines {
            "GPUCORE_EXPORT_BUILD"
        }

        filter "kind:SharedLib"
            defines {

            }
        filter "kind:StaticLib"
            defines {
                "GPUCORE_STATIC_LINK"
            }
        filter {}

    project "sandbox"
        kind "ConsoleApp"

        warnings   "Extra"
        language   "C++"
        cppdialect "C++14"
        staticruntime "On"
        systemversion "latest"

        files {
            "source/private/%{prj.name}/**.hpp", "source/public/%{prj.name}/**.hpp",
            "source/private/%{prj.name}/**.cpp", "source/public/%{prj.name}/**.cpp"
        }

        links {
            "gpucore"
        }

        filter "system:linux"
            links {
                "glfw3", "X11"
            }
        filter "system:macosx"
            links "glfw3"
        filter { "system:windows", "configurations:debug" }
            links {
                "glfw3"
            }
        filter { "system:windows", "configurations:debug" }
            links {
                "glfw3_mt"
            }
        filter {}