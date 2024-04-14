#pragma once

#include "CLight.h"

class CDirectionalLight : public CLight
{
public:

	CDirectionalLight(Actor& p_owner);

	Vector3 GetDirectional();

	Vector3 GetPosition();

	virtual std::string GetName() override;

	virtual void OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

	virtual void OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

	virtual void OnInspector(WidgetContainer& p_root) override;
};

