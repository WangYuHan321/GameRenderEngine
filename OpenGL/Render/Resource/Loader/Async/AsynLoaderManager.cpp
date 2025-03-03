#include "AsynLoaderManager.h"
#include "Texture2DJob.h"
#include "Texture3DJob.h"
#include "ModelJob.h"

AsynLoaderManager::AsynLoaderManager()
{
}

AsynLoaderManager::~AsynLoaderManager()
{
}

void AsynLoaderManager::Update(float appTime)
{
	while (m_jobArray.size() > 0)
	{
		for (int i = 0; i < m_jobArray.size(); i++)
		{
			AsyncJob* pJob = m_jobArray[i];
			
			if (pJob->m_uiLoadState == AsyncJob::LS_PENDING)
			{
				i++;
				continue;
			}

			else if (pJob->m_uiLoadState == AsyncJob::LS_LOADED)
			{
				if (pJob->GetJobType() == AsyncJob::JS_DELETE)
				{
				}
				else
				{
					pJob->MainThreadProcess();
				}
				m_jobArray.erase(m_jobArray.begin() + i);
			}
		}
	}
}

void AsynLoaderManager::AddTexture2D(std::string texPath)
{
	Texture2DJob* pJob = EngineNew Texture2DJob(texPath);
	AddJob(pJob);
}

void AsynLoaderManager::AddModel(std::string modelPath)
{
	ModelJob *pJob = EngineNew ModelJob(modelPath);
	AddJob(pJob);
}

void AsynLoaderManager::DeleteResource(AsyncJob* asynJob)
{
}

void AsynLoaderManager::AddJob(AsyncJob* asynJob)
{
	m_jobArray.push_back(asynJob);
	if (m_jobArray.size() == 1)
		m_asynJobThread.Start();
	m_asynJobThread.SafeAddJob(asynJob);
}