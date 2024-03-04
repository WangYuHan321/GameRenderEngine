#include "CTransform.h"

CTransform::CTransform(Actor& p_owner, Vector3 p_localPosition , Quaternion p_localRotation, Vector3 p_localScale):
	AComponent(p_owner)
{
	m_transform.GenerateMatrices(p_localPosition, p_localRotation, p_localScale);
}

std::string CTransform::GetName()
{
	return "Transform";
}

const Quaternion& CTransform::GetLocalRotation() const
{
	return m_transform.GetLocalRotation();
}

const Vector3& CTransform::GetLocalPosition() const
{
	return m_transform.GetLocalPosition();
}

const Vector3& CTransform::GetLocalScale() const
{
	return m_transform.GetLocalScale();
}

const Vector3& CTransform::GetWorldPosition() const
{
	return m_transform.GetWorldPosition();
}

const Vector3& CTransform::GetWorldScale() const
{
	return m_transform.GetWorldScale();
}

const Quaternion& CTransform::GetWorldRotation() const
{
	return m_transform.GetWorldRotation();
}


const FTransform& CTransform::GetFTransform() const
{
	return m_transform;
}

void CTransform::SetLocalRotation(Quaternion p_newQuaternion)
{
	m_transform.SetLocalRotation(p_newQuaternion);
}

void CTransform::SetLocalPosition(Vector3 p_newPosition)
{
	m_transform.SetLocalPosition(p_newPosition);
}

void CTransform::SetLocalScale(Vector3 p_newScale)
{
	m_transform.SetLocalScale(p_newScale);
}

void CTransform::SetParent(CTransform& p_parent)
{
	m_transform.SetParent(p_parent.m_transform);
}

bool CTransform::RemoveParent()
{
	return m_transform.RemoveParent();
}

void CTransform::OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{

}

void CTransform::OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{

}

void CTransform::OnInspector(WidgetContainer& p_root)
{
	auto getRot = [this]
	{
		return 	EulerAngles(GetLocalRotation().m_quat);
	};

	auto setRot = [this](Vector3 result)
	{
		SetLocalRotation(Quaternion(result));
	};

	GUIDrawer::DrawVec3(p_root, "Position", std::bind(&CTransform::GetLocalPosition, this), std::bind(&CTransform::SetLocalPosition, this, std::placeholders::_1), 0.05f);
	GUIDrawer::DrawVec3(p_root, "Rotation", getRot, setRot, 0.05f);
	GUIDrawer::DrawVec3(p_root, "Scale", std::bind(&CTransform::GetLocalScale, this), std::bind(&CTransform::SetLocalScale, this, std::placeholders::_1), 0.05f, 0.0001f);

}
