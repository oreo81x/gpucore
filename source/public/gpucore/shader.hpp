#pragma once

#include <gpucore/export.hpp>

namespace gpucore
{
    class GPUCORE_API shader
    {
    public:
        void attach() const;
        void detach() const;
        
    public:
         shader();
        ~shader();

        shader(const char *a_vertex_source, const char *a_fragment_source);
        shader(const char *a_vertex_source, const char *a_fragment_source, const char *a_geometry_source);
        
        int32_t get_uniform_location(const char *a_uniform_name) const;

        void set_uniform_array_mat2x2(const char *a_uniform_name, const float *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const;
        void set_uniform_array_mat2x3(const char *a_uniform_name, const float *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const;
        void set_uniform_array_mat2x4(const char *a_uniform_name, const float *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const;

        void set_uniform_array_mat3x2(const char *a_uniform_name, const float *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const;
        void set_uniform_array_mat3x3(const char *a_uniform_name, const float *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const;
        void set_uniform_array_mat3x4(const char *a_uniform_name, const float *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const;

        void set_uniform_array_mat4x2(const char *a_uniform_name, const float *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const;
        void set_uniform_array_mat4x3(const char *a_uniform_name, const float *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const;
        void set_uniform_array_mat4x4(const char *a_uniform_name, const float *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const;

        void set_uniform_array_dmat2x2(const char *a_uniform_name, const double *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const;
        void set_uniform_array_dmat2x3(const char *a_uniform_name, const double *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const;
        void set_uniform_array_dmat2x4(const char *a_uniform_name, const double *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const;

        void set_uniform_array_dmat3x2(const char *a_uniform_name, const double *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const;
        void set_uniform_array_dmat3x3(const char *a_uniform_name, const double *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const;
        void set_uniform_array_dmat3x4(const char *a_uniform_name, const double *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const;

        void set_uniform_array_dmat4x2(const char *a_uniform_name, const double *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const;
        void set_uniform_array_dmat4x3(const char *a_uniform_name, const double *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const;
        void set_uniform_array_dmat4x4(const char *a_uniform_name, const double *a_matrices_data, const bool &a_transpose_matrices, uint32_t a_matrices_count) const;

        void set_uniform_array_vec2(const char *a_uniform_name, const float *a_vectors_data, uint32_t a_vectors_count) const;
        void set_uniform_array_vec3(const char *a_uniform_name, const float *a_vectors_data, uint32_t a_vectors_count) const;
        void set_uniform_array_vec4(const char *a_uniform_name, const float *a_vectors_data, uint32_t a_vectors_count) const;

        void set_uniform_array_dvec2(const char *a_uniform_name, const double *a_vectors_data, uint32_t a_vectors_count) const;
        void set_uniform_array_dvec3(const char *a_uniform_name, const double *a_vectors_data, uint32_t a_vectors_count) const;
        void set_uniform_array_dvec4(const char *a_uniform_name, const double *a_vectors_data, uint32_t a_vectors_count) const;

        void set_uniform_array_ivec2(const char *a_uniform_name, const int32_t *a_vectors_data, uint32_t a_vectors_count) const;
        void set_uniform_array_ivec3(const char *a_uniform_name, const int32_t *a_vectors_data, uint32_t a_vectors_count) const;
        void set_uniform_array_ivec4(const char *a_uniform_name, const int32_t *a_vectors_data, uint32_t a_vectors_count) const;

        void set_uniform_array_uvec2(const char *a_uniform_name, const uint32_t *a_vectors_data, uint32_t a_vectors_count) const;
        void set_uniform_array_uvec3(const char *a_uniform_name, const uint32_t *a_vectors_data, uint32_t a_vectors_count) const;
        void set_uniform_array_uvec4(const char *a_uniform_name, const uint32_t *a_vectors_data, uint32_t a_vectors_count) const;

        void set_uniform_array_bvec2(const char *a_uniform_name, const bool *a_vectors_data, uint32_t a_vectors_count) const;
        void set_uniform_array_bvec3(const char *a_uniform_name, const bool *a_vectors_data, uint32_t a_vectors_count) const;
        void set_uniform_array_bvec4(const char *a_uniform_name, const bool *a_vectors_data, uint32_t a_vectors_count) const;

        void set_uniform_array(const char *a_uniform_name, const float      *a_array_of_floats,     uint32_t a_count) const;
        void set_uniform_array(const char *a_uniform_name, const double     *a_array_of_doubles,    uint32_t a_count) const;
        void set_uniform_array(const char *a_uniform_name, const int32_t    *a_array_of_ints,       uint32_t a_count) const;
        void set_uniform_array(const char *a_uniform_name, const uint32_t   *a_array_of_uints,      uint32_t a_count) const;
        void set_uniform_array(const char *a_uniform_name, const bool       *a_array_of_bools,      uint32_t a_count) const;

        uint32_t get_opengl_render_id() const;
        
    private:
        class components;

        const components *
            m_components = nullptr;

    private:
        bool compile_and_link(const char *a_vertex_source, const char *a_fragment_source, const char *a_geometry_source);
    };
}
