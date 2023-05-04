#include "TextureLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture TextureLoader::LoadTexture(std::string path, GLenum Target, GLenum internalFormat, bool srgb)
{
	Texture texture;

	texture.Target = Target;
	texture.InternalFormat = internalFormat;
	if (texture.InternalFormat == GL_RGB || texture.InternalFormat == GL_SRGB)
		texture.InternalFormat = srgb ? GL_SRGB : GL_RGB;
	if (texture.InternalFormat == GL_RGBA || texture.InternalFormat == GL_SRGB_ALPHA)
		texture.InternalFormat = srgb ? GL_SRGB_ALPHA : GL_RGBA;

	stbi_set_flip_vertically_on_load(true);
    
    int width, height, nrComponents;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        if (Target == GL_TEXTURE_1D)
            texture.Generate(width, texture.InternalFormat, format, GL_UNSIGNED_BYTE, data);
        else if (Target == GL_TEXTURE_2D)
            texture.Generate(width, height, texture.InternalFormat, format, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }
    else
    {
        Log("Texture failed to load at path: " + path);
        stbi_image_free(data);
        return texture;
    }
    texture.Width = width;
    texture.Height = height;

    return texture;
}

Texture TextureLoader::LoadHDRTexture(std::string path)
{
    Texture texture;
    texture.Target = GL_TEXTURE_2D;
    texture.FilterMin = GL_LINEAR;
    texture.MipMapping = false;

    stbi_set_unpremultiply_on_load(true);

    if (stbi_is_hdr(path.c_str()))
    {
        int width, height, nrComponent;
        float* data = stbi_loadf(path.c_str(), &width, &height, &nrComponent, 0);
        if (data)
        {
            GLenum internalFormat, format;
            if (nrComponent == 3)
            {
                internalFormat = GL_RGB32F;
                format = GL_RGB;
            }
            else if (nrComponent == 4)
            {
                internalFormat = GL_RGBA32F;
                format = GL_RGBA;
            }
            texture.Generate(width, height, internalFormat, format, GL_FLOAT, data);
            stbi_image_free(data);
        }
        texture.Width = width;
        texture.Height = height;
    }
    else
    {
        Log("HDR Texture file is error !!!\n");
        return Texture();
    }

    return texture;
}