#include "Texture.h"

Texture::Texture()
{

}
//Texture::~Texture() {}

void Texture::Generate(uint32 width, GLenum internalFormat, GLenum format, GLenum type, void* data)
{
	glGenTextures(1, &ID);

	Width = width;
	InternalFormat = internalFormat;
	Format = format;
	Type = type;

	Assert((Target == GL_TEXTURE_1D), "Texture Generate is not GL_TEXTURE_2D");
	Bind();
	{
		glTexImage1D(Target, MipLevel, InternalFormat, Width, 0, Format, Type, data);
		glTexParameteri(Target, GL_TEXTURE_MIN_FILTER, FilterMin);
		glTexParameteri(Target, GL_TEXTURE_MAG_FILTER, FilterMax);
		glTexParameteri(Target, GL_TEXTURE_WRAP_S, WrapS);
		glTexParameteri(Target, GL_TEXTURE_WRAP_T, WrapT);

		if (MipMapping)
			glGenerateMipmap(Target);
	}
	UnBind();
}

void Texture::Generate(uint32 width, uint32 height, GLenum internalFormat, GLenum format, GLenum type, void* data)
{
	glGenTextures(1, &ID);

	Width = width;
	Height = height;
	InternalFormat = internalFormat;
	Format = format;
	Type = type;
	
	Assert((Target == GL_TEXTURE_2D), "Texture Generate is not GL_TEXTURE_2D");
	Bind();
	{
		glTexImage2D(Target, MipLevel, InternalFormat, Width, Height, 0, Format, Type, data);
		glTexParameteri(Target, GL_TEXTURE_MIN_FILTER, FilterMin);
		glTexParameteri(Target, GL_TEXTURE_MAG_FILTER, FilterMax);
		glTexParameteri(Target, GL_TEXTURE_WRAP_S, WrapS);
		glTexParameteri(Target, GL_TEXTURE_WRAP_T, WrapT);
		
		if (MipMapping)
			glGenerateMipmap(Target);
	}
	UnBind();
}

void Texture::Generate(uint32 width, uint32 height,uint32 depth, GLenum internalFormat, GLenum format, GLenum type, void* data)
{
	glGenTextures(1, &ID);

	Width = width;
	Height = height;
	Depth = depth;
	InternalFormat = internalFormat;
	Format = format;
	Type = type;

	Assert((Target == GL_TEXTURE_2D), "Texture Generate is not GL_TEXTURE_2D");
	Bind();
	{
		glTexImage3D(Target, MipLevel, InternalFormat, Width, Height, Depth, 0, Format, Type, data);
		glTexParameteri(Target, GL_TEXTURE_MIN_FILTER, FilterMin);
		glTexParameteri(Target, GL_TEXTURE_MAG_FILTER, FilterMax);
		glTexParameteri(Target, GL_TEXTURE_WRAP_S, WrapS);
		glTexParameteri(Target, GL_TEXTURE_WRAP_T, WrapT);
		glTexParameteri(Target, GL_TEXTURE_WRAP_R, WrapR);
		if (MipMapping)
			glGenerateMipmap(Target);
	}
	UnBind();
}

void Texture::ReSize(uint32 width, uint32 height, uint32 depth)
{
	Bind();

	if (Target == GL_TEXTURE_1D)
		glTexImage1D(Target, MipLevel, InternalFormat, width, 0, Format, Type, 0);
	else if (Target == GL_TEXTURE_2D)
		glTexImage2D(Target, MipLevel, InternalFormat, width, height, 0, Format, Type, 0);
	else if (Target == GL_TEXTURE_3D)
		glTexImage3D(Target, MipLevel, InternalFormat, width, height, depth, 0, Format, Type, 0);

	UnBind();
}

void Texture::Bind()
{
	glBindTexture(Target, ID);
}

void Texture::Bind(uint32 uit)
{
	glActiveTexture(GL_TEXTURE0 + uit);
	glBindTexture(Target, ID);
}

void Texture::UnBind()
{
	glBindTexture(Target, 0);
}

void Texture::SetFilterMin(GLenum gEnum)
{
	glTexParameteri(Target, GL_TEXTURE_MIN_FILTER, gEnum);
}

void Texture::SetFilterMax(GLenum gEnum)
{
	glTexParameteri(Target, GL_TEXTURE_MAG_FILTER, gEnum);
}

void Texture::SetWrapMode(GLenum gEnum)
{
	glTexParameteri(Target, GL_WRAP_BORDER, gEnum);
}