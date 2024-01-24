#version 420 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D GBufferTexture;

void main()
{  
    FragColor = texture(GBufferTexture, TexCoords);
}

