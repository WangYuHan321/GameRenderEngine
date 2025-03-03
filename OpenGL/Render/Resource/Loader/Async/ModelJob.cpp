#include "ModelJob.h"
#include "../ModelLoader.h"


ModelJob::ModelJob(string texName):
	ResourceJob(texName)
{

}
ModelJob::~ModelJob()
{

}

void ModelJob::MainThreadProcess()
{
	ResourceJob::MainThreadProcess();
}

void ModelJob::AsyncThreadProcess()
{
	m_model = ModelLoader::getInstance()->Create(m_fileName);
	m_uiLoadState = LS_LOADED;
	//ResourceJob::AsyncThreadProcess();
}