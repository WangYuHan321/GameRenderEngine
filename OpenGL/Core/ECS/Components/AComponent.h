#pragma once
/// Actor.h ºÍ AComponent.h 2
#include "../../API/IInspectorItem.h"

class Actor;

class AComponent : public IInspectorItem
{
public:
	AComponent(Actor& p_owner);

	virtual ~AComponent();

	virtual void OnAwake() {}

	virtual void OnStart() {}

	virtual void OnEnable() {}

	virtual void OnDisable() {}

	virtual void OnDestroy() {}

	virtual void OnUpdate(float p_deltaTime) {}

	virtual void OnFixedUpdate(float p_deltaTime) {}

	virtual void OnLateUpdate(float p_deltaTime) {}

	virtual std::string GetName() = 0;

public:
	Actor& owner;
};

