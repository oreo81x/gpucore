R"(
#version 410 core

in vec3 v_position;
in vec3 v_normal;
in vec2 v_uv_map;

out vec4 FragColor;

uniform sampler2D   u_texture_unit;
uniform vec4        u_model_color = vec4(1.0);

void main()
{
    FragColor = texture(u_texture_unit, v_uv_map) * u_model_color;
}
)";