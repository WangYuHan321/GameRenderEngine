#include "AudioSource.h"

#include "../Core/AudioPlayer.h"

AudioSource::AudioSource(AudioPlayer& playerAudio):
	mAudioPlayer(playerAudio)
{
}

AudioSource::~AudioSource()
{
}