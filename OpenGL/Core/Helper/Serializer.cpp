#include "Serializer.h"


void Serializer::SerializeBoolean(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, bool p_value)
{
	tinyxml2::XMLElement* pElement = p_doc.NewElement(p_name.c_str());
	pElement->SetText(p_value);
	p_node->InsertEndChild(pElement);
}

void Serializer::SerializeString(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, std::string p_value)
{
	tinyxml2::XMLElement* pElement = p_doc.NewElement(p_name.c_str());
	pElement->SetText(p_value.c_str());
	p_node->InsertEndChild(pElement);
}

void Serializer::SerializeFloat(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, float p_value)
{
	tinyxml2::XMLElement* pElement = p_doc.NewElement(p_name.c_str());
	pElement->SetText(p_value);
	p_node->InsertEndChild(pElement);
}

void Serializer::SerializeDouble(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, double p_value)
{
	tinyxml2::XMLElement* pElement = p_doc.NewElement(p_name.c_str());
	pElement->SetText(p_value);
	p_node->InsertEndChild(pElement);
}

void Serializer::SerializeUInt(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, uint32 p_value)
{
	tinyxml2::XMLElement* pElement = p_doc.NewElement(p_name.c_str());
	pElement->SetText(p_value);
	p_node->InsertEndChild(pElement);
}

void Serializer::SerializeInt64(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, int64_t p_value)
{
	tinyxml2::XMLElement* pElement = p_doc.NewElement(p_name.c_str());
	pElement->SetText(p_value);
	p_node->InsertEndChild(pElement);
}

void Serializer::SerializeVec2(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Vector2 p_value)
{
	tinyxml2::XMLNode* element = p_doc.NewElement(p_name.c_str());
	p_node->InsertEndChild(element);

	tinyxml2::XMLElement* x = p_doc.NewElement("x");
	x->SetText(p_value.x);
	element->InsertEndChild(x);


	tinyxml2::XMLElement* y = p_doc.NewElement("y");
	y->SetText(p_value.y);
	element->InsertEndChild(y);
}

void Serializer::SerializeVec3(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Vector3 p_value)
{
	tinyxml2::XMLNode* element = p_doc.NewElement(p_name.c_str());
	p_node->InsertEndChild(element);

	tinyxml2::XMLElement* x = p_doc.NewElement("x");
	x->SetText(p_value.x);
	element->InsertEndChild(x);


	tinyxml2::XMLElement* y = p_doc.NewElement("y");
	y->SetText(p_value.y);
	element->InsertEndChild(y);

	tinyxml2::XMLElement* z = p_doc.NewElement("y");
	z->SetText(p_value.z);
	element->InsertEndChild(z);
}

void Serializer::SerializeVec4(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Vector4 p_value)
{
	tinyxml2::XMLNode* element = p_doc.NewElement(p_name.c_str());
	p_node->InsertEndChild(element);

	tinyxml2::XMLElement* x = p_doc.NewElement("x");
	x->SetText(p_value.x);
	element->InsertEndChild(x);


	tinyxml2::XMLElement* y = p_doc.NewElement("y");
	y->SetText(p_value.y);
	element->InsertEndChild(y);

	tinyxml2::XMLElement* z = p_doc.NewElement("y");
	z->SetText(p_value.z);
	element->InsertEndChild(z);

	tinyxml2::XMLElement* w = p_doc.NewElement("w");
	w->SetText(p_value.w);
	element->InsertEndChild(w);
}

void Serializer::SerializeQuat(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Quaternion p_value)
{
	tinyxml2::XMLNode* element = p_doc.NewElement(p_name.c_str());
	p_node->InsertEndChild(element);

	tinyxml2::XMLElement* x = p_doc.NewElement("x");
	x->SetText(p_value.x);
	element->InsertEndChild(x);


	tinyxml2::XMLElement* y = p_doc.NewElement("y");
	y->SetText(p_value.y);
	element->InsertEndChild(y);

	tinyxml2::XMLElement* z = p_doc.NewElement("y");
	z->SetText(p_value.z);
	element->InsertEndChild(z);

	tinyxml2::XMLElement* w = p_doc.NewElement("w");
	w->SetText(p_value.w);
	element->InsertEndChild(w);
}

void Serializer::SerializeColor3(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Color3 p_value)
{
	tinyxml2::XMLNode* element = p_doc.NewElement(p_name.c_str());
	p_node->InsertEndChild(element);

	tinyxml2::XMLElement* r = p_doc.NewElement("r");
	r->SetText(p_value.r);
	element->InsertEndChild(r);


	tinyxml2::XMLElement* g = p_doc.NewElement("g");
	g->SetText(p_value.g);
	element->InsertEndChild(g);

	tinyxml2::XMLElement* b = p_doc.NewElement("b");
	b->SetText(p_value.b);
	element->InsertEndChild(b);
}

