#pragma once

#include <optional>
#include "AViewControllable.h"
#include "../../Editor/Core/GizmoBehaviour.h"

class SceneView  :public AViewControllable
{
public:

	SceneView(
		const std::string& p_title,
		bool p_opened,
		const PanelWindowSetting& p_windowSettings
		);

	~SceneView();

	virtual void Update(float p_deltaTime) override;

	virtual void _Render_Impl() override;

	void RenderScene(uint8_t p_defaultRenderState);
	
	void RenderSceneForActorPicking();

	void HandleActorPicking();

	void HandleActorPicking_Ray();

private:
	RenderTarget* m_actorPickRenderTarget;
	EGizmoOperation m_currentOperation = EGizmoOperation::TRANSLATE;

	GizmoBehaviour m_gizmoOperations;
	std::optional<std::reference_wrapper<Actor>> m_highlightedActor;
	std::optional<GizmoBehaviour::EDirection> m_highlightedGizmoDirection;
};

