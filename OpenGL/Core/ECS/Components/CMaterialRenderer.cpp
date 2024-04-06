#include "CMaterialRenderer.h"
#include "../Actor.h"
#include "../../UI/Widgets/Text/TextColored.h"
#include "../../UI/Widgets/Button/Button.h"
#include "../../UI/Layout/Group.h"
#include "../../UI/Plugin/DDTarget.h"
#include "../../File/Path/PathParser.h"
#include "../../Global/ServiceLocator.h"
#include "../../Render/Resource/MaterialManager.h"

CMaterialRenderer::CMaterialRenderer(Actor& p_owner):
	AComponent(p_owner)
{
	m_materials.fill(nullptr);
	
	for (uint32 i = 0; i < MAX_MATERIAL_COUNT; i++)
		m_materialFields[i].fill(nullptr);
	
	UpdateMaterialList();
}

void CMaterialRenderer::UpdateMaterialList()
{


}

void CMaterialRenderer::FillWithMaterial(Material& p_material)
{
	for (uint8_t i = 0; i < m_materials.size(); ++i)
		m_materials[i] = &p_material;
}

std::string CMaterialRenderer::GetName()
{
	return "CMaterialRenderer";
}

const Matrix4& CMaterialRenderer::GetUserMatrix() const
{
	return m_userMatrix;
}

std::array<AWidget*, 3> CMaterialRenderer::CustomMaterialDrawer(WidgetContainer& p_root, const std::string& p_name, Material*& p_data)
{

	std::array<AWidget*, 3> widgets;

	widgets[0] = &p_root.CreateWidget<TextColored>(p_name, GUIDrawer::titleColor);

	std::string displayedText = (p_data ? p_data->Path : std::string("Empty"));
	auto& rightSide = p_root.CreateWidget<Group>();

	auto& widget = rightSide.CreateWidget<Text>(displayedText);

	widgets[1] = &widget;

	widget.AddPlugin<DDTarget<std::pair<std::string, Group*>>>("File").DataReceivedEvent += [&widget, &p_data](auto p_receivedData)
	{
		if (PathParser::getInstance()->GetFileType(p_receivedData.first) == EFileType::MATERIAL)
		{
			if (auto resource = GLOBALSERVICE(MaterialManager).GetResource(p_receivedData.first); resource)
			{
				p_data = resource;
				widget.content = p_receivedData.first;
			}
		}
	};

	widget.lineBreak = false;

	auto& resetButton = rightSide.CreateWidget<Button>("Clear", ImVec2(40, 40));
	resetButton.idleColor = GUIDrawer::clearBtnColor;
	resetButton.ClickedEvent += [&widget, &p_data]
	{
		p_data = nullptr;
		widget.content = "Empty";
	};

	widgets[2] = &resetButton;

	return widgets;
}

void CMaterialRenderer::OnInspector(WidgetContainer& p_root)
{
	for (uint8_t i = 0; i < m_materials.size(); ++i)
		m_materialFields[i] = CustomMaterialDrawer(p_root, "Material", m_materials[i]);

	UpdateMaterialList();
}

void CMaterialRenderer::OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{

}

void CMaterialRenderer::OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{

}
