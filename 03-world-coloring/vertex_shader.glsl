#version 330 core

in vec4 b_position;
in vec4 b_color;

out vec4 position;
out vec4 s_color;

uniform mat4 u_transform;

void main()
{
    s_color = b_color;
    gl_Position = u_transform * b_position;
    position = gl_Position;
}
