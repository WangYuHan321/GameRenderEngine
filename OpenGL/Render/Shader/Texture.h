#pragma once
#include"../../Util/common.h"

class Texture
{
public:
	uint32 ID;

	GLenum Target = GL_TEXTURE_2D;
	GLenum InternalFormat = GL_RGBA;
	GLenum Format = GL_RGBA;
	GLenum Type = GL_UNSIGNED_BYTE;
	GLenum FilterMin = GL_LINEAR_MIPMAP_LINEAR;
	GLenum FilterMax = GL_LINEAR;
	GLenum WrapS = GL_REPEAT;
	GLenum WrapT = GL_REPEAT;
	GLenum WrapR = GL_REPEAT;
	bool MipMapping = true;

	uint32 Width = 0;
	uint32 Height = 0;
	uint32 Depth = 0;
	uint32 MipLevel = 0;

	std::string Path = "";

public:
	Texture();
	//virtual ~Texture() {}; 在共用体中无法带有析构函数

	//Generate 1D Texture
	void Generate(uint32 width, GLenum internalFormat, GLenum format, GLenum type, void* data);
	//Generate 2D Texture
	void Generate(uint32 width, uint32 height, GLenum internalFormat, GLenum format, GLenum type, void* data);
	//Generate 3D Texture
	void Generate(uint32 width, uint32 height, uint32 depth, GLenum internalFormat, GLenum format, GLenum type, void* data);

	void ReSize(uint32 width, uint32 height, uint32 depth = 0);

	void Bind();
	void Bind(uint32 uit);
	void UnBind();

	void SetFilterMin(GLenum gEnum);
	void SetFilterMax(GLenum gEnum);
	void SetWrapMode(GLenum gEnum);

	void ReSizeSubImage(int x, int y, int width, int height, unsigned int client_format, unsigned int data_type, unsigned char* data);
};

