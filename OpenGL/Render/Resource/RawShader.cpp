#include "RawShader.h"

std::pair<std::string, std::string>  RawShader::GetGrid()
{
	std::pair<std::string, std::string> source;

	source.first = R"(
#version 430 core

layout (location = 0) in vec3 geo_Pos;
layout (location = 1) in vec2 geo_TexCoords;
layout (location = 2) in vec3 geo_Normal;

layout (std140) uniform EngineUBO
{
	mat4 ubo_Model;
	mat4 ubo_View;
	mat4 ubo_Projection;
	vec3 ubo_ViewPos;
	float ubo_Time; 
};	

out VS_OUT
{
	vec3 FragPos;
	vec2 TexCoords;
} vs_out;

void main()
{
	vs_out.FragPos = vec3(ubo_Model *  vec4(geo_Pos, 1.0));
	vs_out.TexCoords = vs_out.FragPos.xz;

	gl_Position = ubo_Projection * ubo_View * vec4(vs_out.FragPos, 1.0);
}

)";

	source.second = R"(
#version 430 core

out vec4 FRAGMENT_COLOR;

layout (std140) uniform EngineUBO
{
    mat4    ubo_Model;
    mat4    ubo_View;
    mat4    ubo_Projection;
    vec3    ubo_ViewPos;
    float   ubo_Time;
};

in VS_OUT
{
    vec3 FragPos;
    vec2 TexCoords;
} fs_in;

uniform vec3 u_Color;

float MAG(float p_lp)
{
  const float lineWidth = 1.0f;

  const vec2 coord       = fs_in.TexCoords / p_lp;
  const vec2 grid        = abs(fract(coord - 0.5) - 0.5) / fwidth(coord);
  const float line       = min(grid.x, grid.y);
  const float lineResult = lineWidth - min(line, lineWidth);

  return lineResult;
}

float Grid(float height, float a, float b, float c)
{
  const float cl   = MAG(a);
  const float ml   = MAG(b);
  const float fl   = MAG(c);

  const float cmit =  10.0f;
  const float cmet =  40.0f;
  const float mfit =  80.0f;
  const float mfet =  160.0f;

  const float df   = clamp((height - cmit) / (cmet - cmit), 0.0f, 1.0f);
  const float dff  = clamp((height - mfit) / (mfet - mfit), 0.0f, 1.0f);

  const float inl  = mix(cl, ml, df);
  const float fnl  = mix(inl, fl, dff);

  return fnl;
}

void main()
{
  const float height = distance(ubo_ViewPos.y, fs_in.FragPos.y);

  const float gridA = Grid(height, 1.0f, 4.0f, 8.0f);
  const float gridB = Grid(height, 4.0f, 16.0f, 32.0f);

  const float grid  = gridA * 0.5f + gridB;

  const vec2  viewdirW    = ubo_ViewPos.xz - fs_in.FragPos.xz;
  const float viewdist    = length(viewdirW);
  
  FRAGMENT_COLOR = vec4(u_Color, grid);
}
)";
	return source;
}