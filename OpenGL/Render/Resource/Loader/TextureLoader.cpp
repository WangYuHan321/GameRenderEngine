#include "TextureLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture* TextureLoader::Create(std::string& path, GLenum target, GLenum internalFormat)
{
    return LoadTexture(path, target, internalFormat);
}

Texture* TextureLoader::LoadTexture(std::string path, GLenum Target, GLenum internalFormat, bool srgb)
{
	Texture* pTexture = new Texture();

    pTexture->Target = Target;
    pTexture->InternalFormat = internalFormat;
	if (pTexture->InternalFormat == GL_RGB || pTexture->InternalFormat == GL_SRGB)
        pTexture->InternalFormat = srgb ? GL_SRGB : GL_RGB;
	if (pTexture->InternalFormat == GL_RGBA || pTexture->InternalFormat == GL_SRGB_ALPHA)
        pTexture->InternalFormat = srgb ? GL_SRGB_ALPHA : GL_RGBA;

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
            pTexture->Generate(width, pTexture->InternalFormat, format, GL_UNSIGNED_BYTE, data);
        else if (Target == GL_TEXTURE_2D)
            pTexture->Generate(width, height, pTexture->InternalFormat, format, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }
    else
    {
        Log("Texture failed to load at path: " + path);
        stbi_image_free(data);
        return pTexture;
    }
    pTexture->Width = width;
    pTexture->Height = height;

    return pTexture;
}

Texture* TextureLoader::CreateColor(uint32_t p_data, GLenum p_firstFilter, GLenum p_secondFilter, bool p_generateMipmap)
{
    Texture* pTexture = new Texture();
    glGenTextures(1, &pTexture->ID);
    glBindTexture(GL_TEXTURE_2D, pTexture->ID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &p_data);

    if (p_generateMipmap)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(p_firstFilter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(p_secondFilter));

    glBindTexture(GL_TEXTURE_2D, 0);

    return pTexture;
}

Texture TextureLoader::LoadTexture1(std::string path, GLenum Target, GLenum internalFormat, bool srgb)
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

Texture TextureLoader::LoadHDRTexture1(std::string path)
{
    Texture texture;
    texture.Target = GL_TEXTURE_2D;
    texture.FilterMin = GL_LINEAR;
    texture.MipMapping = false;

    stbi_set_flip_vertically_on_load(true);

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
    }

    return texture;
}

Texture* TextureLoader::LoadHDRTexture(std::string path)
{
    Texture* pTexture = new Texture();
    pTexture->Target = GL_TEXTURE_2D;
    pTexture->FilterMin = GL_LINEAR;
    pTexture->MipMapping = false;

    stbi_set_flip_vertically_on_load(true);

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
            pTexture->Generate(width, height, internalFormat, format, GL_FLOAT, data);
            stbi_image_free(data);
        }
        pTexture->Width = width;
        pTexture->Height = height;
    }
    else
    {
        Log("HDR Texture file is error !!!\n");
    }

    return pTexture;
}

bool TextureLoader::Destroy(Texture* pTexture)
{
    if (pTexture)
    {
        delete pTexture;
        pTexture = nullptr;

        return true;
    }

    return false;
}