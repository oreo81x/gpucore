#pragma once

#include <gpucore/export.hpp>

namespace gpucore
{
    class GPUCORE_API texture
    {
    public:
         texture(const char *a_image_file_path = nullptr);
        ~texture();

        void attach(uint8_t a_unit = 0u) const;
        void detach() const;

    private:
        class components;

        const components *
            m_components = nullptr;
    };
}
