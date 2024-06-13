#include <string>
#include <vector>

class AudioSource;
class AudioListener;

namespace irrklang 
{ 
	class ISoundEngine;
}

class AudioEngine
{
public:
	AudioEngine(const std::string& p_workingDirectory);
	~AudioEngine();


private:
	std::vector<std::reference_wrapper<AudioSource>> m_audioSources;
	std::vector<std::reference_wrapper<AudioListener>> m_audioListeners;

	irrklang::ISoundEngine* m_irrklangEngine = nullptr;
};