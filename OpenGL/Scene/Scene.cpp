#include"../Render/Mesh/Material.h"
#include"../Render/Mesh/Mesh.h"
#include "../Core/ECS/Actor.h"
#include"SceneNode.h"
#include"Scene.h"
#include<stack>
#include <algorithm>

Scene::Scene()
{
	Root = new SceneNode(0);
}

Scene::~Scene()
{
	Scene::DeleteSceneNode(Root);
}

void Scene::Clear()
{
	Scene::DeleteSceneNode(Root);
	Scene::Root = new SceneNode(0);
}

Actor* Scene::CreateActor()
{
	return nullptr;
}

Actor* Scene::CreateActor(const std::string& p_name, const std::string& p_tag)
{
	return nullptr;
}

SceneNode* Scene::MakeSceneNode(Mesh mesh, Material material)
{
	SceneNode* node = new SceneNode(Scene::CounterID++);
	Root->AddChild(node);
	return node;
}

SceneNode* Scene::MakeSceneNode(SceneNode* node)
{
	SceneNode* newNode = new SceneNode(Scene::CounterID++);

	newNode->Mesh = node->Mesh;
	newNode->Material = node->Material;
	newNode->m_BoxMin = node->m_BoxMin;
	newNode->m_BoxMax = node->m_BoxMax;

	std::stack<SceneNode*> nodeStack;
	for (uint32 i = 0; i < node->GetChildren().size(); ++i)
	{
		nodeStack.push(node->GetChildByIndex(i));
	}
	while (!nodeStack.empty())
	{
		SceneNode* child = nodeStack.top();
		nodeStack.pop();
		SceneNode* newChild = new SceneNode(Scene::CounterID++);
		newChild->Mesh = child->Mesh;
		newChild->Material = child->Material;
		newChild->m_BoxMin = child->m_BoxMin;
		newChild->m_BoxMax = child->m_BoxMax;
		newNode->AddChild(newChild);

		for (unsigned int i = 0; i < child->GetChildren().size(); ++i)
			nodeStack.push(child->GetChildByIndex(i));
	}

	Root->AddChild(newNode);
	return newNode;
}

void Scene::DeleteSceneNode(SceneNode* node)
{
	if (node->GetParent())
	{
		node->GetParent()->RemoveChild(node->GetID());
	}
	Scene::CounterID = 0;
	delete node;
}

void Scene::OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{
	tinyxml2::XMLNode* sceneNode = p_doc.NewElement("scene");
	p_node->InsertEndChild(sceneNode);

	tinyxml2::XMLNode* actorNode = p_doc.NewElement("actors");
	sceneNode->InsertEndChild(actorNode);

	for (auto& actor : m_actors)
	{
		actor->OnSerialize(p_doc, actorNode);
	}
}

void Scene::OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{

	tinyxml2::XMLNode* actorRoot = p_node->FirstChildElement("actors");

	if (actorRoot)
	{
		tinyxml2::XMLElement* curActor = actorRoot->FirstChildElement("actor");

		int64_t maxID = 1;
		while (curActor)
		{
			auto actor = CreateActor();
			actor->OnDeserialize(p_doc, curActor);
			maxID = std::max(actor->GetID() + 1, maxID);
			curActor = curActor->NextSiblingElement("actor");
		}

		m_availableID = maxID;

		for (auto actor : m_actors)
		{
			if (actor->GetParentID() > 0)
			{
				if (auto found = FindActorByID(actor->GetParentID()); found)
					actor->SetParent(*found);
			}
		}
	}	
}

Actor* Scene::FindActorByID(int64_t p_id)
{
	auto result = std::find_if(m_actors.begin(), m_actors.end(), [p_id](Actor* element)
		{
			return element->GetID() == p_id;
		});

	if (result != m_actors.end())
		return *result;
	else
		return nullptr;
}


