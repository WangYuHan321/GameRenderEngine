#include "AudioPlayer.h"

AudioPlayer::AudioPlayer(AudioEngine& p_audioEngine): m_audioEngine(p_audioEngine)
{
}

void AudioPlayer::PlaySound(const Sound& p_sound, bool p_autoPlay, bool p_looped, bool p_track)
{
	irrklang::ISound* sound = m_audioEngine.GetIrrklangEngine()->play2D((m_audioEngine.GetWorkingDirectory() + p_sound.path).c_str(), p_looped, p_autoPlay, p_track);
}