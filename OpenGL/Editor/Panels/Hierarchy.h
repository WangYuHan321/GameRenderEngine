#pragma once

#include "../../UI/Panel/PanelWindow.h"
#include "../../UI/Layout/TreeNode.h"

class Actor;

class Hierarchy : public PanelWindow
{
public:

	Hierarchy(const std::string& p_title,
		bool p_opened,
		const PanelWindowSetting p_windowSetting);

	void AddActorByInstance(Actor& p_actor);
	void DestroyActor(Actor& p_actor);
	void AttachActor(Actor& p_actor, Actor& p_other);
	void DetachActor(Actor& p_actor, Actor& p_parent);

private:
	void AddClickFunction(TreeNode& treeNode, Actor& p_actor);
	void AddContextualMenu(TreeNode& treeNode, Actor& p_actor);
	void AddDDTargetFunction(TreeNode& treeNode, Actor& p_actor);
	void AddDDSourceFunction(TreeNode& treeNode, std::string& name, Actor& p_actor);

public:
	Event<Actor&> ActorSelectedEvemt;
	Event<Actor&> ActorUnselectedEvemt;

private:
	TreeNode* m_sceneRoot;
	std::unordered_map<Actor*, TreeNode*> m_widgetActorLink;

};

