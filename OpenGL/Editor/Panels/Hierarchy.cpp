#include "Hierarchy.h"

#include <algorithm>
#include "../../Core/ECS/Actor.h"
#include "../../UI/Plugin/ContextualMenu.h"
#include "../../UI/Plugin/DDTarget.h"
#include "../../Editor/Core/EditorAction.h"
#include "../../UI/Widgets/InputField/InputText.h"

class HierarchyContextualMenu : public ContextualMenu
{
public:
	HierarchyContextualMenu(Actor* p_target, TreeNode& p_treeNode, bool p_panelMenu = false):
		m_target(p_target),
		m_treeNode(p_treeNode)
	{
		if (m_target)
		{

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

}

void Hierarchy::AddActorByInstance(Actor& p_actor)
{
	auto& textSelectable = m_sceneRoot->CreateWidget<TreeNode>(p_actor.GetName(), true);
	textSelectable.leaf = true;//是叶子节点
	textSelectable.AddPlugin<HierarchyContextualMenu>(&p_actor, textSelectable);

	m_widgetActorLink[&p_actor] = &textSelectable;

	textSelectable.ClickedEvent += EDITOR_BIND(SelectActor, std::ref(p_actor));
}


#include"../Core/EditorAction.h"