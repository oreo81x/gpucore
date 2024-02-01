#pragma once

#include <gpucore/export.hpp>

namespace gpucore
{
    class GPUCORE_API vertex_buffer
    {
    public:
         vertex_buffer(const float *a_data, uint32_t a_size);
        ~vertex_buffer();

        void attach() const;
        void detach() const;

    private:
        class components;

        const components *
            m_components = nullptr;
    };
}
