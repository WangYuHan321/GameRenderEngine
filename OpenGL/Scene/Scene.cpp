#include"../Render/Mesh/Material.h"
#include"../Render/Mesh/Mesh.h"
#include"SceneNode.h"
#include"Scene.h"
#include<stack>

Scene::Scene()
{
	Scene::Root = new SceneNode(0);
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