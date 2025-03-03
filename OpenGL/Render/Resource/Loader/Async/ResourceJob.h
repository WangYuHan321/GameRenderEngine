#pragma once
#include "FileJob.h"

class ResourceJob : public FileJob
{
public:
	enum	//Resource Type
	{
		RT_TEXTURE,
		RT_SKELECTON_MODEL,
		RT_STATIC_MODEL,
		RT_ACTION,
		RT_MATERIAL,
		RT_POSTEFFECT,
		RT_ANIMTREE,
		RT_ACTOR,
		RT_MAP,
		RT_FONTTYPE,
		RT_MAX
	};

	ResourceJob(string resourceName);
	virtual ~ResourceJob() = 0;
	virtual unsigned int GetResourceType() const = 0;
	virtual unsigned int GetJobType()const
	{
		return JT_RESOURCE;
	}

	virtual void MainThreadProcess();
	virtual void AsyncThreadProcess();
};