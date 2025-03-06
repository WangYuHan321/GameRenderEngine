#include "ModelJob.h"
#include "../ModelLoader.h"
#include "../../ModelManager.h"
#include "../../Global/ServiceLocator.h"


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

	ServiceLocator::getInstance()->Get<ModelManager>().SetNewResource(m_fileName, m_model);
}

void ModelJob::AsyncThreadProcess()
{
	m_model = ModelLoader::getInstance()->Create(m_fileName);
	m_uiLoadState = LS_LOADED;
	//ResourceJob::AsyncThreadProcess();
}