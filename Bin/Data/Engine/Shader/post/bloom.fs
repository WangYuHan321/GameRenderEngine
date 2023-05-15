#version 420 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D HDRScene;

void main()
{  
    vec3 hdrColor = texture(HDRScene, TexCoords).rgb;
    FragColor.rgb = 0.1 * hdrColor;
    FragColor.a = 1.0;
}

