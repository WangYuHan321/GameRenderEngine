#include "../../Util/common.h"
#include "Texture.h"
#include "TextureCube.h"

enum SHADER_TYPE
{
	SHADER_NONE,
	SHADER_BOOL,
	SHADER_INT,
	SHADER_FLOAT,
	SHADER_SAMPLER1D,
	SHADER_SAMPLER2D,
	SHADER_SAMPLER3D,
	SHADER_SAMPLERCUBE,
	SHADER_VEC2,
	SHADER_VEC3,
	SHADER_VEC4,
	SHADER_MAT2,
	SHADER_MAT3,
	SHADER_MAT4,
};

struct Uniform {
	SHADER_TYPE Type;
	string Name;
	uint32 Size;
	uint32 Location;
};

struct VertexAttr {
	SHADER_TYPE Type;
	string Name;
	uint32 Size;
	uint32 Location;
};

struct UniformValue
{
	SHADER_TYPE Type;
	union
	{
		bool BOOL;
		int INT;
		float FLOAT;
		glm::vec2 VEC2;
		glm::vec3 VEC3;
		glm::vec4 VEC4;
		glm::mat2 MAT2;
		glm::mat3 MAT3;
		glm::mat4 MAT4;
	};
	UniformValue() {}
};



struct UniformSampler {
	SHADER_TYPE Type;
	int32 ID;
	union {
		Texture* TEXTURE;
		TextureCube* TEXTURE_CUBE;
	};
	UniformSampler() {}
};