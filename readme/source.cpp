#include <gpucore/header_name.hpp>
#include <gpucore/opengl.hpp>

#include <private/gpucore/utility.hpp>

namespace gpucore
{
    class class_name::components
    {
    public:
        mutable uint32_t render_id = 0u;
        mutable uint32_t cached_id = 0u;
    };

    class_name::class_name()
        : m_components(new class_name::components)
    {
    }

    class_name::~class_name()
    {
        if (m_components)
            delete m_components;

        m_components = nullptr;
    }

    void class_name::attach() const
    {
    }

    void class_name::detach() const
    {
    }
}
