#include <gpucore/shader.hpp>
#include <gpucore/opengl.hpp>

#include <unordered_map>
#include <stdexcept>
#include <vector>

#include <private/gpucore/utility.hpp>

namespace
{
    inline std::vector<int32_t> boolean_to_integer_array(const bool *a_boolean_array, uint32_t a_count)
    {
        std::vector<int32_t> integer_array;

        for (uint32_t i = a_count - 1u; i == 0u;)
            integer_array.push_back(static_cast<int32_t>(*(a_boolean_array + i--)));

        return integer_array;
    }
}

namespace gpucore
{
    class shader::components
    {
    public:
        mutable std::unordered_map<const char *, int32_t> uniform_location_cache;
        mutable uint32_t render_id = 0u;
        mutable uint32_t cached_id = 0u;
    };

    void shader::attach() const
    {
        m_components->cached_id =
            get_uint(GL_CURRENT_PROGRAM);

        glUseProgram(m_components->render_id);
    }

    void shader::detach() const
    {
        glUseProgram(m_components->cached_id);

        if (m_components->cached_id)
            m_components->cached_id = 0u;
    }

    shader::shader()
        : m_components(new shader::components)
    {
        runtime_error((m_components->render_id = glCreateProgram()), "opengl: glCreateProgram() failed!");
    }

    shader::~shader()
    {
        if (m_components->render_id)
            glDeleteProgram(m_components->render_id);

        m_components->render_id = 0u;
        m_components->cached_id = 0u;

        if (m_components)
            delete m_components;
        
        m_components = nullptr;
    }

    shader::shader(const char *a_vertex_source, const char *a_fragment_source) : shader()
    {
        compile_and_link(a_vertex_source, a_fragment_source, nullptr);
        debug_runtime_error(a_vertex_source && a_fragment_source, "invalid value: shader source should not be null!");
    }

    shader::shader(const char *a_vertex_source, const char *a_fragment_source, const char *a_geometry_source) : shader()
    {
        compile_and_link(a_vertex_source, a_fragment_source, a_geometry_source);
        debug_runtime_error(a_vertex_source && a_fragment_source && a_geometry_source, "invalid value: shader source should not be null!");
    }
    
    int32_t shader::get_uniform_location(const char *a_uniform_name) const
    {
        debug_runtime_error(a_uniform_name, "invalid value: uniform name should not be null!");
        
        if (m_components->uniform_location_cache.find(a_uniform_name) != m_components->uniform_location_cache.end())
            return m_components->uniform_location_cache[a_uniform_name];

        const int32_t UNIFORM_LOCATION = glGetUniformLocation(m_components->render_id, a_uniform_name);

        if (UNIFORM_LOCATION != -1)
            m_components->uniform_location_cache[a_uniform_name] = UNIFORM_LOCATION;

        return UNIFORM_LOCATION;
    }

