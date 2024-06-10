#include "AudioListener.h"

Event<AudioListener&> AudioListener::CreateEvent;
Event<AudioListener&> AudioListener::DestroyEvent;

AudioListener::AudioListener():
	m_transform(new FTransform()),
	m_internalTransform(true)
{
	SetUp();
}

AudioListener::AudioListener(FTransform& p_transform):
	m_transform(&p_transform),
	m_internalTransform(false)
{
	SetUp();
}

AudioListener::~AudioListener()
{
	DestroyEvent.Invoke(*this);
}

FTransform& AudioListener::GetTransform()
{
	return *m_transform;
}

void AudioListener::SetEnabled(bool p_enable)
{
	m_enable = p_enable;
}

bool AudioListener::IsEnabled() const
{
	return m_enable;
}

void AudioListener::SetUp()
{
	CreateEvent.Invoke(*this);
}