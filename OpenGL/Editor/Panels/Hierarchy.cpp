#include "Hierarchy.h"

#include "../../UI/Plugin/ContextualMenu.h"
#include "../../UI/Plugin/DDTarget.h"
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

	};
	
	m_sceneRoot = &CreateWidget<TreeNode>("Root", true);
	m_sceneRoot->Open();

	Event<std::pair<Actor*, TreeNode*>>s;

	m_sceneRoot->AddPlugin< DDTarget<std::pair<Actor*, TreeNode*>> >("Actor").DataReceivedEvent += [this](std::pair<Actor*, TreeNode*> p_element)
	{
	};

	m_sceneRoot->AddPlugin<HierarchyContextualMenu>(nullptr, *m_sceneRoot);

}