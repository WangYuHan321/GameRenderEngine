#include "XmlManager.h"
#include "ConfigManager.h"
#include <map>
#include <codecvt> 
#include <locale>

LANGUAGE XmlManager::language = LANGUAGE::EN_US; // default

XmlManager::XmlManager()
{
	LoadLanguageXml("language", "item");
}
XmlManager::~XmlManager()
{
}


std::string XmlManager::GetXmlNameByLanguage(std::string path)
{
	switch (language)
	{
	case LANGUAGE::EN_US:
		return path;
		break;
	case LANGUAGE::ZH_CN:
		return path + "_zh";
		break;
	case LANGUAGE::VI_VN:
		return path + "_vn";
		break;
	case LANGUAGE::ZH_TW:
		return path + "_tw";
		break;
	}
	return "";
}

void XmlManager::SwitchLanguage(LANGUAGE newLanguage)
{
	if (language != newLanguage)
	{
		language = newLanguage;
		m_languageMap.clear();
		LoadLanguageXml("language", "item");
	}
}

std::wstring wstring_from_utf8(std::string bype_string) {
	static std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;
	return utf8_conv.from_bytes(bype_string);
}

std::wstring stringtowstring(std::string str)
{
	std::string utf8_str(str);
	return wstring_from_utf8(utf8_str);
}

std::string string_tows_utf8(std::string str) {

	std::wstring temp = stringtowstring(str);
	static std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;
	return utf8_conv.to_bytes(temp);
}

void XmlManager::LoadLanguageXml(std::string xmlName, std::string nodeName)
{
	std::string fileName = GetXmlNameByLanguage(xmlName);

	tinyxml2::TinyXMLDocument doc;
	std::string xmlPath = ConfigManager::getInstance()->GetXmlPath() + "/" + fileName + ".xml";

	doc.LoadFile(xmlPath.c_str());

	if (!doc.Error())
	{
		tinyxml2::XMLNode* pRoot = doc.FirstChild();

		for (tinyxml2::XMLElement* current = pRoot->FirstChildElement(); current != nullptr; current = current->NextSiblingElement())
		{
			tinyxml2::XMLElement* curElement = current;
			std::string name = curElement->Name();
			if (name == nodeName)
			{
				int id = atoi(curElement->Attribute("id"));
				std::string content = curElement->Attribute("language");
				m_languageMap[id] = string_tows_utf8(content);
			}

		}

	}
	doc.Clear();
}

std::string XmlManager::GetLanguage(uint32 id)
{
	if (m_languageMap.count(id) > 0)
	{
		return m_languageMap[id];
	}
	return "";
}

LANGUAGE XmlManager::GetLanguageType() const
{
	return language;
}