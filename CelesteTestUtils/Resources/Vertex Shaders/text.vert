#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 tex;

out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    TexCoords = tex;
    gl_Position = projection * view * model * vec4(position, 0, 1.0);
}  