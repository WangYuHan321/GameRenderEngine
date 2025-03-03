#pragma once
#include "ResourceJob.h"

class Model;

class ModelJob : public ResourceJob
{
public:

	ModelJob(string texName);
	virtual ~ModelJob();
	virtual unsigned int GetResourceType() const
	{
		return RT_STATIC_MODEL;
	}

	virtual void MainThreadProcess();
	virtual void AsyncThreadProcess();

private:
	Model* m_model;
};

