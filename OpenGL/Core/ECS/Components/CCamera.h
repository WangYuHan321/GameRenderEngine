#pragma once

#include "AComponent.h"
#include "../../Camera/Camera.h"


class CCamera : public AComponent
{

public:

    CCamera(Actor& p_actor);
    ~CCamera();

    Camera& GetCamera();

    float GetFov();
    void SetFov(float fov);
    float GetSize();
    void SetSize(float pSize);
    float GetFar();
    void SetFar(float pFar);
    float GetNear();
    void SetNear(float pNear);
    Color4 GetClearColor();
    void SetClearColor(Color4 p_clearColor);

    virtual std::string GetName();

    virtual void OnInspector(WidgetContainer& p_root);

    virtual void OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node);

    virtual void OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node);


private:
    Camera m_camera;
};

