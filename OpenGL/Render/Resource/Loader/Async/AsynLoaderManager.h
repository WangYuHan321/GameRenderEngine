#pragma once
#include "FileJob.h"
#include "../../AResourceManager.h"
#include "../../ResourceManager.h"

class AsynLoaderManager
{
	friend ResourceManager;

public:
	enum TaskType
	{
		Task_Thread_Num = 2
	};

	AsynLoaderManager();
	~AsynLoaderManager();

	void Update(float appTime);
	void AddResource();

	void DeleteResource();
	void AddJob();
	std::vector<AsyncJob*> m_jobArray;


};

