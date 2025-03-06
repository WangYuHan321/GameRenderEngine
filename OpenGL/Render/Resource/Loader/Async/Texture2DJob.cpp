#include "Texture2DJob.h"
#include "../TextureLoader.h"
#include "../../TextureManager.h"
#include "../../Global/ServiceLocator.h"

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
	ServiceLocator::getInstance()->Get<TextureManager>();
}

void Texture2DJob::AsyncThreadProcess()
{
	m_resTex = TextureLoader::getInstance()->LoadTexture(m_fileName,GL_TEXTURE_2D, GL_RGBA);
}