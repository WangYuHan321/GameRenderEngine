#pragma once

#include"../Util/Singleton.h"
#include "../Util/common.h"
#include "../Core/API/tinyxml2.h"
#include "LanguageDefine.h"

enum class LANGUAGE
{
	ZH_CN,
	EN_US,
	ZH_TW,
	VI_VN,
};

class XmlManager 
{
public:
	XmlManager();
	~XmlManager();

	std::string GetXmlNameByLanguage(std::string path);
	void SwitchLanguage(LANGUAGE newLanguage);
	void LoadLanguageXml(std::string xmlName, std::string nodeName);
	std::string GetLanguage(uint32 id);
	LANGUAGE GetLanguageType() const ;

private:
	std::map<int, std::string> m_languageMap;
	static LANGUAGE language;
};

