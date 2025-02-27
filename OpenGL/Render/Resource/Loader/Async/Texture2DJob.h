#pragma once
#include "ResourceJob.h"

class Texture2DJob : public ResourceJob
{
public:

	Texture2DJob();
	virtual ~Texture2DJob();
	virtual unsigned int GetResourceType() const
	{
		return RT_TEXTURE;
	}

	virtual void MainThreadProcess();
	virtual void AsyncThreadProcess();
};
