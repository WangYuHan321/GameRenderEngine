#pragma once

#include "AComponent.h"
#include "../../Camera/Camera.h"


class CCamera : public AComponent
{

public:

    CCamera(Actor& p_actor);
    ~CCamera();

    virtual std::string GetName();

    virtual void OnInspector(WidgetContainer& p_root);

    virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node);

    virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node);


private:
    Camera m_camera;
};

