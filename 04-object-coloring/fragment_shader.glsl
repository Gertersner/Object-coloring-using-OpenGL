#version 330 core

in vec4 position;
in vec4 s_color;

out vec4 FragColor;

void main()
{
    vec4 fColor = vec4(1.0);

    if (position.x - position.y < 0.0) fColor.r = 0.25;
    if (position.y - position.z < 0.0) fColor.g = 0.25;
    if (position.z - position.x < 0.0) fColor.b = 0.25;

    fColor *= s_color;

    FragColor = fColor;
}
