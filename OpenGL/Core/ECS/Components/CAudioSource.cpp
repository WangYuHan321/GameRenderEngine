#include "CAudioSource.h"

#include "../../Audio/Core/AudioPlayer.h"
#include "../../Global/ServiceLocator.h"

CAudioSource::CAudioSource(Actor& p_owner):
	AComponent(p_owner),
	m_audioSource(ServiceLocator::getInstance()->Get<AudioPlayer>())
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

void CAudioSource::OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{

}

void CAudioSource::OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{

}

void CAudioSource::OnInspector(WidgetContainer& p_root)
{
	
}
