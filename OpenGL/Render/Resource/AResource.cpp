#include "AResource.h"

ResName::ResName(string name)
{
	void* pData = (void*)name.c_str();
	unsigned int mUI = strlen(name.c_str());
	CRC32Compute(pData, mUI);
}

ResName::~ResName()
{
}

bool ResName::operator==(const ResName& other) const
{
	return (this->m_strName == other.m_strName);
}

AResource::AResource(ResName& resName):
	m_resName(resName)
{
}

AResource::~AResource()
{
}
