#pragma once

#include "../../Util/Singleton.h"
#include "Texture.h"
#include "TextureCube.h"
#include <iostream>

class TextureLoader : public CSingleton<TextureLoader>
{
public:
	Texture LoadTexture(std::string path, GLenum Target, GLenum internalFormat, bool srgb = false);
	Texture LoadHDRTexture(std::string path);
};

