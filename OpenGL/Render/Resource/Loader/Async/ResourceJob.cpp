#include "ResourceJob.h"

ResourceJob::ResourceJob()
{
}

ResourceJob::~ResourceJob()
{
}

void ResourceJob::MainThreadProcess()
{
	LOG("This function is no implement !!!!");
}

void ResourceJob::AsyncThreadProcess()
{
	FileJob::AsyncThreadProcess();
	if (m_uiLoadState == LS_PENDING)
	{
		m_uiJobState = LS_LOADED;
	}
}

