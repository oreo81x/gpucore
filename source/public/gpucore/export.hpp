#pragma once

#include <cstdint>

#if !defined(NDEBUG)

    #define GPUCORE_DEBUG_ENABLED

#endif

#define GPUCORE_OPENGL_VERSION_MAJOR 4
#define GPUCORE_OPENGL_VERSION_MINOR 1

#if defined(GPUCORE_STATIC_LINK)

    #define GPUCORE_API_EXPORT
    #define GPUCORE_API_IMPORT

#else

    #if defined(_WIN32)

        #define GPUCORE_API_EXPORT __declspec(dllexport)
        #define GPUCORE_API_IMPORT __declspec(dllimport)

    #else

        #if __GNUC__ >= 4

            #define GPUCORE_API_EXPORT __attribute__((__visibility__("default")))
            #define GPUCORE_API_IMPORT __attribute__((__visibility__("default")))

        #else

            #define GPUCORE_API_EXPORT
            #define GPUCORE_API_IMPORT

        #endif

    #endif

#endif


#if defined(GPUCORE_EXPORT_BUILD)

    #define GPUCORE_API GPUCORE_API_EXPORT

#else

    #define GPUCORE_API GPUCORE_API_IMPORT

#endif


namespace gpucore
{
}
