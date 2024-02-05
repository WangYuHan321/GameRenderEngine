#pragma once
#include "AComponent.h"
#include "../../Util/Light.h"

class CLight :
    public AComponent
{
public:
    CLight(Actor& p_owner);

    const Light& GetData() const;

    void SetColor(const Vector3& p_color);

    void SetIntensity(float p_intensity);

    float GetIntensity() const;

    Vector3 GetColor() const;

    virtual std::string GetName();

    virtual void OnInspector(WidgetContainer& p_root) ;

    virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) ;

    virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) ;

protected:
    Light m_data;
};

