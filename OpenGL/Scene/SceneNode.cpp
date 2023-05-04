#include"Scene.h"
#include"SceneNode.h"
#include<glm/gtc/matrix_transform.hpp> 

glm::mat4 rotatex(glm::vec3 axis, float angle)
{
	glm::mat4 result;

	const float c = cos(angle);
	const float s = sin(angle);
	const float t = 1.0f - c;

	result[0][0] = t * axis.x * axis.x + c;
	result[0][1] = t * axis.x * axis.y + s * axis.z;
	result[0][2] = t * axis.x * axis.z - s * axis.y;

	result[1][0] = t * axis.x * axis.y - s * axis.z;
	result[1][1] = t * axis.y * axis.y + c;
	result[1][2] = t * axis.y * axis.z + s * axis.x;

	result[2][0] = t * axis.x * axis.z + s * axis.y;
	result[2][1] = t * axis.y * axis.z - s * axis.x;
	result[2][2] = t * axis.z * axis.z + c;

	return result;
}

glm::mat4 rotatex(glm::mat4 result, glm::vec3 axis, float angle)
{
	glm::mat4 rot = rotatex(axis, angle);
	result = result * rot;
	return result;
}

SceneNode::SceneNode(uint32 id) : m_ID(id)
{
	m_Parent = nullptr;
	Mesh = nullptr;
}

SceneNode::~SceneNode()
{
	for (uint32 i = 0; i < m_Children.size(); i++)
	{
		delete m_Children[i];
	}
}

void SceneNode::SetPosition(glm::vec3 pos)
{
	m_Position = pos;
	m_Dirty = true;
}

void SceneNode::SetRotation(glm::vec4 rot)
{
	m_Rotation = rot;
	m_Dirty = true;
}

void SceneNode::SetScale(glm::vec3 scale)
{
	m_Scale = scale;
	m_Dirty = true;
}

void SceneNode::SetScale(float scale)
{
	m_Scale = glm::vec3(scale);
	m_Dirty = true;
}
glm::vec3 SceneNode::GetLocalPos()
{
	return m_Position;
}
glm::vec4 SceneNode::GetLocalRotat()
{
	return m_Rotation;
}
glm::vec3 SceneNode::GetLocalScale()
{
	return m_Scale;
}
glm::vec3 SceneNode::GetWorldPos()
{
	glm::vec4 pos(m_Position, 1.0f);
	glm::vec4 result = pos * GetTransform();
	return glm::vec3(result.x, result.y, result.z);
}
glm::vec3 SceneNode::GetWorldScale()
{
	glm::mat4 tran = GetTransform();
	glm::vec3 scale = glm::vec3(tran[0][0], tran[1][1], tran[2][2]);
	if (scale.x < 0.0f) scale.x *= -1.0f;
	if (scale.y < 0.0f) scale.y *= -1.0f;
	if (scale.x < 0.0f) scale.z *= -1.0f;
	return scale;
}

glm::mat4 SceneNode::GetTransform()
{
	if (m_Dirty)
	{
		UpdateTransform(false);
	}
	return m_Transform;
}

glm::mat4 SceneNode::GetPrevTransform()
{
	return m_PrevTransform;
}

uint32 SceneNode::GetID()
{
	return m_ID;
}
void SceneNode::AddChild(SceneNode* node)
{
	if (node->m_Parent)
	{
		node->m_Parent->RemoveChild(node->m_ID);
	}
	node->m_Parent = this;
	m_Children.push_back(node);
}

SceneNode* SceneNode::GetParent()
{
	return m_Parent;
}

SceneNode* SceneNode::GetChild(uint32 id)
{
	for (unsigned int i = 0; i < m_Children.size(); ++i)
	{
		if (m_Children[i]->GetID() == id)
			return m_Children[i];
	}
	return nullptr;
}

void SceneNode::RemoveChild(uint32 id)
{
	auto it = std::find(m_Children.begin(), m_Children.end(), GetChild(id));
	if (it != m_Children.end())
		m_Children.erase(it);

}

SceneNode* SceneNode::GetChildByIndex(uint32 index)
{
	assert(index < GetChildren().size());
	return m_Children[index];
}

std::vector<SceneNode*> SceneNode::GetChildren()
{
	return m_Children;
}

void SceneNode::UpdateTransform(bool updatePrevTransform)
{
	if (updatePrevTransform)
	{
		m_PrevTransform = m_Transform;
	}

	if (m_Dirty)
	{
		m_Transform = glm::translate(m_Transform, m_Position);
		m_Transform = glm::scale(m_Transform, m_Scale);
		m_Transform = rotatex(m_Transform, glm::vec3(m_Rotation.x, m_Rotation.y, m_Rotation.z), m_Rotation.w);
		if (m_Parent)
		{
			m_Transform = m_Parent->m_Transform * m_Transform;
		}
	}
	for (uint32 i = 0; i < m_Children.size(); ++i)
	{
		if (m_Dirty)
		{
			m_Children[i]->m_Dirty = true;
		}
		m_Children[i]->UpdateTransform(updatePrevTransform);
	}
	m_Dirty = false;
}
