#pragma once
#include "../../UI/Panel/PanelWindow.h"

class Actor;
class Group;
class ComboBox;
class InputText;
class AComponent;

class Inspector : public PanelWindow
{
public:
	Inspector
	(
		const std::string& p_title,
		bool p_opened,
		const PanelWindowSetting& p_panelSetting
	);


	~Inspector();

	void FocusActor(Actor& p_target);

	void CreateActorInspector(Actor& p_target);

	void UnFocus();

	void SoftUnFocuse();

	void DrawComponent(AComponent& p_component);

	Actor* GetCurrentActor();

private:

	Actor* m_currentActor = nullptr;
	Group* m_actorInfo;
	Group* m_inspectorHeader;
	ComboBox* m_componentSelectorWidget;
	InputText* m_scriptSelectorWidget;

	uint64_t m_componentAddedListener = 0;
	uint64_t m_componentRemovedListener = 0;
	uint64_t m_destroyedListener = 0;
};

