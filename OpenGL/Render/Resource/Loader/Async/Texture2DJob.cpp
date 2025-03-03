#include "Texture2DJob.h"
#include "../TextureLoader.h"

Texture2DJob::Texture2DJob(string texName):
	ResourceJob(texName)
{
}
Texture2DJob::~Texture2DJob()
{

}

void Texture2DJob::MainThreadProcess()
{
	ResourceJob::MainThreadProcess();
}

void Texture2DJob::AsyncThreadProcess()
{
	m_resTex = TextureLoader::getInstance()->LoadTexture(m_fileName,GL_TEXTURE_2D, GL_RGBA);
}