void Serializer::SerializeColor4(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Color4 p_value)
{
	tinyxml2::XMLNode* element = p_doc.NewElement(p_name.c_str());
	p_node->InsertEndChild(element);

	tinyxml2::XMLElement* r = p_doc.NewElement("r");
	r->SetText(p_value.r);
	element->InsertEndChild(r);


	tinyxml2::XMLElement* g = p_doc.NewElement("g");
	g->SetText(p_value.g);
	element->InsertEndChild(g);

	tinyxml2::XMLElement* b = p_doc.NewElement("b");
	b->SetText(p_value.b);
	element->InsertEndChild(b);

	tinyxml2::XMLElement* a = p_doc.NewElement("a");
	a->SetText(p_value.a);
	element->InsertEndChild(a);
}

void Serializer::DeserializeBoolean(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, bool& p_value)
{
	if (auto element = p_node->FirstChildElement(p_name.c_str()); element)
		element->QueryBoolText(&p_value);
}

void Serializer::DeserializeString(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, std::string& p_value)
{
	if (auto element = p_node->FirstChildElement(p_name.c_str()); element)
	{
		const char* result = element->GetText();
		p_value = result ? result : "";
	}
}
void Serializer::DeserializeFloat(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, float& p_value)
{
	if (auto element = p_node->FirstChildElement(p_name.c_str()); element)
		element->QueryFloatText(&p_value);
}
void Serializer::DeserializeDouble(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, double& p_value)
{
	if (auto element = p_node->FirstChildElement(p_name.c_str()); element)
		element->QueryDoubleText(&p_value);
}
void Serializer::DeserializeUInt(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, uint32& p_value)
{
	if (auto element = p_node->FirstChildElement(p_name.c_str()); element)
		element->QueryUnsignedText(&p_value);
}
void Serializer::DeserializeInt64(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, int64_t& p_value)
{
	if (auto element = p_node->FirstChildElement(p_name.c_str()); element)
		element->QueryInt64Text(&p_value);
}
void Serializer::DeserializeVec2(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Vector2& p_value)
{
	if (auto node = p_node->FirstChildElement(p_name.c_str()); node)
	{
		if (auto element = node->FirstChildElement("x"); element)
			element->QueryFloatText(&p_value.x);

		if (auto element = node->FirstChildElement("y"); element)
			element->QueryFloatText(&p_value.y);
	}
}
void Serializer::DeserializeVec3(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Vector3& p_value)
{
	if (auto node = p_node->FirstChildElement(p_name.c_str()); node)
	{
		if (auto element = node->FirstChildElement("x"); element)
			element->QueryFloatText(&p_value.x);

		if (auto element = node->FirstChildElement("y"); element)
			element->QueryFloatText(&p_value.y);

		if (auto element = node->FirstChildElement("z"); element)
			element->QueryFloatText(&p_value.z);
	}
}
void Serializer::DeserializeVec4(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Vector4& p_value)
{
	if (auto node = p_node->FirstChildElement(p_name.c_str()); node)
	{
		if (auto element = node->FirstChildElement("x"); element)
			element->QueryFloatText(&p_value.x);

		if (auto element = node->FirstChildElement("y"); element)
			element->QueryFloatText(&p_value.y);

		if (auto element = node->FirstChildElement("z"); element)
			element->QueryFloatText(&p_value.z);

		if (auto element = node->FirstChildElement("w"); element)
			element->QueryFloatText(&p_value.w);
	}
}

void Serializer::DeserializeQuat(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Quaternion& p_value)
{
	if (auto node = p_node->FirstChildElement(p_name.c_str()); node)
	{
		if (auto element = node->FirstChildElement("x"); element)
			element->QueryFloatText(&p_value.x);

		if (auto element = node->FirstChildElement("y"); element)
			element->QueryFloatText(&p_value.y);

		if (auto element = node->FirstChildElement("z"); element)
			element->QueryFloatText(&p_value.z);

		if (auto element = node->FirstChildElement("w"); element)
			element->QueryFloatText(&p_value.w);
	}
}

void Serializer::DeserializeColor3(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Color3& p_value)
{
	if (auto node = p_node->FirstChildElement(p_name.c_str()); node)
	{
		if (auto element = node->FirstChildElement("r"); element)
			element->QueryFloatText(&p_value.r);

		if (auto element = node->FirstChildElement("g"); element)
			element->QueryFloatText(&p_value.g);

		if (auto element = node->FirstChildElement("b"); element)
			element->QueryFloatText(&p_value.b);
	}
}

void Serializer::DeserializeColor4(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Color4& p_value)
{
	if (auto node = p_node->FirstChildElement(p_name.c_str()); node)
	{
		if (auto element = node->FirstChildElement("r"); element)
			element->QueryFloatText(&p_value.r);

		if (auto element = node->FirstChildElement("g"); element)
			element->QueryFloatText(&p_value.g);

		if (auto element = node->FirstChildElement("b"); element)
			element->QueryFloatText(&p_value.b);

		if (auto element = node->FirstChildElement("a"); element)
			element->QueryFloatText(&p_value.a);
	}
}
