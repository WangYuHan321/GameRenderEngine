#pragma once
#include "FileJob.h"
#include "../../AResourceManager.h"
#include "../../ResourceManager.h"
#include "../../Thread/AsynJobThread.h"

class AsynLoaderManager
{
	friend ResourceManager;

public:
	AsynLoaderManager();
	~AsynLoaderManager();

	void Update(float appTime);
	void AddTexture2D();


	void DeleteResource(AsyncJob* asynJob);
	void AddJob(AsyncJob* asynJob);
	std::vector<AsyncJob*> m_jobArray;
	AsynJobThread m_asynJobThread;

};

