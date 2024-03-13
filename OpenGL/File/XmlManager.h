#pragma once

#include"../Util/Singleton.h"
#include "../Util/common.h"
#include "../Core/API/tinyxml2.h"
#include "LanguageDefine.h"

class XmlManager 
{
public:
	XmlManager();
	~XmlManager();

	void LoadLanguageXml(std::string xmlName, std::string nodeName);
	std::string GetLanguage(uint32 id);


private:
	std::map<int, std::string> m_languageMap;

};

