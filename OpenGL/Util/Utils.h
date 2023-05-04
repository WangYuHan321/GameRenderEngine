#pragma once
#include <initializer_list>
//#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
//#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#include <iostream>
#include <numeric>
//#include <boost/algorithm/string/split.hpp>
//#include <boost/algorithm/string/classification.hpp>

#include "common.h"
#include "../Math/Math.h"
#include "../Render/Shader/Texture.h"
#include "../Render/Shader/TextureCube.h"

enum class CursorShape
{
	ARROW = 0x00036001,
	IBEAM = 0x00036002,
	CROSSHAIR = 0x00036003,
	HAND = 0x00036004,
	HRESIZE = 0x00036005,
	VRESIZE = 0x00036006
};

static void G_LoadTextureFromFile(std::string& texturePath, EasyGraphics::ETexture& texture)
{
	unsigned char* data = stbi_load(texturePath.c_str(), &texture.width, &texture.height, &texture.nrComponents, 0);

	if (data != nullptr) {
		glGenTextures(1, &texture.ID);
		switch (texture.type)
		{
		case EasyGraphics::ETexture::Texture2D:
			glBindTexture(texture.type, texture.ID);
			glTexImage2D(texture.type, 0, GL_RGB, texture.width, texture.height, 0, GL_RGB, texture.type, 0);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
			break;
		case EasyGraphics::ETexture::Texture3D:
			break;
		case EasyGraphics::ETexture::Texture2DArray:
			break;
		case EasyGraphics::ETexture::TextureCubeMap:
			break;
		case EasyGraphics::ETexture::TextureCUbeArray:
			break;
		default:
			break;
		}
	}
}

static string G_GetTextFromFile(string strFilePath)
{
	if (strFilePath.length() != 0)
	{
		std::ifstream streamV(strFilePath);
		Assert(streamV.fail(), "Error ifstream");
		std::stringstream strStreamV;
		strStreamV << streamV.rdbuf();
		string fileContent = strStreamV.str();
		streamV.close();
		strStreamV.clear();

		return fileContent;
	}
	return "";
}
