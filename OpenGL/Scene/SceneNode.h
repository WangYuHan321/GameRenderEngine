#pragma once
#include<vector>
#include<list>
#include "../Util/common.h"

class Mesh;
class Material;

class SceneNode 
{
public:
	Mesh* Mesh;
	Material* Material;

	glm::vec3 m_BoxMin = glm::vec3(-9999.9f);
	glm::vec3 m_BoxMax = glm::vec3(9999.9f);

private:
	std::vector<SceneNode*> m_Children;
	SceneNode* m_Parent;// parent pointer

	glm::mat4 m_Transform;
	glm::mat4 m_PrevTransform;
	glm::vec3 m_Position = glm::vec3(0.0f);
	glm::vec4 m_Rotation;
	glm::vec3 m_Scale = glm::vec3(1.0f);

	bool m_Dirty;// «∑Ò‘‡µÙ
	uint32 m_ID;

public:
	SceneNode(uint32 id);
	~SceneNode();

	void SetPosition(glm::vec3 pos);
	void SetRotation(glm::vec4 rot);
	void SetScale(glm::vec3 scale);
	void SetScale(float scale);
	glm::vec3 GetLocalPos();
	glm::vec4 GetLocalRotat();
	glm::vec3 GetLocalScale();
	glm::vec3 GetWorldPos();
	glm::vec3 GetWorldScale();
	glm::mat4 GetTransform();
	glm::mat4 GetPrevTransform();

	uint32 GetID();
	void AddChild(SceneNode* node);
	void RemoveChild(uint32 id);
	SceneNode* GetChildByIndex(uint32 index);
	std::vector<SceneNode*> GetChildren();
	SceneNode* GetChild(uint32 id);
	SceneNode* GetParent();
	unsigned int GetChildCount()
	{
		return m_Children.size();
	}

	void UpdateTransform(bool updatePrevTransform = false);
};