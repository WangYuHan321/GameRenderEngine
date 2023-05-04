#version 420 core
out vec4 FragColor;
in vec3 WorldPos;

#include ../common/constants.glsl
#include ../common/sampling.glsl

//采样点
uniform samplerCube environment;

void main()
{
    vec3 N = normalize(WorldPos);

    //切线空间
    vec3 up = vec3(0.0, 1.0, 0.0);
    vec3 right = cross(up, N);
    up         = cross(N, right);

    vec3 irradiance = vec3(0.0);
	int samples = 0;

    float sampleDelta = 0.025f;

    for(float phi = 0.0; phi < 2.0*PI; phi += sampleDelta)
    {
        for(float theta = 0.0; theta < 0.5*PI; theta += sampleDelta)
        {
            vec3 tangentSample = vec3(cos(phi) * sin(theta), sin(phi) * sin(theta), cos(theta));
            vec3 sampleVec = tangentSample.x * right + tangentSample.y * up + tangentSample.z * N;
            irradiance += texture(environment, sampleVec).rgb * cos(theta) * sin(theta);
            samples++;
        }
    }
    irradiance = PI * irradiance * (1.0 / float(samples));

    FragColor = vec4(irradiance, 1.0);
}