#include <gpucore/vertex_array.hpp>
#include <gpucore/opengl.hpp>

#include <private/gpucore/utility.hpp>

namespace gpucore
{
    vertex_layout::vertex_layout(uint32_t a_index, uint32_t a_count, uint32_t a_stride, const void *a_offset)
        : index(a_index), count(a_count), stride(a_stride), offset(a_offset)
    {
    }

    class vertex_array::components
    {
    public:
        mutable uint32_t render_id = 0u;
        mutable uint32_t cached_id = 0u;
    };

    vertex_array::vertex_array()
        : m_components(new vertex_array::components)
    {
        glGenVertexArrays(1, &m_components->render_id);

        attach();
        detach();
    }

    vertex_array::~vertex_array()
    {
        if (m_components->render_id)
            glDeleteVertexArrays(1, &m_components->render_id);

        m_components->render_id = 0u;
        m_components->cached_id = 0u;

        if (m_components)
            delete m_components;
        
        m_components = nullptr;
    }

    void vertex_array::link(vertex_buffer &a_buffer, vertex_layout a_layout) const
    {
        attach();
            a_buffer.attach();
                glVertexAttribPointer(a_layout.index, a_layout.count, GL_FLOAT, GL_FALSE, a_layout.stride, a_layout.offset);
                glEnableVertexAttribArray(a_layout.index);
            a_buffer.detach();
        detach();
    }

    void vertex_array::link(element_buffer &a_buffer) const
    {
        attach();
            a_buffer.attach();
        detach();
        // we should unbind vertex array first because
        // unbinding the element buffer first will unlink it
        a_buffer.detach();
    }

    void vertex_array::attach() const
    {
        m_components->cached_id =
            get_uint(GL_VERTEX_ARRAY_BINDING);

        glBindVertexArray(m_components->render_id);
    }

    void vertex_array::detach() const
    {
        glBindVertexArray(m_components->cached_id);

        if (m_components->cached_id)
            m_components->cached_id = 0u;
    }
}
