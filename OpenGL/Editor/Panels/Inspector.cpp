#include "Inspector.h"

#include "../../Core/ECS/Actor.h"
#include "../Core/EditorAction.h"
#include "../../UI/Layout/Group.h"
#include "../../UI/Layout/Columns.h"
#include "../../UI/Widgets/Button/Button.h"
#include "../../UI/Layout/GroupCollapsable.h"
#include "../../UI/Widgets/Selection/ComboBox.h"

#include "../../Core/ECS/Components/AComponent.h"
#include "../../Core/ECS/Components/Behaviour.h"
#include "../../Core/ECS/Components/CCamera.h"
#include "../../Core/ECS/Components/CDirectionalLight.h"
#include "../../Core/ECS/Components/CMaterialRenderer.h"
#include "../../Core/ECS/Components/CModelRenderer.h"

Inspector::Inspector
(
	const std::string& p_title,
	bool p_opened,
	const PanelWindowSetting& p_panelSetting
) : PanelWindow(p_title, p_opened, p_panelSetting)
{
	m_inspectorHeader = &CreateWidget<Group>();
	m_inspectorHeader->enabled = false;
	m_actorInfo = &CreateWidget<Group>();

	auto& headerColumers = m_inspectorHeader->CreateWidget<Columns<2>>();
	auto nameGather = [this] { return m_currentActor ? m_currentActor->GetName() : "%undef%"; };
	auto nameProvider = [this](const std::string& p_name) { if (m_currentActor) m_currentActor->SetName(p_name); };
	GUIDrawer::DrawString(headerColumers, "Name", nameGather, nameProvider);

	auto tagGatherer = [this] { return m_currentActor ? m_currentActor->GetTag() : "%undef%"; };
	auto tagProvider = [this](const std::string& p_newName) { if (m_currentActor) m_currentActor->SetTag(p_newName); };
	GUIDrawer::DrawString(headerColumers, "Tag", tagGatherer, tagProvider);

	auto activeGather = [this] { return m_currentActor ? m_currentActor->IsActive() : false; };
	auto activeProvider = [this](bool p_active) { if(m_currentActor) m_currentActor->SetActive(p_active);  };
	GUIDrawer::DrawBoolean(headerColumers, "Active", activeGather, activeProvider);

	{
		auto& componentSelectorWidget = m_inspectorHeader->CreateWidget<ComboBox>(0);
		componentSelectorWidget.lineBreak = false;
		componentSelectorWidget.choices.emplace(0, "Model Renderer");
		componentSelectorWidget.choices.emplace(1, "Camera");
		componentSelectorWidget.choices.emplace(2, "Physical Box");
		componentSelectorWidget.choices.emplace(3, "Physical Sphere");
		componentSelectorWidget.choices.emplace(4, "Physical Capsule");
		componentSelectorWidget.choices.emplace(5, "Point Light");
		componentSelectorWidget.choices.emplace(6, "Directional Light");
		componentSelectorWidget.choices.emplace(7, "Spot Light");
		componentSelectorWidget.choices.emplace(8, "Ambient Box Light");
		componentSelectorWidget.choices.emplace(9, "Ambient Sphere Light");
		componentSelectorWidget.choices.emplace(10, "Material Renderer");
		componentSelectorWidget.choices.emplace(11, "Audio Source");
		componentSelectorWidget.choices.emplace(12, "Audio Listener");

		auto& addComponentButton = m_inspectorHeader->CreateWidget<Button>("Add Component", ImVec2(100.f, 0));
		addComponentButton.idleColor = Color4(0.7f, 0.5f, 0.f, 1.0f);
		addComponentButton.textColor = Color4(1.0f, 1.0f, 1.0f, 1.0f);
		addComponentButton.ClickedEvent += [&componentSelectorWidget, this]
		{
			switch (componentSelectorWidget.currentChoice)
			{
			case 0: GetCurrentActor()->AddComponent<CModelRenderer>(); GetCurrentActor()->AddComponent<CMaterialRenderer>(); break;
			case 1: GetCurrentActor()->AddComponent<CCamera>();				break;
				//case 2: GetCurrentActor()->AddComponent<CPhysicalBox>();			break;
				//case 3: GetCurrentActor()->AddComponent<CPhysicalSphere>();		break;
				//case 4: GetCurrentActor()->AddComponent<CPhysicalCapsule>();		break;
				//case 5: GetCurrentActor()->AddComponent<CPointLight>();			break;
			case 6: GetCurrentActor()->AddComponent<CDirectionalLight>();	break;
				//case 7: GetCurrentActor()->AddComponent<CSpotLight>();			break;
				//case 8: GetCurrentActor()->AddComponent<CAmbientBoxLight>();		break;
				//case 9: GetCurrentActor()->AddComponent<CAmbientSphereLight>();	break;
			case 10: GetCurrentActor()->AddComponent<CMaterialRenderer>();	break;
				//case 11: GetCurrentActor()->AddComponent<CAudioSource>();		break;
				//case 12: GetCurrentActor()->AddComponent<CAudioListener>();		break;
			}

			componentSelectorWidget.ValueChangedEvent.Invoke(componentSelectorWidget.currentChoice);
		};

	}

}

Inspector::~Inspector()
{
}

void Inspector::FocusActor(Actor& p_target)
{
	if (m_currentActor)
		UnFocus();

	m_actorInfo->RemoveAllWidgets();

	m_currentActor = &p_target;

	m_inspectorHeader->enabled = true;

	CreateActorInspector(p_target);

	EDITOR_EVENT(ActorSelectedEvent).Invoke(*m_currentActor);
}

void Inspector::CreateActorInspector(Actor& p_target)
{
	std::map<std::string, AComponent*> components;

	for (auto component : p_target.GetComponents())
		if (component->GetName() != "Transform")
			components[component->GetName()] = component.get();

	auto transform = p_target.GetComponent<CTransform>();
	if (transform)
		DrawComponent(*transform);

	for (auto& [name, instance] : components)
		DrawComponent(*instance);
}

void Inspector::UnFocus()
{
	if (m_currentActor)
	{
		m_currentActor->ComponentAddedEvent -= m_componentAddedListener;
		m_currentActor->ComponentRemovedEvent -= m_componentRemovedListener;
	}
}

void Inspector::SoftUnFocuse()
{
	if (m_currentActor)
	{
		EDITOR_EVENT(ActorUnSelectedEvent).Invoke(*m_currentActor);
		m_inspectorHeader->enabled = false;
		m_currentActor = nullptr;
		m_actorInfo->RemoveAllWidgets();
	}
}

void Inspector::DrawComponent(AComponent& p_component)
{
	if (auto inspectorItem = dynamic_cast<IInspectorItem*>(&p_component); inspectorItem)
	{
		auto& header = m_actorInfo->CreateWidget<GroupCollapsable>(p_component.GetName());
		header.closeable = !dynamic_cast<CTransform*>(&p_component);//不是Transofrm都隐藏
		header.CloseEvent += [this, &header, &p_component]
		{
			if (p_component.owner.RemoveComponent(p_component))
				m_componentSelectorWidget->ValueChangedEvent.Invoke(m_componentSelectorWidget->currentChoice);
		};
		auto& columns = header.CreateWidget<Columns<2>>();
		columns.widths[0] = 200;
		inspectorItem->OnInspector(columns);//有派生类去实现
	}
}

Actor* Inspector::GetCurrentActor()
{
	return m_currentActor;
}
