#include "Texture2DJob.h"
#include "../../ResourceManager.h"

Texture2DJob::Texture2DJob()
{

}
Texture2DJob::~Texture2DJob()
{

}

void Texture2DJob::MainThreadProcess()
{
	LOG_INFO("Main Thread Set Texture !!!!");
}

void Texture2DJob::AsyncThreadProcess()
{
	ResourceJob::AsyncThreadProcess();
}