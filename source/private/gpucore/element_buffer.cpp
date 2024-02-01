#include <gpucore/element_buffer.hpp>
#include <gpucore/opengl.hpp>

#include <private/gpucore/utility.hpp>

#define BUFFER_TARGET           GL_ELEMENT_ARRAY_BUFFER
#define BUFFER_TARGET_BINDING   GL_ELEMENT_ARRAY_BUFFER_BINDING

namespace gpucore
{
    class element_buffer::components
    {
    public:
        mutable uint32_t render_id = 0u;
        mutable uint32_t cached_id = 0u;
    };

    element_buffer::element_buffer(const uint32_t *a_data, uint32_t a_size)
        : m_components(new element_buffer::components)
    {
        glGenBuffers(1, &m_components->render_id);

        attach();
        debug_runtime_error((m_components->render_id), "failed obtain valid opengl id for gpucore::element_buffer object!");
            glBufferData(BUFFER_TARGET, a_size, a_data, GL_STATIC_DRAW);
        detach();
    }

    element_buffer::~element_buffer()
    {
        if (m_components->render_id)
            glDeleteBuffers(1, &m_components->render_id);

        m_components->render_id = 0u;
        m_components->cached_id = 0u;

        if (m_components)
            delete m_components;

        m_components = nullptr;
    }

    void element_buffer::attach() const
    {
        m_components->cached_id =
            get_uint(BUFFER_TARGET_BINDING);

        glBindBuffer(BUFFER_TARGET, m_components->render_id);
    }

    void element_buffer::detach() const
    {
        glBindBuffer(BUFFER_TARGET, m_components->cached_id);
        
        if (m_components->cached_id)
            m_components->cached_id = 0u;
    }
}
