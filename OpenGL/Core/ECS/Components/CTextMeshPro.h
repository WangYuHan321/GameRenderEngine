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

    void SetContent(std::string);

    std::string GetTTFFile();

    int GetFontSize();

    virtual std::string GetName();

    virtual void OnInspector(WidgetContainer& p_root);

    virtual void OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node);

    virtual void OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node);


private:
    std::string m_inputText;
    std::string m_ttfConfig;
    int m_fontSize;

};