    void shader::set_uniform_array_mat2x2(const char *a_uniform_name, const float *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniformMatrix2fv   (static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_matrices_count), static_cast<GLboolean>(a_transpose_matrices), static_cast<const GLfloat *>(a_matrices_data)); } }
    void shader::set_uniform_array_mat2x3(const char *a_uniform_name, const float *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniformMatrix2x3fv (static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_matrices_count), static_cast<GLboolean>(a_transpose_matrices), static_cast<const GLfloat *>(a_matrices_data)); } }
    void shader::set_uniform_array_mat2x4(const char *a_uniform_name, const float *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniformMatrix2x4fv (static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_matrices_count), static_cast<GLboolean>(a_transpose_matrices), static_cast<const GLfloat *>(a_matrices_data)); } }

    void shader::set_uniform_array_mat3x2(const char *a_uniform_name, const float *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniformMatrix3x2fv (static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_matrices_count), static_cast<GLboolean>(a_transpose_matrices), static_cast<const GLfloat *>(a_matrices_data)); } }
    void shader::set_uniform_array_mat3x3(const char *a_uniform_name, const float *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniformMatrix3fv   (static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_matrices_count), static_cast<GLboolean>(a_transpose_matrices), static_cast<const GLfloat *>(a_matrices_data)); } }
    void shader::set_uniform_array_mat3x4(const char *a_uniform_name, const float *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniformMatrix3x4fv (static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_matrices_count), static_cast<GLboolean>(a_transpose_matrices), static_cast<const GLfloat *>(a_matrices_data)); } }

    void shader::set_uniform_array_mat4x2(const char *a_uniform_name, const float *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniformMatrix4x2fv (static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_matrices_count), static_cast<GLboolean>(a_transpose_matrices), static_cast<const GLfloat *>(a_matrices_data)); } }
    void shader::set_uniform_array_mat4x3(const char *a_uniform_name, const float *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniformMatrix4x3fv (static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_matrices_count), static_cast<GLboolean>(a_transpose_matrices), static_cast<const GLfloat *>(a_matrices_data)); } }
    void shader::set_uniform_array_mat4x4(const char *a_uniform_name, const float *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniformMatrix4fv   (static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_matrices_count), static_cast<GLboolean>(a_transpose_matrices), static_cast<const GLfloat *>(a_matrices_data)); } }

    void shader::set_uniform_array_dmat2x2(const char *a_uniform_name, const double *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniformMatrix2dv     (static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_matrices_count), static_cast<GLboolean>(a_transpose_matrices), static_cast<const GLdouble *>(a_matrices_data)); } }
    void shader::set_uniform_array_dmat2x3(const char *a_uniform_name, const double *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniformMatrix2x3dv   (static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_matrices_count), static_cast<GLboolean>(a_transpose_matrices), static_cast<const GLdouble *>(a_matrices_data)); } }
    void shader::set_uniform_array_dmat2x4(const char *a_uniform_name, const double *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniformMatrix2x4dv   (static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_matrices_count), static_cast<GLboolean>(a_transpose_matrices), static_cast<const GLdouble *>(a_matrices_data)); } }

    void shader::set_uniform_array_dmat3x2(const char *a_uniform_name, const double *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniformMatrix3x2dv   (static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_matrices_count), static_cast<GLboolean>(a_transpose_matrices), static_cast<const GLdouble *>(a_matrices_data)); } }
    void shader::set_uniform_array_dmat3x3(const char *a_uniform_name, const double *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniformMatrix3dv     (static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_matrices_count), static_cast<GLboolean>(a_transpose_matrices), static_cast<const GLdouble *>(a_matrices_data)); } }
    void shader::set_uniform_array_dmat3x4(const char *a_uniform_name, const double *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniformMatrix3x4dv   (static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_matrices_count), static_cast<GLboolean>(a_transpose_matrices), static_cast<const GLdouble *>(a_matrices_data)); } }

    void shader::set_uniform_array_dmat4x2(const char *a_uniform_name, const double *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniformMatrix4x2dv   (static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_matrices_count), static_cast<GLboolean>(a_transpose_matrices), static_cast<const GLdouble *>(a_matrices_data)); } }
    void shader::set_uniform_array_dmat4x3(const char *a_uniform_name, const double *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniformMatrix4x3dv   (static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_matrices_count), static_cast<GLboolean>(a_transpose_matrices), static_cast<const GLdouble *>(a_matrices_data)); } }
    void shader::set_uniform_array_dmat4x4(const char *a_uniform_name, const double *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniformMatrix4dv     (static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_matrices_count), static_cast<GLboolean>(a_transpose_matrices), static_cast<const GLdouble *>(a_matrices_data)); } }
    
    void shader::set_uniform_array_vec2(const char *a_uniform_name, const float *a_vectors_data, uint32_t a_vectors_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniform2fv(static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_vectors_count), static_cast<const GLfloat *>(a_vectors_data)); } }
    void shader::set_uniform_array_vec3(const char *a_uniform_name, const float *a_vectors_data, uint32_t a_vectors_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniform3fv(static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_vectors_count), static_cast<const GLfloat *>(a_vectors_data)); } }
    void shader::set_uniform_array_vec4(const char *a_uniform_name, const float *a_vectors_data, uint32_t a_vectors_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniform4fv(static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_vectors_count), static_cast<const GLfloat *>(a_vectors_data)); } }

    void shader::set_uniform_array_dvec2(const char *a_uniform_name, const double *a_vectors_data, uint32_t a_vectors_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniform2dv(static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_vectors_count), static_cast<const GLdouble *>(a_vectors_data)); } }
    void shader::set_uniform_array_dvec3(const char *a_uniform_name, const double *a_vectors_data, uint32_t a_vectors_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniform3dv(static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_vectors_count), static_cast<const GLdouble *>(a_vectors_data)); } }
    void shader::set_uniform_array_dvec4(const char *a_uniform_name, const double *a_vectors_data, uint32_t a_vectors_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniform4dv(static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_vectors_count), static_cast<const GLdouble *>(a_vectors_data)); } }

    void shader::set_uniform_array_ivec2(const char *a_uniform_name, const int32_t *a_vectors_data, uint32_t a_vectors_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniform2iv(static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_vectors_count), static_cast<const GLint *>(a_vectors_data)); } }
    void shader::set_uniform_array_ivec3(const char *a_uniform_name, const int32_t *a_vectors_data, uint32_t a_vectors_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniform3iv(static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_vectors_count), static_cast<const GLint *>(a_vectors_data)); } }
    void shader::set_uniform_array_ivec4(const char *a_uniform_name, const int32_t *a_vectors_data, uint32_t a_vectors_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniform4iv(static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_vectors_count), static_cast<const GLint *>(a_vectors_data)); } }

    void shader::set_uniform_array_uvec2(const char *a_uniform_name, const uint32_t *a_vectors_data, uint32_t a_vectors_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniform2uiv(static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_vectors_count), static_cast<const GLuint *>(a_vectors_data)); } }
    void shader::set_uniform_array_uvec3(const char *a_uniform_name, const uint32_t *a_vectors_data, uint32_t a_vectors_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniform3uiv(static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_vectors_count), static_cast<const GLuint *>(a_vectors_data)); } }
    void shader::set_uniform_array_uvec4(const char *a_uniform_name, const uint32_t *a_vectors_data, uint32_t a_vectors_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniform4uiv(static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_vectors_count), static_cast<const GLuint *>(a_vectors_data)); } }

    void shader::set_uniform_array_bvec2(const char *a_uniform_name, const bool *a_vectors_data, uint32_t a_vectors_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniform2iv(static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_vectors_count), static_cast<const GLint *>(boolean_to_integer_array(a_vectors_data, a_vectors_count * 2u).data())); } }
    void shader::set_uniform_array_bvec3(const char *a_uniform_name, const bool *a_vectors_data, uint32_t a_vectors_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniform3iv(static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_vectors_count), static_cast<const GLint *>(boolean_to_integer_array(a_vectors_data, a_vectors_count * 3u).data())); } }
    void shader::set_uniform_array_bvec4(const char *a_uniform_name, const bool *a_vectors_data, uint32_t a_vectors_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniform4iv(static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_vectors_count), static_cast<const GLint *>(boolean_to_integer_array(a_vectors_data, a_vectors_count * 4u).data())); } }

    void shader::set_uniform_array(const char *a_uniform_name, const float      *a_array_of_data,   uint32_t a_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniform1fv    (static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_count), static_cast<const GLfloat   *>(a_array_of_data)); } }
    void shader::set_uniform_array(const char *a_uniform_name, const double     *a_array_of_data,   uint32_t a_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniform1dv    (static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_count), static_cast<const GLdouble  *>(a_array_of_data)); } }
    void shader::set_uniform_array(const char *a_uniform_name, const int32_t    *a_array_of_data,   uint32_t a_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniform1iv    (static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_count), static_cast<const GLint     *>(a_array_of_data)); } }
    void shader::set_uniform_array(const char *a_uniform_name, const uint32_t   *a_array_of_data,   uint32_t a_count) const { const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1) { glUniform1uiv   (static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_count), static_cast<const GLuint    *>(a_array_of_data)); } }
    void shader::set_uniform_array(const char *a_uniform_name, const bool       *a_array_of_data,   uint32_t a_count) const {
        
        const int32_t UNIFORM_LOCATION = get_uniform_location(a_uniform_name); if (UNIFORM_LOCATION != -1)
            glUniform1iv(static_cast<GLint>(UNIFORM_LOCATION), static_cast<GLsizei>(a_count), static_cast<const int32_t *>(boolean_to_integer_array(a_array_of_data, a_count).data()));
    }

    uint32_t shader::get_opengl_render_id() const
    {
        return m_components->render_id;
    }

    bool shader::compile_and_link(const char *a_vertex_source, const char *a_fragment_source, const char *a_geometry_source)
    {
        const uint32_t VERTEX_SHADER_ID =
            (a_vertex_source) ? glCreateShader(GL_VERTEX_SHADER) : 0u;

        const uint32_t FRAGMENT_SHADER_ID = (a_fragment_source) ? glCreateShader(GL_FRAGMENT_SHADER) : 0u;
        const uint32_t GEOMETRY_SHADER_ID = (a_geometry_source) ? glCreateShader(GL_GEOMETRY_SHADER) : 0u;
        
        auto compile_shader =
            [](uint32_t a_render_id, const char *a_source)
            {
                glShaderSource(a_render_id, 1, &a_source, nullptr);
                glCompileShader(a_render_id);
                
            #if defined(GPUCORE_DEBUG_ENABLED)

                int32_t compiled = 0;
                glGetShaderiv(a_render_id, GL_COMPILE_STATUS, &compiled);

                if (!compiled)
                {
                }

                return static_cast<bool>(compiled);

            #endif

                return true;
            };

        bool compiled = true;

        if (VERTEX_SHADER_ID)
            compiled = compiled && compile_shader(VERTEX_SHADER_ID, a_vertex_source);

        if (FRAGMENT_SHADER_ID)
            compiled = compiled && compile_shader(FRAGMENT_SHADER_ID, a_fragment_source);

        if (GEOMETRY_SHADER_ID)
            compiled = compiled && compile_shader(GEOMETRY_SHADER_ID, a_geometry_source);

    #if defined(GPUCORE_DEBUG_ENABLED)

        if (!compiled)
        {
        }

    #endif

        auto delete_shader =
            [](uint32_t a_shader_render_id)
            {
                if (a_shader_render_id)
                    glDeleteShader(a_shader_render_id);

                a_shader_render_id = 0u;
            };

        auto attach_shader =
            [](uint32_t a_program_render_id, uint32_t a_shader_render_id)
            {
                if (a_shader_render_id)
                {
                    glAttachShader(a_program_render_id, a_shader_render_id);
                }
            };

        auto detach_shader =
            [](uint32_t a_program_render_id, uint32_t a_shader_render_id)
            {
                if (a_shader_render_id)
                {
                    glDetachShader(a_program_render_id, a_shader_render_id);
                }
            };

        attach_shader(m_components->render_id, VERTEX_SHADER_ID);
        attach_shader(m_components->render_id, FRAGMENT_SHADER_ID);
        attach_shader(m_components->render_id, GEOMETRY_SHADER_ID);

            glLinkProgram(m_components->render_id);

        detach_shader(m_components->render_id, GEOMETRY_SHADER_ID);
        detach_shader(m_components->render_id, FRAGMENT_SHADER_ID);
        detach_shader(m_components->render_id, VERTEX_SHADER_ID);

    #if defined(GPUCORE_DEBUG_ENABLED)

        int32_t linked = 0;
        glGetProgramiv(m_components->render_id, GL_LINK_STATUS, &linked);

        if (!linked)
        {
        }

        return static_cast<bool>(linked);

    #endif

        delete_shader(VERTEX_SHADER_ID);
        delete_shader(FRAGMENT_SHADER_ID);
        delete_shader(GEOMETRY_SHADER_ID);

        return true;
    }
}
