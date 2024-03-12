#pragma once

#include"CLight.h"

class CAmbientSphereLight : public CLight
{
public:
	CAmbientSphereLight(Actor& p_actor);

	std::string GetName() override;

	void SetRadius(float p_radius) ;

	float GetRadius() const;

	virtual void OnInspector(WidgetContainer& p_root);

	virtual void OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node);

	virtual void OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node);
};

