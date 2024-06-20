#pragma once

#include "AudioEngine.h"
#include "../Resource/Sound.h"
#include "../../Util/common.h"
#include "irrklang/irrKlang.h"

class AudioPlayer
{
public:

	AudioPlayer(AudioEngine& p_audioEngine);

	void PlaySound(const Sound& p_sound, bool p_autoPlay, bool p_looped, bool p_track);

private:
	AudioEngine& m_audioEngine;
};

