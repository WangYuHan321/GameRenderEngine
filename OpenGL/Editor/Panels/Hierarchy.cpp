#include "Hierarchy.h"

#include <algorithm>
#include "MaterialEditor.h"
#include "../../Core/ECS/Actor.h"
#include "../../UI/Plugin/ContextualMenu.h"
#include "../../UI/Plugin/DDSource.h"
#include "../../UI/Plugin/DDTarget.h"
#include "../../Editor/Core/EditorAction.h"
#include "../../UI/Widgets/InputField/InputText.h"
#include "../../Editor/Core/EditorAction.h"
#include "../../Core/ECS/Components/CMaterialRenderer.h"

class HierarchyContextualMenu : public ContextualMenu
{
public:
	HierarchyContextualMenu(Actor* p_target, TreeNode& p_treeNode, bool p_panelMenu = false):
		m_target(p_target),
		m_treeNode(p_treeNode)
	{
		if (m_target)
		{
			auto& editorActorBtn = CreateWidget<MenuItem>("Editor Material");
			editorActorBtn.ClickedEvent += [this]
			{
				if (m_target->GetComponent<CMaterialRenderer>() != nullptr)
				{
					// wirte on modify
					EDITOR_PANEL(MaterialEditor, "MaterialEditor").SetOpened(true);
					EDITOR_PANEL(MaterialEditor, "MaterialEditor").SetTarget(m_target->GetComponent<CMaterialRenderer>()->GetMaterialList()[0]);
				}
			};

		}

	}

private:
	Actor* m_target;
	TreeNode& m_treeNode;
};

std::vector<TreeNode*> nodesToCollapse;
std::vector<TreeNode*> founds;

Hierarchy::Hierarchy(const std::string& p_title,
	bool p_opened,
	const PanelWindowSetting p_windowSetting):
	PanelWindow(p_title, p_opened, p_windowSetting)
{
	auto& searchBar = CreateWidget<InputText>();
	searchBar.ContentChangedEvent += [this](const std::string& p_content)
	{
		founds.clear();

		auto content = p_content;
		std::transform(content.begin(), content.end(), content.begin(), ::tolower); //tolower字母小写 将content 所有按顺序 放入content.begin()

		for (auto& [actor, item] : m_widgetActorLink)
		{
			if (!p_content.empty())
			{
				auto itemName = item->name;
				std::transform(itemName.begin(), itemName.end(), itemName.begin(), ::tolower);

				if (itemName.find(content) != std::string::npos)
				{
					founds.push_back(item);
				}

				item->enabled = false;
			}
			else
			{
				item->enabled = true;
			}
		}

		for (auto node : founds)
		{
			node->enabled = true;
		}

	};
	
	m_sceneRoot = &CreateWidget<TreeNode>("Root", true);
	m_sceneRoot->Open();

	Event<std::pair<Actor*, TreeNode*>>s;

	m_sceneRoot->AddPlugin< DDTarget<std::pair<Actor*, TreeNode*>> >("Actor").DataReceivedEvent += [this](std::pair<Actor*, TreeNode*> p_element)
	{
	};

	m_sceneRoot->AddPlugin<HierarchyContextualMenu>(nullptr, *m_sceneRoot);

	Actor::CreateEvent += std::bind(&Hierarchy::AddActorByInstance, this, std::placeholders::_1);
	Actor::DestroyedEvent += std::bind(&Hierarchy::DestroyActor, this, std::placeholders::_1);
	Actor::AttachEvent += std::bind(&Hierarchy::AttachActor, this, std::placeholders::_1, std::placeholders::_2);
	Actor::DettachEvent += std::bind(&Hierarchy::DetachActor, this, std::placeholders::_1, std::placeholders::_2);
}

void Hierarchy::AddContextualMenu(TreeNode& treeNode, Actor& p_actor)
{
	treeNode.AddPlugin<HierarchyContextualMenu>(&p_actor, treeNode);
}

void Hierarchy::AddDDTargetFunction(TreeNode& treeNode, Actor& p_actor)
{
	treeNode.AddPlugin<DDTarget<Actor*>>("Scene_Actor").DataReceivedEvent += [&treeNode, &p_actor, this](Actor* p_otherActor)
	{
		LOG_INFO(p_otherActor->GetName());
		p_otherActor->SetParent(p_actor);

		bool isLeaf = m_widgetActorLink[p_otherActor]->leaf;
		m_sceneRoot->RemoveWidget(*m_widgetActorLink[p_otherActor]);
		std::unordered_map<Actor*, TreeNode*>::iterator it = m_widgetActorLink.find(p_otherActor);
		if (it != m_widgetActorLink.end()) {
			m_widgetActorLink[&p_actor]->leaf = false;
			m_widgetActorLink[p_otherActor] = &m_widgetActorLink[&p_actor]->CreateWidget<TreeNode>(p_otherActor->GetName(), true);

			AddContextualMenu(*m_widgetActorLink[p_otherActor], *p_otherActor);
			AddDDTargetFunction(*m_widgetActorLink[p_otherActor], *p_otherActor);
			AddDDSourceFunction(*m_widgetActorLink[p_otherActor], p_otherActor->GetName(), *p_otherActor);

			m_widgetActorLink[p_otherActor]->leaf = isLeaf;
		}
	};
}

