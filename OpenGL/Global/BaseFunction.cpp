#include "BaseFunction.h"
#include "../File/XmlManager.h"
#include "ServiceLocator.h"


std::string GetLanguage(int32_t id)
{
	return GLOBALSERVICE(XmlManager).GetLanguage(id);
}