#include <gpucore/texture.hpp>
#include <gpucore/opengl.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <private/gpucore/utility.hpp>

#define GPUCORE_TEXTURE_TARGET GL_TEXTURE_2D
#define GPUCORE_TEXTURE_TARGET_BINDING GL_TEXTURE_BINDING_2D

namespace gpucore
{
    class texture::components
    {
    public:
        mutable uint8_t  crnt_unit = 0u;
        mutable uint32_t render_id = 0u;
        mutable uint32_t cached_id = 0u;
    };

    texture::texture(const char *a_image_file_path)
        : m_components(new texture::components)
    {
        glGenTextures(1, &m_components->render_id);

        attach();
        debug_runtime_error(m_components->render_id, "opengl: glGenTextures() failed!");

        if (a_image_file_path)
        {
            stbi_set_flip_vertically_on_load(1);
            int32_t width = 0, height = 0, format = 0;
            unsigned char *pixels =
                stbi_load(a_image_file_path, &width, &height, &format, 0);
            debug_runtime_error(pixels, "faild load image file(" + std::string(a_image_file_path) + ")!");

            const uint32_t COLOR_FORMAT =
                (format == 1) ? GL_RED  :
                (format == 3) ? GL_RGB  :
                (format == 4) ? GL_RGBA : GL_RG;
                
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, COLOR_FORMAT, GL_UNSIGNED_BYTE, pixels);
            stbi_image_free(pixels);
        }
        else {
            unsigned char pixels[4] = { 255u, 255u, 255u, 255u };
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
        detach();
    }

    texture::~texture()
    {
        if (m_components->render_id)
            glDeleteTextures(1, &m_components->render_id);

        m_components->render_id = 0u;
        m_components->cached_id = 0u;
        m_components->crnt_unit = 0u;

        if (m_components)
            delete m_components;

        m_components = nullptr;
    }

    void texture::attach(uint8_t a_unit) const
    {
        glActiveTexture(GL_TEXTURE0 + (m_components->crnt_unit = a_unit));

        m_components->cached_id =
            get_uint(GPUCORE_TEXTURE_TARGET_BINDING);

        glBindTexture(GPUCORE_TEXTURE_TARGET, m_components->render_id);
    }

    void texture::detach() const
    {
        glActiveTexture(GL_TEXTURE0 +           m_components->crnt_unit);
        glBindTexture(GPUCORE_TEXTURE_TARGET,   m_components->cached_id);

        m_components->cached_id = 0u;
        m_components->crnt_unit = 0u;
    }
}
