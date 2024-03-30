#pragma once
#include "../../UI/Panel/PanelWindow.h"
#include "../../UI/Layout/TreeNode.h"

class Actor;

class HierarchyNew : public PanelWindow
{
public:

	HierarchyNew(const std::string& p_title,
		bool p_opened,
		const PanelWindowSetting p_windowSetting);

	void SelectedActor(Actor& p_actor);
private:
	TreeNode* m_sceneRoot;
	std::unordered_map<std::string, TreeNode*> m_widgetBoneLink;
};
