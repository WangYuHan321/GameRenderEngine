#include "CAudioSource.h"
CAudioSource::CAudioSource(Actor& p_owner):
	AComponent(p_owner)
{
}

std::string CAudioSource::GetName()
{
	return "CAudioSource";
}

void CAudioSource::SetSound(Sound* p_sound)
{
	m_sound = p_sound;
}