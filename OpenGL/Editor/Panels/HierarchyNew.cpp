#include "HierarchyNew.h"

#include <algorithm>
#include "../../Render/Mesh/Mesh.h"
#include "../../Core/ECS/Actor.h"
#include "../../Core/ECS/Components/CModelRenderer.h"
#include "../../UI/Plugin/ContextualMenu.h"
#include "../../UI/Plugin/DDTarget.h"
#include "../../Editor/Core/EditorAction.h"
#include "../../UI/Widgets/InputField/InputText.h"

std::vector<TreeNode*> nodesToCollapseNew;
std::vector<TreeNode*> foundNews;

HierarchyNew::HierarchyNew(const std::string& p_title,
	bool p_opened,
	const PanelWindowSetting p_windowSetting) :
	PanelWindow(p_title, p_opened, p_windowSetting)
{
	auto& searchBar = CreateWidget<InputText>();
	searchBar.ContentChangedEvent += [this](const std::string& p_content)
	{
		foundNews.clear();

		auto content = p_content;
		std::transform(content.begin(), content.end(), content.begin(), ::tolower); //tolower字母小写 将content 所有按顺序 放入content.begin()

		for (auto& [actor, item] : m_widgetBoneLink)
		{
			if (!p_content.empty())
			{
				auto itemName = item->name;
				std::transform(itemName.begin(), itemName.end(), itemName.begin(), ::tolower);

				if (itemName.find(content) != std::string::npos)
				{
					foundNews.push_back(item);
				}

				item->enabled = false;
			}
			else
			{
				item->enabled = true;
			}
		}

		for (auto node : foundNews)
		{
			node->enabled = true;
		}

	};

	m_sceneRoot = &CreateWidget<TreeNode>("Root", true);
	m_sceneRoot->Open();

	m_sceneRoot->AddPlugin< DDTarget<std::pair<Actor*, TreeNode*>> >("Actor").DataReceivedEvent += [this](std::pair<Actor*, TreeNode*> p_element)
	{
	};
}

void HierarchyNew::InitHierarcht(Actor& p_actor)
{
	if (p_actor.GetComponent<CModelRenderer>()->GetModel() != nullptr)
	{
		for (auto item : p_actor.GetComponent<CModelRenderer>()->GetModel()->GetMeshes())
		{
			m_sceneRoot->CreateWidget<TreeNode>(item->m_strName, true);
		}

	}
}