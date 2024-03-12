#pragma once
#include "texture.h"

#include <vector>

class TextureCube
{
public:
    unsigned int ID;

    GLenum InternalFormat = GL_RGBA;            
    GLenum Format         = GL_RGBA;            
    GLenum Type           = GL_UNSIGNED_BYTE;
    GLenum FilterMin      = GL_LINEAR;         
    GLenum FilterMax      = GL_LINEAR;         
    GLenum WrapS          = GL_CLAMP_TO_EDGE;   
    GLenum WrapT          = GL_CLAMP_TO_EDGE;   
    GLenum WrapR          = GL_CLAMP_TO_EDGE;   
    bool   Mipmapping = false;

    unsigned int FaceWidth  = 0;
    unsigned int FaceHeight = 0;

    std::string Path = "";
private:
public:
    TextureCube();
    ~TextureCube();

    void DefaultInitialize(unsigned int width, unsigned int height, GLenum format, GLenum type, bool mipmap = false);

    void GenerateFace(GLenum face, unsigned int width, unsigned int height, GLenum format, GLenum type, unsigned char* data);

    void SetMipFace(GLenum face, unsigned int width, unsigned int height, GLenum format, GLenum type, unsigned int mipLevel, unsigned char* data);


    void Resize(unsigned int width, unsigned int height);

    void Bind(int unit = -1);
    void Unbind();
};