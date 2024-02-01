#pragma once

#include <gpucore/export.hpp>

namespace gpucore
{
    class GPUCORE_API element_buffer
    {
    public:
         element_buffer(const uint32_t *a_data, uint32_t a_size);
        ~element_buffer();

        void attach() const;
        void detach() const;

    private:
        class components;

        const components *
            m_components = nullptr;
    };
}
