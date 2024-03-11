#include "CMaterialRenderer.h"
#include "../Actor.h"

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

void CMaterialRenderer::OnInspector(WidgetContainer& p_root)
{

}

void CMaterialRenderer::OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{

}

void CMaterialRenderer::OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{

}
