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
	vs_out.FragPos = vec3(ubo_Model * vec4(geo_Pos, 1.0));
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

std::pair<std::string, std::string> RawShader::GetGrizmo()
{
	std::pair<std::string, std::string> source;

	source.first = R"(
#version 430 core

layout (location = 0) in vec3 geo_Pos;
layout (location = 1) in vec2 geo_TexCoord;
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
	vec3 Color;
} vs_out;

uniform bool u_IsBall; //球 
uniform bool u_IsPickable; //被鼠标选择并可以移动
uniform int u_HighlightedAxis;//高亮的移动轴

mat4 rotationMatrix(vec3 axis, float angle)
{
	axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;
    
    return mat4
    (
        oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
        oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
        oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
        0.0,                                0.0,                                0.0,                                1.0
    );
}

void main()
{
	mat4 instanceModel = ubo_Model;
	
	if (gl_InstanceID == 1)
		instanceModel = instanceModel * rotationMatrix(vec3(0, 1, 0), radians(-90)); //X
	else if (gl_InstanceID == 2)
		instanceModel = instanceModel * rotationMatrix(vec3(1, 0, 0), radians(90)); //Y

	float distanceToCamera = distance(ubo_ViewPos, vec3(instanceModel[3][0], instanceModel[3][1], instanceModel[3][2]));

	vec3 pos = geo_Pos;

	vec3 fragPos = vec3(instanceModel * vec4(pos * distanceToCamera * 0.1f, 1.0f));

	if(u_IsPickable)//如果当前是选中
	{
		int blueComponent = 0;
		
		if(gl_InstanceID == 1)
			blueComponent = 252;
	
		if(gl_InstanceID == 2)
			blueComponent = 253;	

		if(gl_InstanceID == 0)
			blueComponent = 254;
		
		vs_out.Color = vec3(1.0f, 1.0f, blueComponent / 255.0f);
	}
	else
	{
		if(u_IsBall)
		{
			vs_out.Color = vec3(1.0f);
		}
		else
		{
			float red	= float(gl_InstanceID == 1); // X
			float green = float(gl_InstanceID == 2); // Y
			float blue	= float(gl_InstanceID == 0); // Z

			if (!u_IsPickable && ((gl_InstanceID == 1 && u_HighlightedAxis == 0) || (gl_InstanceID == 2 && u_HighlightedAxis == 1) || (gl_InstanceID == 0 && u_HighlightedAxis == 2)))
			{
				vs_out.Color = vec3(1.0f, 1.0f, 0.0f);
			}	
			else
			{
				vs_out.Color = vec3(red, green, blue);
			}
		}
	}
	    gl_Position = ubo_Projection * ubo_View * vec4(fragPos, 1.0);
}
		)";

	source.second = R"(
	#version 430 core

	out vec4 FRAGMENT_COLOR;

	in VS_OUT
	{
		vec3 Color;
	} fs_in;

	uniform bool u_IsPickable;

	void main()
	{
		FRAGMENT_COLOR = vec4(fs_in.Color, 1.0f);
	})";
	
	return source;
}

std::pair<std::string, std::string> RawShader::GetBillboard()
{
	std::pair<std::string, std::string> source;

	source.first = R"(
#version 430 core

layout (location = 0) in vec3 geo_Pos;
layout (location = 1) in vec2 geo_TexCoords;
layout (location = 2) in vec3 geo_Normal;

layout (std140) uniform EngineUBO
{
    mat4    ubo_Model;
    mat4    ubo_View;
    mat4    ubo_Projection;
    vec3    ubo_ViewPos;
    float   ubo_Time;
};

out VS_OUT
{
    vec2 TexCoords;
} vs_out;

uniform float u_Scale = 1.0f;

void main()
{
    vs_out.TexCoords = geo_TexCoords;

    mat4 model = ubo_Model;
	float distanceToCamera = distance(ubo_ViewPos, model[3].xyz);

    gl_Position = ubo_Projection * ubo_View * ubo_Model * vec4(geo_Pos * distanceToCamera * u_Scale, 1.0);
})";

	source.second = R"(
#version 430 core

out vec4 FRAGMENT_COLOR;

in VS_OUT
{
    vec2 TexCoords;
} fs_in;

uniform vec4        u_Diffuse = vec4(1.0, 1.0, 1.0, 1.0);
uniform sampler2D   u_DiffuseMap;
uniform vec2        u_TextureTiling = vec2(1.0, 1.0);
uniform vec2        u_TextureOffset = vec2(0.0, 0.0);

void main()
{
    FRAGMENT_COLOR = texture(u_DiffuseMap, u_TextureOffset + vec2(mod(fs_in.TexCoords.x * u_TextureTiling.x, 1), mod(fs_in.TexCoords.y * u_TextureTiling.y, 1))) * u_Diffuse;
})";

	return source;
}

std::pair<std::string, std::string> RawShader::GetShadow()
{
	std::pair<std::string, std::string> source;

	source.first = R"(
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
})";

	source.second = R"(
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
})";

	return source;
}

std::pair<std::string, std::string> RawShader::GetFont()
{
	std::pair<std::string, std::string> source;

	source.first = R"(
#version 430 core

layout (location = 0) in vec3 geo_Pos;
layout (location = 1) in vec2 geo_TexCoords;

out VS_OUT
{
    vec2 TexCoords;
} vs_out;

/* Global information sent by the engine */
layout (std140) uniform EngineUBO
{
    mat4    ubo_Model;
    mat4    ubo_View;
    mat4    ubo_Projection;
    vec3    ubo_ViewPos;
    float   ubo_Time;
};

void main()
{
	vs_out.TexCoords = geo_TexCoords;
    vec3 Position = vec3(ubo_Model * vec4(geo_Pos, 1.0));
    gl_Position = ubo_Projection * ubo_View * vec4(Position, 1.0);
})";

	source.second = R"(
#version 430 core

layout (std140) uniform EngineUBO
{
    mat4    ubo_Model;
    mat4    ubo_View;
    mat4    ubo_Projection;
    vec3    ubo_ViewPos;
    float   ubo_Time;
};

uniform sampler2D font_texture;

in VS_OUT
{
	vec2 TexCoords;
} fs_in;

/* Light information sent by the engine */
layout(std430, binding = 0) buffer LightSSBO
{
    mat4 ssbo_Lights[];
};

out vec4 FRAG_COLOR;

void main()
{
	vec4 pixelColor = texture(font_texture, fs_in.TexCoords);
    FRAG_COLOR = pixelColor;
})";

	return source;
}
