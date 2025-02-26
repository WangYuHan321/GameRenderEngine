#pragma once
#include "../../Util/common.h"
class ResourceManager;

class ResName
{
	friend class ResourceManager;
public:
	explicit ResName(string name);
	~ResName();

	bool operator==(const ResName&) const;

private:
	string m_strName;
};

class AResource
{
public:
	enum class ResType
	{
		RT_TEXTURE,
		RT_MODEL,
		RT_UNKNOW,
		RT_SCRIPT,
		RT_ANIM,
	}RESTYPE;

	AResource(ResName& resName);
	~AResource();

	virtual ResType GetResourceType()const { return ResType::RT_UNKNOW; }

private:
	ResName m_resName;
};
