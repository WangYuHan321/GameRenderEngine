#include "AComponent.h"
#include "../Actor.h"

AComponent::AComponent(Actor& p_owner) : owner(p_owner)
{
}

AComponent::~AComponent()
{
	if (owner.IsActive())
	{
		OnDisable();
		OnDestroy();
	}
}