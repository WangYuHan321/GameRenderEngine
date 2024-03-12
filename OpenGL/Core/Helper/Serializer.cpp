#include "Serializer.h"
#include "../../Render/Shader/EShader.h"
#include "../../Global/ServiceLocator.h"
#include "../../Render/Resource/ModelManager.h"
#include "../../Render/Resource/ShaderManager.h"
#include "../../Render/Resource/TextureManager.h"

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
	x->SetText(p_value.m_quat.x);
	element->InsertEndChild(x);


	tinyxml2::XMLElement* y = p_doc.NewElement("y");
	y->SetText(p_value.m_quat.y);
	element->InsertEndChild(y);

	tinyxml2::XMLElement* z = p_doc.NewElement("y");
	z->SetText(p_value.m_quat.z);
	element->InsertEndChild(z);

	tinyxml2::XMLElement* w = p_doc.NewElement("w");
	w->SetText(p_value.m_quat.w);
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

void Serializer::SerializeTexture(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Texture* p_value)
{
	SerializeString(p_doc, p_node, p_name.c_str(), p_value ? p_value->Path : "?");
}

void Serializer::SerializeTextureCube(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, TextureCube* p_value)
{
	SerializeString(p_doc, p_node, p_name.c_str(), p_value ? p_value->Path : "?");
}

void Serializer::SerializeShader(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, CShader* p_value)
{
	SerializeString(p_doc, p_node, p_name.c_str(), p_value ? p_value->GetShaderPath() : "Empty Shader");
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
			element->QueryFloatText(&p_value.m_quat.x);

		if (auto element = node->FirstChildElement("y"); element)
			element->QueryFloatText(&p_value.m_quat.y);

		if (auto element = node->FirstChildElement("z"); element)
			element->QueryFloatText(&p_value.m_quat.z);

		if (auto element = node->FirstChildElement("w"); element)
			element->QueryFloatText(&p_value.m_quat.w);
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

void Serializer::DeserializeTexture(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Texture*& p_value)
{
	if (std::string path = DeserializeString(p_doc, p_node, p_name.c_str()); path != "?" && path != "")
		p_value = ServiceLocator::getInstance()->Get<TextureManager>().GetResource(path);
	else
		p_value = nullptr;
}

void Serializer::DeserializeTextureCube(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, TextureCube*& p_value)
{
	//if (std::string path = DeserializeString(p_doc, p_node, p_name.c_str()); path != "?" && path != "")
	//	p_value = ServiceLocator::getInstance()->Get<TextureManager>().GetResource(path);
	//else
		p_value = nullptr;
}

void Serializer::DeserializeShader(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, CShader*& p_out)
{
	if (std::string path = DeserializeString(p_doc, p_node, p_name.c_str()); path != "?" && path != "")
		p_out = ServiceLocator::getInstance()->Get<ShaderManager>().GetResource(path);
	else
		p_out = nullptr;
}


bool Serializer::DeserializeBoolean(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name)
{
	bool result;
	DeserializeBoolean(p_doc, p_node, p_name, result);
	return result;
}

std::string Serializer::DeserializeString(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name)
{
	std::string result;
	DeserializeString(p_doc, p_node, p_name, result);
	return result;
}

float Serializer::DeserializeFloat(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name)
{
	float result;
	DeserializeFloat(p_doc, p_node, p_name, result);
	return result;
}

double Serializer::DeserializeDouble(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name)
{
	double result;
	DeserializeDouble(p_doc, p_node, p_name, result);
	return result;
}

uint32 Serializer::DeserializeUInt(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name)
{
	uint32 result;
	DeserializeUInt(p_doc, p_node, p_name, result);
	return result;
}

int64_t Serializer::DeserializeInt64(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name)
{
	int64_t result;
	DeserializeInt64(p_doc, p_node, p_name, result);
	return result;
}

Vector2 Serializer::DeserializeVec2(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name)
{
	Vector2 result;
	DeserializeVec2(p_doc, p_node, p_name, result);
	return result;
}

Vector3 Serializer::DeserializeVec3(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name)
{
	Vector3 result;
	DeserializeVec3(p_doc, p_node, p_name, result);
	return result;
}

Vector4 Serializer::DeserializeVec4(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name)
{
	Vector4 result;
	DeserializeVec4(p_doc, p_node, p_name, result);
	return result;
}

Quaternion Serializer::DeserializeQuat(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name)
{
	Quaternion result;
	DeserializeQuat(p_doc, p_node, p_name, result);
	return result;
}

Color3 Serializer::DeserializeColor3(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name)
{
	Color3 result(0 , 0, 0);
	DeserializeColor3(p_doc, p_node, p_name, result);
	return result;
}

Color4 Serializer::DeserializeColor4(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name)
{
	Color4 result(0, 0, 0, 1);
	DeserializeColor4(p_doc, p_node, p_name, result);
	return result;
}

Texture* Serializer::DeserializeTexture(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name)
{
	Texture* result;
	DeserializeTexture(p_doc, p_node, p_name, result);
	return result;
}

TextureCube* Serializer::DeserializeTextureCube(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name)
{
	TextureCube* result;
	DeserializeTextureCube(p_doc, p_node, p_name, result);
	return result;
}

CShader* Serializer::DeserializeShader(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name)
{
	CShader* result;
	DeserializeShader(p_doc, p_node, p_name, result);
	return result;
}

