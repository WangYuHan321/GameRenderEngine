#pragma once
#include "FileJob.h"

class ResourceJob : public FileJob
{
public:
	enum
	{
		JS_WaitLoadFromDisk_AnyThread = JS_PENDING,
		JS_CreateLoadJobObject_MainThread = JS_MAIN_THREAD,
	};

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

	ResourceJob();
	virtual ~ResourceJob() = 0;
	virtual unsigned int GetResourceType() const = 0;
	virtual unsigned int GetJobType()const
	{
		return JT_RESOURCE;
	}

	virtual void MainThreadProcess();
	virtual void AsyncThreadProcess();
};