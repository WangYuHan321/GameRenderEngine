#include "ResourceJob.h"

ResourceJob::ResourceJob()
{
}

ResourceJob::~ResourceJob()
{
}

void ResourceJob::MainThreadProcess()
{
	if (m_uiJobState == JS_MAIN_THREAD)
	{
		LOG("This function is no implement !!!!");
	}
}

void ResourceJob::AsyncThreadProcess()
{
	if (m_uiJobState == JS_PENDING)
	{
		FileJob::AsyncThreadProcess();
		if (m_uiJobState != JS_FAIL)
		{
			m_uiJobState = JS_MAIN_THREAD;
		}
	}

}

