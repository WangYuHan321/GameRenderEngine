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

	virtual void OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

	virtual void OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

	virtual void OnInspector(WidgetContainer& p_root) override;

private:
	Sound* m_sound = nullptr;
	AudioSource m_audioSource;
	bool m_autoPlay = false;;

};

