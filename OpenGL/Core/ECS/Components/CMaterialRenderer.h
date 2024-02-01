#pragma once

#include <array>
#include "AComponent.h"
#include "../../Render/Mesh/Material.h"

#define MAX_MATERIAL_COUNT 255

class CMaterialRenderer : public AComponent
{
public:
	
	using MaterialList = std::array<Material*, MAX_MATERIAL_COUNT>;
	using MaterialField = std::array<std::array<AWidget*, 3>, MAX_MATERIAL_COUNT>;

	CMaterialRenderer(Actor& p_owner);

	void UpdateMaterialList();

	virtual std::string GetName() override;
	
	virtual void OnInspector(WidgetContainer& p_root) override;

	virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

	virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

private:
	MaterialList m_materials;
	MaterialField m_materialFileds;
	std::array<std::string, MAX_MATERIAL_COUNT> m_materialNames;

};

