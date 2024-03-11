#pragma once
#include "../../../Util/common.h"

#include "../../Core/API/tinyxml2.h"

using namespace tinyxml2;

class CShader;

class Serializer
{
public:

	static void SerializeBoolean(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, bool p_value);
	static void SerializeString(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, std::string p_value);
	static void SerializeFloat(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, float p_value);
	static void SerializeDouble(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, double p_value);
	static void SerializeUInt(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, uint32 p_value);
	static void SerializeInt64(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, int64_t p_value);
	static void SerializeVec2(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Vector2 p_value);
	static void SerializeVec3(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Vector3 p_value);
	static void SerializeVec4(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Vector4 p_value);
	static void SerializeQuat(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Quaternion p_value);
	static void SerializeColor3(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Color3 p_value);
	static void SerializeColor4(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Color4 p_value);
	static void SerializeShader(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, CShader* p_value);

	static void DeserializeBoolean(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, bool& p_value);
	static void DeserializeString(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, std::string& p_value);
	static void DeserializeFloat(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, float& p_value);
	static void DeserializeDouble(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, double& p_value);
	static void DeserializeUInt(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, uint32& p_value);
	static void DeserializeInt64(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, int64_t& p_value);
	static void DeserializeVec2(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Vector2& p_value);
	static void DeserializeVec3(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Vector3& p_value);
	static void DeserializeVec4(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Vector4& p_value);
	static void DeserializeQuat(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Quaternion& p_value);
	static void DeserializeColor3(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Color3& p_value);
	static void DeserializeColor4(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Color4& p_value);
	static void DeserializeShader(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, CShader*& p_out);

	static std::string DeserializeString(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
	static CShader* DeserializeShader(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
};

