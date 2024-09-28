#pragma once

#include <optional>
#include "AViewControllable.h"
#include "../../Editor/Core/GizmoBehaviour.h"

class Actor;
class TreeNode;
class GroupCollapsable;

class ModelView :public AViewControllable
{
public:
	ModelView
	(
		const std::string& p_title,
		bool p_opened,
		const PanelWindowSetting& p_panelSetting
	);
	~ModelView();
	
	virtual void Update(float deltaTime) override;
	virtual void _Render_Impl() override;

	void RenderSceneForActorPicking();
	void HandleActorPicking();
	void RenderScene();

	void InitHierarchy();

private:
	RenderTarget* m_actorPickRenderTarget;
	EGizmoOperation m_currentOperation = EGizmoOperation::TRANSLATE;

	TreeNode* m_sceneRoot;
	std::unordered_map<std::string, TreeNode*> m_widgetBoneLink;

	GizmoBehaviour m_gizmoOperations;
	std::optional<std::reference_wrapper<Actor>> m_highlightedActor;
	std::optional<GizmoBehaviour::EDirection> m_highlightedGizmoDirection;

	Actor* m_curActor;
};

