#pragma once

#include "CLight.h"

class CDirectionalLight : public CLight
{
public:

	CDirectionalLight(Actor& p_owner);

	virtual std::string GetName() override;

	virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

	virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

	virtual void OnInspector(WidgetContainer& p_root) override;
};

