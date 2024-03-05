#pragma once

#include "../../../Util/common.h"
#include"AComponent.h"

class Actor;

class CTransform : public AComponent
{
public:

	CTransform(Actor& p_owner, Vector3 p_localPosition = Vector3(0.0f, 0.0f, 0.0f), Quaternion p_localRotation = Quaternion(0.0f, 0.0f, 0.0f, 1.0f), Vector3 p_localScale = Vector3(1.0f, 1.0f, 1.0f));

	std::string GetName() override;

	const Quaternion& GetLocalRotation() const;
	const Vector3& GetLocalPosition() const;
	const Vector3& GetLocalScale() const;
	const Matrix4& GetLocalMatrix4() const;

	const Vector3& GetWorldPosition() const;
	const Vector3& GetWorldScale() const;
	const Quaternion& GetWorldRotation() const;
	const Matrix4& GetWorldMatrix() const;

	const FTransform& GetFTransform()const;

	void SetLocalRotation(Quaternion p_newQuaternion);
	void SetLocalPosition(Vector3 p_newPosition);
	void SetLocalScale(Vector3 p_newScale);

	void SetParent(CTransform& p_parent);
	bool RemoveParent();

	virtual void OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

	virtual void OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

	virtual void OnInspector(WidgetContainer& p_root) override;


private:

	FTransform m_transform;

};

