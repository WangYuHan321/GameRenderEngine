#include "CTextMeshPro.h"

#include <filesystem>
#include "../../File/ConfigManager.h"
#include "../../File/Path/PathParser.h"
#include "../../Global/ServiceLocator.h"
#include "../../Render/Font/FontManager.h"
#include "../../UI/Widgets/Selection/ComboBox.h"

std::vector<std::string> GetAllFont()
{
	std::vector<std::string> vecFiles;
	std::filesystem::path path(ConfigManager::getInstance()->GetFontPath());

	for (const auto& iter : std::filesystem::directory_iterator(path))
	{
		if (std::filesystem::is_directory(iter.path()))
			continue;

		string sFile = iter.path().filename().string();
		vecFiles.push_back(sFile);
	}
	return vecFiles;
}

void DrawCombox(WidgetContainer& p_root, Actor& pActor, const std::string& p_name, std::string& ttfFileName)
{
	GUIDrawer::CreateTitle(p_root, p_name);

	std::vector<std::string> vecFiles = GetAllFont();
	auto& item = p_root.CreateWidget<ComboBox>(vecFiles.size());

	for (int i = 0; i < vecFiles.size(); i++)
		item.choices[i] = PathParser::getInstance()->GetFileNameByPath(vecFiles[i]);

	item.currentChoice = 0;

	item.ValueChangedEvent += [&ttfFileName, &pActor](int id)
	{
		ttfFileName = GetAllFont()[id];
		GLOBALSERVICE(FontManager).ModifyFontStr(pActor);
	};
}

CTextMeshPro::CTextMeshPro(Actor& p_actor):
	AComponent(p_actor),
	m_inputText("CTextMeshPro"),
	m_ttfConfig(""),
	m_fontSize(100)
{
	std::vector<std::string> vecFiles = GetAllFont();

	if(vecFiles.size() > 0)
		m_ttfConfig = PathParser::getInstance()->GetFileNameByPath(vecFiles[0]);
}

CTextMeshPro::~CTextMeshPro()
{

}

std::string CTextMeshPro::GetContent()
{
	return m_inputText;
}

void CTextMeshPro::SetContent(std::string strFont)
{
	m_inputText = strFont;
	GLOBALSERVICE(FontManager).ModifyFontStr(owner);
}

std::string CTextMeshPro::GetTTFFile()
{
	return m_ttfConfig;
}

int CTextMeshPro::GetFontSize()
{
	return m_fontSize;
}

std::string CTextMeshPro::GetName()
{
	return "CTextMeshPro";
}

void CTextMeshPro::OnInspector(WidgetContainer& p_root)
{
	DrawCombox(p_root, owner, "TTFileName", m_ttfConfig);
	GUIDrawer::DrawString(p_root, "Mesh Font", std::bind(&CTextMeshPro::GetContent, this), std::bind(&CTextMeshPro::SetContent, this, std::placeholders::_1));
}

void CTextMeshPro::OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{

}

void CTextMeshPro::OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{

}