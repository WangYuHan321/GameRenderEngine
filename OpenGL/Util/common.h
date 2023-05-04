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
#include"../Log/ILog.h"

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

#define Assert(exp, desc)\
if(!___assert(exp, desc, __FILE__, __LINE__))\
{ __debugbreak(); }\

static bool ___assert(bool exp, const char* desc,const char* filename, int line)
{
	if (!exp) {
		GTipWindowLog.OutputError(desc);
		GTipWindowLog.OutputError(filename);
		GTipWindowLog.OutputError("" + line);
	}
	return exp;
}

//static EasyGraphics::EWINDOWINFO GWindowInfo(1024,1024,"EasyEngine");
//static EasyGraphics::EINPUTMODEL GInputModel(true, true);