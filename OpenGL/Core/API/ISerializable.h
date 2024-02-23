#pragma once
/// <summary>
///  by Overload Engine 
///  WangYuHan 2023 5.23
/// </summary>
#include "tinyxml2.h"


class ISerializable
{
public:
	virtual void OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node) = 0;

	virtual void OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node) = 0;

	virtual ~ISerializable() = default;
};

