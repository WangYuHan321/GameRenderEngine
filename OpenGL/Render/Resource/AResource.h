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
	AResource(ResName& resName);
	~AResource();

private:
	ResName m_resName;
};