#include <iostream>

#include <sandbox/camera.hpp>
#include <sandbox/object.hpp>

#include <gpucore.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <GLFW/glfw3.h>

#include <vector>
#include <string>

class GLFWinitializer
{
public:
    GLFWinitializer()
    {
    #if !defined(NDEBUG)

        int32_t glfw_init_succeeded =

    #endif

        glfwInit();

    #if !defined(NDEBUG)

        if (!glfw_init_succeeded)
            throw std::runtime_error("glfwInit() function failed!");

    #endif
    }

    ~GLFWinitializer()
    {
        glfwTerminate();
    }
};

const char *SIMPLE_VERTEX_SOURCE =
    #include <sandbox/shaders/minimal.vert.glsl>

const char *SIMPLE_FRAGMENT_SOURCE =
    #include <sandbox/shaders/minimal.frag.glsl>

int main()
{
    // initalizing glfw with object because i want if a val returned the destructor
    GLFWinitializer glfw_init_object;   // will call glfwTerminate() automatically.

            GLFWmonitor *monitor = glfwGetPrimaryMonitor(  );
    const   GLFWvidmode *vidmode = glfwGetVideoMode(monitor);

    // ______________________________________________________________________
    // set glfw window creation hint using glfwWindowHint function.

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GPUCORE_OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GPUCORE_OPENGL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DECORATED, 1);
    glfwWindowHint(GLFW_RESIZABLE, 0);

    glfwWindowHint(GLFW_RED_BITS,       vidmode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS,     vidmode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS,      vidmode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE,   vidmode->refreshRate);

    // ______________________________________________________________________
    // creating the window object.

    int32_t window_width    = 900;
    int32_t window_height   = 800;

    GLFWwindow *window =
        glfwCreateWindow(window_width, window_height, "gpucore-sandbox-application", nullptr, nullptr);

    if (!window)
        throw std::runtime_error("glfwCreateWindow(...) function failed!");
    

    // ______________________________________________________________________
    // creating opengl context with the window and set opengl viewport.

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, window_width, window_height);

    glfwSetWindowPos(window, (vidmode->width / 2) - (window_width / 2), (vidmode->height / 2) - (window_height / 2));
    
    // ______________________________________________________________________
    // enabling opengl stuff here.
    
    glEnable(GL_DEPTH_TEST);

    // ______________________________________________________________________
    // create (shader, texture and ...) objects.

    gpucore::shader simple_shader =
        gpucore::shader(SIMPLE_VERTEX_SOURCE, SIMPLE_FRAGMENT_SOURCE);

    // the greate camera that i made from victor gordan camera tutorial on youtube.
    sandbox::camera camera =
        sandbox::camera(static_cast<float>(window_width) / static_cast<float>(window_height));
    
    sandbox::object skybox  = sandbox::cube("assets/galaxy.png");
    sandbox::object cube    = sandbox::cube("assets/image.jpg");
    
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        simple_shader.attach();
            simple_shader.set_uniform_array_mat4x4("u_view_matrix", &camera.get_view_matrix()[0][0], false, 1u);
            simple_shader.set_uniform_array_mat4x4("u_clip_matrix", &camera.get_clip_matrix()[0][0], false, 1u);
        simple_shader.detach();

        glDepthMask(GL_FALSE);
            sandbox::draw(simple_shader, skybox);
        glDepthMask(GL_TRUE);

        sandbox::draw(simple_shader, cube);

        glfwSwapBuffers(window);
        glfwSwapInterval(1);

        glfwPollEvents();

        sandbox::camera_board_input(window, &camera);
        sandbox::camera_mouse_input(window, &camera);
        
        skybox.set_center(camera.center);
    }

    return 0;
}

/*
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
*/