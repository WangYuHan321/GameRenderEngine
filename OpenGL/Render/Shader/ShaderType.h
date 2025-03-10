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
	SHADER_INT_ARRAY,
	SHADER_FLOAT_ARRAY,
	SHADER_VEC2_ARRAY,
	SHADER_VEC3_ARRAY,
	SHADER_VEC4_ARRAY,
	SHADER_MAT2_ARRAY,
	SHADER_MAT3_ARRAY,
	SHADER_MAT4_ARRAY,
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
	//union
	//{
		bool BOOL;
		int INT;
		float FLOAT;
		glm::vec2 VEC2;
		glm::vec3 VEC3;
		glm::vec4 VEC4;
		glm::mat2 MAT2;
		glm::mat3 MAT3;
		glm::mat4 MAT4;
		std::vector<int32> INTS;
		std::vector<float> FLOATS;
		std::vector<Vector2> VEC2S;
		std::vector<Vector3> VEC3S;
		std::vector<Vector4> VEC4S;
		std::vector<Matrix2> MAT2S;
		std::vector<Matrix3> MAT3S;
		std::vector<Matrix4> MAT4S;
	//};
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