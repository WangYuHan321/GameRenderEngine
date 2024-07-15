#include "AudioEngine.h"
#include "irrklang/irrKlang.h"

#include "../Entity/AudioListener.h"

AudioEngine::AudioEngine(const std::string& p_workingDirectory)
{
	m_irrklangEngine = irrklang::createIrrKlangDevice();
}

AudioEngine::~AudioEngine()
{
}

void AudioEngine::Update()
{
	m_irrklangEngine->setListenerPosition({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, -1.0f });
}