void Hierarchy::AddDDSourceFunction(TreeNode& treeNode, std::string& name, Actor& p_actor)
{
	treeNode.AddPlugin<DDSource<Actor*>>("Scene_Actor", name, &p_actor);
}

void Hierarchy::AddActorByInstance(Actor& p_actor)
{
	if (p_actor.HasParent())
	{
		if(m_widgetActorLink.find(p_actor.GetParent()) != m_widgetActorLink.end())
		{
			//if contain widget Actor
			auto& textSelectable = m_widgetActorLink[p_actor.GetParent()]->CreateWidget<TreeNode>(p_actor.GetName(), true);
			textSelectable.leaf = true;//是叶子节点
			textSelectable.AddPlugin<HierarchyContextualMenu>(&p_actor, textSelectable);

			m_widgetActorLink[&p_actor] = &textSelectable;
		}
		else
		{
			auto& parentSelectable = m_sceneRoot->CreateWidget<TreeNode>(p_actor.GetParent()->GetName(), true);
			parentSelectable.leaf = true;//是叶子节点
			parentSelectable.AddPlugin<HierarchyContextualMenu>(&p_actor, parentSelectable);

			m_widgetActorLink[p_actor.GetParent()] = &parentSelectable;

			auto& textSelectable = parentSelectable.CreateWidget<TreeNode>(p_actor.GetName(), true);
			textSelectable.leaf = true;//是叶子节点
			textSelectable.AddPlugin<HierarchyContextualMenu>(&p_actor, textSelectable);

			m_widgetActorLink[&p_actor] = &parentSelectable;
		}
	}
	else
	{
		auto& textSelectable = m_sceneRoot->CreateWidget<TreeNode>(p_actor.GetName(), true);
		textSelectable.leaf = true;//是叶子节点

		AddContextualMenu(textSelectable , p_actor);
		AddDDSourceFunction(textSelectable, p_actor.GetName(), p_actor);
		AddDDTargetFunction(textSelectable, p_actor);

		m_widgetActorLink[&p_actor] = &textSelectable;

		textSelectable.ClickedEvent += EDITOR_BIND(SelectActor, std::ref(p_actor));
	}

}

void Hierarchy::DestroyActor(Actor& p_actor)
{
	std::unordered_map<Actor*, TreeNode*>::iterator it = m_widgetActorLink.find(&p_actor);
	if (it != m_widgetActorLink.end()) 
	{
		if (p_actor.GetParent() != nullptr)
			m_widgetActorLink[p_actor.GetParent()]->RemoveWidget(*m_widgetActorLink[&p_actor]);
		else
			m_sceneRoot->RemoveWidget(*m_widgetActorLink[&p_actor]);
	}
}

void Hierarchy::AttachActor(Actor& p_actor, Actor& p_other)//actor to parent
{
	bool isLeaf = m_widgetActorLink[&p_actor]->leaf;
	m_sceneRoot->RemoveWidget(*m_widgetActorLink[&p_actor]);
	std::unordered_map<Actor*, TreeNode*>::iterator it = m_widgetActorLink.find(&p_other);
	if (it != m_widgetActorLink.end()) {
		m_widgetActorLink[&p_other]->leaf = false;
		m_widgetActorLink[&p_actor] = &m_widgetActorLink[&p_other]->CreateWidget<TreeNode>(p_actor.GetName(), true);

		AddContextualMenu(*m_widgetActorLink[&p_actor], p_actor);
		AddDDTargetFunction(*m_widgetActorLink[&p_actor], p_actor);
		AddDDSourceFunction(*m_widgetActorLink[&p_actor], p_actor.GetName(), p_actor);

		m_widgetActorLink[&p_actor]->leaf = isLeaf;
	}

}

void Hierarchy::DetachActor(Actor& p_actor, Actor& p_parent)
{
	std::unordered_map<Actor*, TreeNode*>::iterator it = m_widgetActorLink.find(&p_parent);
	if (it != m_widgetActorLink.end()) {
		m_widgetActorLink[&p_parent]->RemoveWidget(*m_widgetActorLink[&p_actor]);
		m_widgetActorLink[&p_actor] = &m_sceneRoot->CreateWidget<TreeNode>(p_actor.GetName());
		
		AddContextualMenu(*m_widgetActorLink[&p_actor], p_actor);
		AddDDTargetFunction(*m_widgetActorLink[&p_actor], p_actor);
		AddDDSourceFunction(*m_widgetActorLink[&p_actor], p_actor.GetName(), p_actor);

		m_widgetActorLink[&p_actor]->leaf = true;
	}

}


#include"../Core/EditorAction.h"