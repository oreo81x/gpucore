#pragma once

#include <gpucore.hpp>
#include <glm/glm.hpp>

#include <vector>
#include <memory>

#define safe_delete(a_pointer) if (a_pointer) { delete a_pointer; a_pointer = nullptr; }

namespace sandbox
{
    class drawable
    {
    public:
        virtual void draw(gpucore::shader &a_shader) const = 0;
    };
    void draw(gpucore::shader &a_shader, const drawable &a_object) { a_object.draw(a_shader); }


    struct vertex
    {
        glm::vec3 position  = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 normal    = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec2 uv_map    = glm::vec2(0.0f, 0.0f);

        vertex(glm::vec3 a_position, glm::vec3 a_normal, glm::vec2 a_uv_map)
            : position(a_position), normal(a_normal), uv_map(a_uv_map)
        {
        }
    };


    class object : public drawable
    {
    public:
         object();
        ~object();

        object(object &&a_other)
        {
            std::swap(m_tex, a_other.m_tex);
            std::swap(m_vao, a_other.m_vao);
            std::swap(m_vbo, a_other.m_vbo);
            std::swap(m_ebo, a_other.m_ebo);

            std::swap(m_count_vertices, a_other.m_count_vertices);
            std::swap(m_count_elements, a_other.m_count_elements);
            
            std::swap(m_color, a_other.m_color);
            std::swap(m_scale, a_other.m_scale);
            std::swap(m_center, a_other.m_center);
            std::swap(m_rotation, a_other.m_rotation);
        }

        object(const char *a_texture_image_file_path,   const vertex    *a_data_vertices, uint32_t a_count_vertices);
        object(const char *a_texture_image_file_path,   const vertex    *a_data_vertices, uint32_t a_count_vertices,
                                                        const uint32_t  *a_data_elements, uint32_t a_count_elements);
        
        void draw(gpucore::shader &a_shader) const override
        {
            glm::mat4x4 model_matrix =
                glm::scale(glm::mat4x4(1.0f), m_scale) * glm::mat4_cast(m_rotation) * glm::translate(glm::mat4x4(1.0f), m_center);

            m_tex->attach();
            m_vao->attach();
            a_shader.attach();

                a_shader.set_uniform_array_mat4x4   ("u_model_matrix",  &model_matrix[0][0], false, 1u);
                a_shader.set_uniform_array_vec4     ("u_model_color",   &m_color        [0],        1u);

                if (m_count_elements == 0u)
                    glDrawArrays(GL_TRIANGLES, 0, m_count_vertices);
                else {
                    glDrawElements(GL_TRIANGLES, m_count_elements, GL_UNSIGNED_INT, (const void *)0);
                }
                
            a_shader.detach();
            m_vao->detach();
            m_tex->detach();
        }

        void set_color(glm::vec4 a_color) { m_color = a_color; }
        void set_scale(glm::vec3 a_scale) { m_scale = a_scale; }

        void set_center(glm::vec3 a_center) { m_center = a_center; }
        void set_rotation(glm::quat a_rotation) { m_rotation = a_rotation; }

        glm::vec4 get_color     () const { return m_color; }
        glm::vec3 get_scale     () const { return m_scale; }
        glm::vec3 get_center    () const { return m_center;     }
        glm::quat get_rotation  () const { return m_rotation;   }

        void scale  (glm::vec3 a_scale)     { set_scale     (m_scale    + a_scale   ); }
        void move   (glm::vec3 a_vilocity)  { set_center    (m_center   + a_vilocity); }
        void rotate (glm::quat a_rotation)  { set_rotation  (m_rotation * a_rotation); }

    private:
        glm::vec4 m_color     = glm::vec4(1.0f);
        glm::vec3 m_scale     = glm::vec3(1.0f);
        glm::vec3 m_center    = glm::vec3(0.0f);
        glm::quat m_rotation  =
            glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
        
        gpucore::texture        *m_tex = nullptr;
        gpucore::vertex_array   *m_vao = nullptr;
        gpucore::vertex_buffer  *m_vbo = nullptr;
        gpucore::element_buffer *m_ebo = nullptr;

        std::size_t m_count_vertices = 0u;
        std::size_t m_count_elements = 0u;
    };

