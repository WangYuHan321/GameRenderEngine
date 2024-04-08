#shader vertex
#version 430 core

layout (location = 0) in vec3 geo_Pos;

/* Global information sent by the engine */
layout (std140) uniform EngineUBO
{
    mat4    ubo_Model;
    mat4    ubo_View;
    mat4    ubo_Projection;
    vec3    ubo_ViewPos;
    float   ubo_Time;
    mat4    ubo_UserMatrix;
};

void main()
{
    vec3 Position = vec3(ubo_Model * vec4(geo_Pos, 1.0));
    gl_Position = ubo_UserMatrix * vec4(Position, 1.0);
}

#shader fragment
#version 430 core

/* Global information sent by the engine */
layout (std140) uniform EngineUBO
{
    mat4    ubo_Model;
    mat4    ubo_View;
    mat4    ubo_Projection;
    vec3    ubo_ViewPos;
    float   ubo_Time;
    mat4    ubo_UserMatrix;
};

/* Light information sent by the engine */
layout(std430, binding = 0) buffer LightSSBO
{
    mat4 ssbo_Lights[];
};

layout (location = 0) out vec4 light_depth;

void main()
{
    light_depth = vec4(gl_FragCoord.z, gl_FragCoord.z, gl_FragCoord.z, 0);
}