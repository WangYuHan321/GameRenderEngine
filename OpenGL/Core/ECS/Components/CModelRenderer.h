#pragma once

#include "AComponent.h"
#include "../../Render/Mesh/Model.h"


class CModelRenderer : public AComponent
{
public:
	CModelRenderer(Actor& p_owner);

	void SetModel(Model* p_model);

	Model* GetModel() const;

	virtual std::string GetName() override;

	virtual void OnInspector(WidgetContainer& p_root) override;

	virtual void OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

	virtual void OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

private:
	Model* m_model = nullptr;
	Event<> m_modelChangedEvent;

	bool isShadowRecive;

};

