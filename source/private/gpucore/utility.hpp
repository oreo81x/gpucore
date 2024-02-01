#pragma once

namespace
{
    inline uint32_t get_uint(GLenum opengl_enum)
    {
        GLint value = 0;
        glGetIntegerv(opengl_enum, &value);

        return static_cast<uint32_t>(value);
    }
}

#if defined(GPUCORE_DEBUG_ENABLED)

    #include <stdexcept>
    #include <cassert>
    #include <string>
    
    inline void runtime_error(bool a_condition, const std::string &a_error)
    {
        if (!a_condition)
            throw std::runtime_error("runtime_error: " + a_error);
    }

    inline void debug_runtime_error(bool a_condition, const std::string &a_error)
    {
        if (!a_condition)
            throw std::runtime_error("runtime_error: " + a_error);
    }

#else

    #define         runtime_error(a_condition, a_error) a_condition
    #define   debug_runtime_error(a_condition, a_error)

#endif
