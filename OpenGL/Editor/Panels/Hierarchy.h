#pragma once

#include "../../UI/Panel/PanelWindow.h"
#include "../../Core/ECS/Actor.h"
#include "../../UI/Layout/TreeNode.h"

class Hierarchy : public PanelWindow
{
public:

	Hierarchy(const std::string& p_title,
		bool p_opened,
		const PanelWindowSetting p_windowSetting);

public:
	Event<Actor&> ActorSelectedEvemt;
	Event<Actor&> ActorUnselectedEvemt;

private:
	TreeNode* m_sceneRoot;
	std::unordered_map<Actor*, TreeNode*> m_widgetActorLink;

};

