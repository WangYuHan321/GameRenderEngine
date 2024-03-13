#include "XmlManager.h"
#include "ConfigManager.h"
#include <map>

XmlManager::XmlManager()
{
	LoadLanguageXml("language.xml", "item");
}
XmlManager::~XmlManager()
{
}

void XmlManager::LoadLanguageXml(std::string xmlName, std::string nodeName)
{
	tinyxml2::TinyXMLDocument doc;
	std::string xmlPath = ConfigManager::getInstance()->GetXmlPath() + "/" + xmlName;

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

				m_languageMap[id] = content;
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