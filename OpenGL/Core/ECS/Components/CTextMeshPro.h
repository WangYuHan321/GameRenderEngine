#pragma once
#include "AComponent.h"
#include "../../Util/Light.h"

class CTextMeshPro :
    public AComponent
{
public:

    CTextMeshPro(Actor& p_actor);
    ~CTextMeshPro();

    std::string GetContent();

    virtual std::string GetName();

    virtual void OnInspector(WidgetContainer& p_root);

    virtual void OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node);

    virtual void OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node);


private:
    std::string m_inputText;
};
