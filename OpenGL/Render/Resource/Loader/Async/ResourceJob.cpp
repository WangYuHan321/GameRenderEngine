#include "ResourceJob.h"

ResourceJob::ResourceJob(string resName):
	FileJob(resName)
{
}

ResourceJob::~ResourceJob()
{
}

void ResourceJob::MainThreadProcess()
{
	LOG("This function is no implement !!!!");
	LOG_INFO("Load " + m_fileName + " is success !!!!");
}

void ResourceJob::AsyncThreadProcess()
{
	FileJob::AsyncThreadProcess();
	if (m_uiLoadState == LS_PENDING)
	{
		m_uiJobState = LS_LOADED;
	}
}

