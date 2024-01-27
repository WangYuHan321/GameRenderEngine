#include "Transform.h"

Transform::Transform(Actor& p_owner, Vector3 p_localPosition , Quaternion p_localRotation, Vector3 p_localScale):
	AComponent(p_owner)
{
	m_transform.GenerateMatrices(p_localPosition, p_localRotation, p_localScale);
}

std::string Transform::GetName()
{
	return "Transform";
}

const Quaternion& Transform::GetLocalRotation() const
{
	return m_transform.GetLocalRotation();
}

const Vector3& Transform::GetLocalPosition() const
{
	return m_transform.GetLocalPosition();
}

const Vector3& Transform::GetLocalScale() const
{
	return m_transform.GetLocalScale();
}

void Transform::SetLocalRotation(Quaternion p_newQuaternion)
{
	m_transform.SetLocalRotation(p_newQuaternion);
}

void Transform::SetLocalPosition(Vector3 p_newPosition)
{
	m_transform.SetLocalPosition(p_newPosition);
}

void Transform::SetLocalScale(Vector3 p_newScale)
{
	m_transform.SetLocalScale(p_newScale);
}

void Transform::OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{

}

void Transform::OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{

}

void Transform::OnInspector(WidgetContainer& p_root)
{
	auto Rotat = [this]
	{
		return 	GetLocalRotation();
	};

	auto setRot = [this](Vector3 result)
	{
		SetLocalRotation(Quaternion(result));
	};




}
