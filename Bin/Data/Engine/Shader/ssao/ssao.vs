#version 420 core

out vec2 TexCoords;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

void main()
{
    TexCoords = aTex;
    gl_Position = vec4(aPos, 1.0);
}

