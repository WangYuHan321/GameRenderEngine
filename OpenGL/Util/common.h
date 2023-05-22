#pragma once
#include<GL/glew.h>
#include<GLM/glm.hpp>
#include<GLFW/glfw3.h>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include<intrin.h>
#include<map>
#include"string_id.hpp"
#include"../Log/Logger.h"
#include"../ThirdLib/ImGui/imgui.h"
#include"../ThirdLib/ImGui/imgui_internal.h"

#define MSAA_NUM 4

#define DUMP_FILE L"C://dump.dmp" 

typedef unsigned int uint32;
typedef int int32;
typedef unsigned __int64 uint64;
typedef __int64 int64;  
typedef std::string string;

namespace EasyGraphics {

#ifdef _DEBUG
	#include"new_on.h"
	#include"MemoryManager.h"
#else

#endif // DEBUG
	struct EWINDOWINFO
	{
		uint32 WINDOW_WIDTH;
		uint32 WINDOW_HEIGHT;
		string WINDOW_TITLE;

		EWINDOWINFO(uint32 width, uint32 height, string title) :
			WINDOW_WIDTH(width), WINDOW_HEIGHT(height), WINDOW_TITLE(title)
		{}
	};

	struct EINPUTMODEL
	{
		bool INPUT_CURSOUR_DISABLE;
		bool INPUT_KEYWORD_DISABLE;

		EINPUTMODEL(bool isMouseDsiable, bool isKeyboardDisable) : INPUT_CURSOUR_DISABLE(isMouseDsiable), INPUT_KEYWORD_DISABLE(isKeyboardDisable) {}
	};

	struct ETexture 
	{
		enum TextureType
		{
			Texture2D = GL_TEXTURE_2D,
			Texture3D = GL_TEXTURE_3D,
			Texture2DArray = GL_TEXTURE_2D_ARRAY,
			TextureCubeMap = GL_TEXTURE_CUBE_MAP,
			TextureCUbeArray = GL_TEXTURE_CUBE_MAP_ARRAY,
		};
		TextureType type;
		GLuint ID;
		GLint width;
		GLint height;
		GLint nrComponents;
	};
}

#if 0

#define Assert(exp, desc)\
if(!___assert(exp, desc, __FILE__, __LINE__))\
{ __debugbreak(); }\

static bool ___assert(bool exp, const char* desc,const char* filename, int line)
{
	if (!exp) {
		//ELOG_ERROR(desc);
		//ELOG_ERROR(filename);
		//ELOG_ERROR("" + line);
	}
	return exp;
}

#endif

struct Color3   
{
	float r, g, b;

	Color3& operator=(ImVec4& right)
	{
		r = right.x;
		g = right.y;
		b = right.z;
		return *this;
	}
};

struct Color4
{
	float r, g, b, a;
	Color4() :r(0.0), g(0.0), b(0.0), a(0.0) {}
	Color4(float x, float y, float z, float w)
		:r(x), g(y), b(z), a(w) {}

	Color4& operator=(ImVec4& right)
	{
		r = right.x;
		g = right.y;
		b = right.z;
		a = right.w;
		return *this;
	}

	ImVec4 toImVec4()
	{
		ImVec4 imv;
		imv.x = r;
		imv.y = g;
		imv.z = b;
		imv.w = a;
		return imv;
	}
};