    object:: object() = default;
    object::~object()
    {
        safe_delete(m_tex);
        safe_delete(m_vao);
        safe_delete(m_vbo);
        safe_delete(m_ebo);

        m_count_vertices = 0u;
        m_count_elements = 0u;
    }

    object::object(const char *a_texture_image_file_path, const vertex *a_data_vertices, uint32_t a_count_vertices)
        : m_count_vertices(a_count_vertices)
    {
        if (!a_data_vertices || !a_count_vertices)
            throw std::runtime_error("object::object constructor can not accept null for any of it's arguments!");

        m_tex = new gpucore::texture(a_texture_image_file_path);
        m_vao = new gpucore::vertex_array   ();
        m_vbo = new gpucore::vertex_buffer  ((const float *)a_data_vertices, a_count_vertices * sizeof(vertex));

        m_vao->link(*m_vbo, gpucore::vertex_layout(0u, 3u, sizeof(vertex), (const void *)offsetof(vertex, position)));
        m_vao->link(*m_vbo, gpucore::vertex_layout(1u, 3u, sizeof(vertex), (const void *)offsetof(vertex, normal)));
        m_vao->link(*m_vbo, gpucore::vertex_layout(2u, 2u, sizeof(vertex), (const void *)offsetof(vertex, uv_map)));
    }

    object::object(const char *a_texture_image_file_path, const vertex *a_data_vertices, uint32_t a_count_vertices, const uint32_t *a_data_elements, uint32_t a_count_elements)
        : object(a_texture_image_file_path, a_data_vertices, a_count_vertices)
    {
        if (!a_data_elements || !a_count_elements)
            throw std::runtime_error("object::object constructor can not accept null for any of it's arguments!");

        m_ebo = new gpucore::element_buffer(a_data_elements, (m_count_elements = a_count_elements) * sizeof(uint32_t));
        m_vao->link(*m_ebo);
    }

}

namespace sandbox
{
    std::vector<sandbox::vertex> gen_cube_vertices()
    {
        std::vector<sandbox::vertex> data =
        {
            sandbox::vertex(glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 1.0f)),
            sandbox::vertex(glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 0.0f)),
            sandbox::vertex(glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 0.0f)),
            sandbox::vertex(glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 1.0f)),
            sandbox::vertex(glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 1.0f)),
            sandbox::vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 0.0f)),
            sandbox::vertex(glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 0.0f)),
            sandbox::vertex(glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 1.0f)),
            sandbox::vertex(glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(1.0f, 0.0f)),
            sandbox::vertex(glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(0.0f, 1.0f)),
            sandbox::vertex(glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(1.0f, 1.0f)),
            sandbox::vertex(glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(0.0f, 0.0f)),
            sandbox::vertex(glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(1.0f, 0.0f)),
            sandbox::vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(0.0f, 1.0f)),
            sandbox::vertex(glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(1.0f, 1.0f)),
            sandbox::vertex(glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(0.0f, 0.0f)),
            sandbox::vertex(glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(1.0f, 1.0f)),
            sandbox::vertex(glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(0.0f, 0.0f)),
            sandbox::vertex(glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(1.0f, 0.0f)),
            sandbox::vertex(glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(0.0f, 1.0f)),
            sandbox::vertex(glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(1.0f, 1.0f)),
            sandbox::vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(0.0f, 0.0f)),
            sandbox::vertex(glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(1.0f, 0.0f)),
            sandbox::vertex(glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(0.0f, 1.0f)),
        };
    
        return data;
    }

    std::vector<uint32_t> gen_cube_elements()
    {
        std::vector<uint32_t> data =
        {
            0u, 1u, 2u,
            0u, 1u, 3u,

            4u, 5u, 6u,
            4u, 5u, 7u,

            8u, 9u, 10u,
            8u, 9u, 11u,

            12u, 13u, 14u,
            12u, 13u, 15u,

            16u, 17u, 18u,
            16u, 17u, 19u,

            20u, 21u, 22u,
            20u, 21u, 23u
        };

        return data;
    }

    object cube(const char *a_texture_image_file_path)
    {
        std::vector<vertex>     vertices = gen_cube_vertices();
        std::vector<uint32_t>   elements = gen_cube_elements();
        
        return object(a_texture_image_file_path, vertices.data(), vertices.size(), elements.data(), elements.size());
    }
}
