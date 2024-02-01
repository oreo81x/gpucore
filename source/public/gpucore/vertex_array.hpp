#pragma once

#include <gpucore/export.hpp>
#include <gpucore/vertex_buffer.hpp>
#include <gpucore/element_buffer.hpp>

namespace gpucore
{
    class GPUCORE_API vertex_layout
    {
    public:
        const uint32_t  index   = 0u;
        const uint32_t  count   = 0u;
        const uint32_t  stride  = 0u;
        const void     *offset  = nullptr;

        vertex_layout(uint32_t a_index, uint32_t a_count, uint32_t a_stride, const void *a_offset);
    };

    class GPUCORE_API vertex_array
    {
    public:
         vertex_array();
        ~vertex_array();
        
        void link(vertex_buffer     &a_buffer, vertex_layout a_layout) const;
        void link(element_buffer    &a_buffer) const;

        void attach() const;
        void detach() const;

    private:
        class components;

        const components *
            m_components = nullptr;
    };
}
