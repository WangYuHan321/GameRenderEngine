#include"../Render/Mesh/Material.h"
#include"../Render/Mesh/Mesh.h"
#include "../Core/ECS/Actor.h"
#include "../Core/ECS/Components/CCamera.h"
#include "../Core/ECS/Components/CLight.h"
#include "../Core/ECS/Components/CModelRenderer.h"
#include"SceneNode.h"
#include"Scene.h"
#include<stack>
#include <algorithm>

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

SceneNode* Scene::MakeSceneNode(Mesh mesh, Material material)
{
	SceneNode* node = new SceneNode(Scene::CounterID++);
	Root->AddChild(node);
	return node;
}

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
	return CreateActor("New Actor");
}

Actor* Scene::CreateActor(const std::string& p_name, const std::string& p_tag)
{
	m_actors.push_back(new Actor(m_availableID++, p_name, p_tag, m_isPlaying));
	auto& instance = *m_actors.back();
	instance.ComponentAddedEvent += std::bind(&Scene::OnComponentAdded, this, std::placeholders::_1);
	instance.ComponentRemovedEvent += std::bind(&Scene::OnComponentRemoved, this, std::placeholders::_1);

	if (m_isPlaying)
	{

		if (instance.IsActive())
		{
			instance.OnAwake();
			instance.OnEnable();
			instance.OnStart();
		}
	}
	return &instance;
}

void Scene::OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
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

void Scene::OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
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

const Scene::FastAccessComponents Scene::GetFastAccessComponents() const
{
	return m_fastAccessComponents;
}

void Scene::OnComponentAdded(AComponent& p_component)
{
	if (auto result = dynamic_cast<CCamera*>(&p_component); result)
		m_fastAccessComponents.cameras.push_back(result);
	if(auto result = dynamic_cast<CLight*>(&p_component); result)
		m_fastAccessComponents.lights.push_back(result);
	if (auto result = dynamic_cast<CModelRenderer*>(&p_component); result)
		m_fastAccessComponents.modelRenderers.push_back(result);

}

void Scene::OnComponentRemoved(AComponent& p_component)
{
	//std::remove
	//函数不改变所包含的“范围对象”的属性（换句话说，函数不改变数组或者容器的真实 size ）：
	//元素被移动是通过下一个不等于 val 的元素，来替换当前等于 val 的元素，而且会通过返回一个指向新 end 的迭代器，
	//来指示出新的稍“短”一些的范围（返回的迭代器所指向的元素是新的 past-the-end 元素）。
	if (auto result = dynamic_cast<CCamera*>(&p_component); result)
		m_fastAccessComponents.cameras.erase(std::remove(m_fastAccessComponents.cameras.begin(), m_fastAccessComponents.cameras.end(), result), m_fastAccessComponents.cameras.end());
	if (auto result = dynamic_cast<CLight*>(&p_component); result)
		m_fastAccessComponents.lights.erase(std::remove(m_fastAccessComponents.lights.begin(), m_fastAccessComponents.lights.end(), result), m_fastAccessComponents.lights.end());
	if (auto result = dynamic_cast<CModelRenderer*>(&p_component); result)
		m_fastAccessComponents.modelRenderers.erase(std::remove(m_fastAccessComponents.modelRenderers.begin(), m_fastAccessComponents.modelRenderers.end(), result), m_fastAccessComponents.modelRenderers.end());
}


