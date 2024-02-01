#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <gpucore/opengl.hpp>
#include <GLFW/glfw3.h>

namespace sandbox
{
    struct camera
    {
        camera(float a_aspect_ratio)
            : aspect_ratio(a_aspect_ratio)
        {
        }

        glm::mat4x4 get_view_matrix() const
        {
            return glm::lookAtRH(center, center + orient, upward);
        }
        
        glm::mat4x4 get_clip_matrix() const
        {
            return glm::perspective(field_of_view, aspect_ratio, nearest, farest);
        }

        glm::vec3 upward = glm::vec3(0.0f, 1.0f,  0.0f);
        glm::vec3 orient = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 center = glm::vec3(0.0f, 0.0f,  5.0f);

        float aspect_ratio  = 0.0f;
        float field_of_view = 0.7f;
        float nearest   = 000.1f;
        float farest    = 100.0f;
        
        bool    first_click = true;
        float   sensitivity = 70.0f;
    };

    void camera_board_input(GLFWwindow *a_window, camera *a_camera)
    {
        if (glfwGetKey(a_window, GLFW_KEY_W) == GLFW_PRESS) { a_camera->center += 0.1f *  a_camera->orient; }
        if (glfwGetKey(a_window, GLFW_KEY_S) == GLFW_PRESS) { a_camera->center += 0.1f * -a_camera->orient; }

        if (glfwGetKey(a_window, GLFW_KEY_A) == GLFW_PRESS) { a_camera->center += 0.1f * -glm::normalize(glm::cross(a_camera->orient, a_camera->upward)); }
        if (glfwGetKey(a_window, GLFW_KEY_D) == GLFW_PRESS) { a_camera->center += 0.1f *  glm::normalize(glm::cross(a_camera->orient, a_camera->upward)); }

        if (glfwGetKey(a_window, GLFW_KEY_Q) == GLFW_PRESS) { a_camera->center += 0.1f *  a_camera->upward; }
        if (glfwGetKey(a_window, GLFW_KEY_E) == GLFW_PRESS) { a_camera->center += 0.1f * -a_camera->upward; }
    }

    void camera_mouse_input(GLFWwindow *a_window, camera *a_camera)
    {
        int32_t window_size_x = 0;
        int32_t window_size_y = 0;
        glfwGetWindowSize(a_window, &window_size_x, &window_size_y);

        if (glfwGetMouseButton(a_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
            glfwSetInputMode(a_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

            if (a_camera->first_click)
            {
                glfwSetCursorPos(a_window, window_size_x / 2, window_size_y / 2);
                a_camera->first_click = false;
            }

            double cursor_x = 0.0;
            double cursor_y = 0.0;

            glfwGetCursorPos(a_window, &cursor_x, &cursor_y);

            float pitch = a_camera->sensitivity * (float)(cursor_y - (window_size_y / 2)) / window_size_y;
            float yaw   = a_camera->sensitivity * (float)(cursor_x - (window_size_x / 2)) / window_size_x;

            glm::vec3 new_orient
                = glm::rotate(a_camera->orient, glm::radians(-pitch), glm::normalize(glm::cross(a_camera->orient, a_camera->upward)));

            if (!((glm::angle(new_orient, a_camera->upward) <= glm::radians(5.0f)) or (glm::angle(new_orient, -a_camera->upward) <= glm::radians(5.0f))))
                a_camera->orient = new_orient;

            a_camera->orient =
                glm::rotate(a_camera->orient, glm::radians(-yaw), a_camera->upward);

            glfwSetCursorPos(a_window, window_size_x / 2, window_size_y / 2);
        }
        else if (glfwGetMouseButton(a_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
        {
            glfwSetInputMode(a_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            a_camera->first_click = true;
        }
    }
}
