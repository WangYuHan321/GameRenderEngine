#pragma once

#include "../../Util/Singleton.h"
#include "../../Shader/Texture.h"
#include "../../Shader/TextureCube.h"
#include <iostream>

class TextureLoader : public CSingleton<TextureLoader>
{
public:
	//default enable mipmap
	Texture* Create(std::string& path, GLenum target, GLenum internalFormat);

	Texture* LoadTexture(std::string path, GLenum Target, GLenum internalFormat, bool srgb = false);
	Texture* LoadHDRTexture(std::string path);

	Texture* CreateColor(uint32_t p_data, GLenum p_firstFilter, GLenum p_secondFilter, bool p_generateMipmap);
	//font
	Texture* Create(uint32 width, uint32 height, GLenum internalFormat, GLenum format, GLenum type, void* data);

	Texture LoadTexture1(std::string path, GLenum Target, GLenum internalFormat, bool srgb = false);//¼æÈÝÎÞ±à¼­Æ÷Ä£Ê½
	Texture LoadHDRTexture1(std::string path);

	bool Destroy(Texture* pTexture);
};

