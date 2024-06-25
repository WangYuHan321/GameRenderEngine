
#include "../../Event/Event.h"

class AudioPlayer;

class AudioSource
{
public:

	AudioSource(AudioPlayer& playerAudio);
	~AudioSource();


public:
	static Event<AudioSource&> CreateEvent;
	static Event<AudioSource&> DestroyEvent;

private:
	AudioPlayer& mAudioPlayer;


};