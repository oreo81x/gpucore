R"(
#version 410 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_uv_map;

out vec3 v_position;
out vec3 v_normal;
out vec2 v_uv_map;

uniform mat4x4 u_model_matrix  = mat4x4(1.0);
uniform mat4x4 u_view_matrix   = mat4x4(1.0);
uniform mat4x4 u_clip_matrix   = mat4x4(1.0);

void main()
{
    gl_Position = u_clip_matrix * u_view_matrix * u_model_matrix * vec4(a_position, 1.0);

    v_position  = a_position;
    v_normal    = a_normal;
    v_uv_map    = a_uv_map;
}
)";