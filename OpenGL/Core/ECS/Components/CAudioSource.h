#pragma once

#include "../Actor.h"
#include "../../Audio/Entity/AudioSource.h"
#include "../../Audio/Resource/Sound.h"

class CAudioSource : public AComponent
{

public:
	CAudioSource(Actor& p_owner);

	std::string GetName() override;

	void SetSound(Sound* p_sound);


private:
	Sound* m_sound = nullptr;
	//AudioSource m_audioSource;
	bool m_autoPlay = false;;

};

