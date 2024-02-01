#include <gpucore/camera.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace gpucore
{
    class camera::components
    {
    public:
        mutable glm::mat4x4 view_matrix = glm::mat4x4(1.0f);
        mutable glm::mat4x4 clip_matrix = glm::mat4x4(1.0f);

        mutable glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
        mutable glm::vec3 orient = glm::vec3(0.0f, 0.0f, 0.0f);
        mutable glm::vec3 upward = glm::vec3(0.0f, 1.0f, 0.0f);
        
        mutable bool view_matrix_need_update = true;
        mutable bool clip_matrix_need_update = true;

        mutable float field_of_view = 0.0f;
        mutable float aspect_ratio  = 0.0f;
        mutable float near_plane    = 0.0f;
        mutable float far_plane     = 0.0f;
    };

    camera::camera()
        : m_components(new camera::components)
    {
    }

    camera::~camera()
    {
        if (m_components)
            delete m_components;

        m_components = nullptr;
    }

    const float *camera::get_view_matrix() const
    {
        if (m_components->view_matrix_need_update)
        {
            m_components->view_matrix =
                glm::lookAt(m_components->center, m_components->orient - m_components->center, m_components->upward);

            m_components->view_matrix_need_update = false;
        }

        return &m_components->view_matrix[0][0];
    }
    
    const float *camera::get_clip_matrix() const
    {
        if (m_components->clip_matrix_need_update)
        {
            m_components->clip_matrix =
                glm::perspective(m_components->field_of_view, m_components->aspect_ratio, m_components->near_plane, m_components->far_plane);

            m_components->clip_matrix_need_update = false;
        }
        
        return &m_components->clip_matrix[0][0];
    }

    camera::camera(float a_aspect_ratio, float a_field_of_view_in_radians, float a_near_plane, float a_far_plane, const float *a_center, const float *a_orient)
        : camera()
    {
        float center[3];
        float orient[3];

        if (a_center)
            for (int8_t i = 0; i < 3; i++)
            {
                center[i] = a_center[i];
            }
        else {
            center[0] = 0.0f;
            center[1] = 0.0f;
            center[2] = 4.0f;
        }

        if (a_orient)
            for (int8_t i = 0; i < 3; i++)
            {
                orient[i] = a_orient[i];
            }
        else {
            orient[0] =  0.0f;
            orient[1] =  0.0f;
            orient[2] = -1.0f;
        }

        m_components->center = glm::vec3(center[0], center[1], center[2]);
        m_components->orient = glm::vec3(orient[0], orient[1], orient[2]);
        
        m_components->field_of_view = a_field_of_view_in_radians;
        m_components->aspect_ratio = a_aspect_ratio;

        m_components->near_plane = a_near_plane;
        m_components->far_plane = a_far_plane;
    }
}
