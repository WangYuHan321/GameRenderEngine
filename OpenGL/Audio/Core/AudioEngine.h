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

	void Update();

	irrklang::ISoundEngine* GetIrrklangEngine() { return m_irrklangEngine; }
	std::string GetWorkingDirectory() { return ""; }

private:
	std::vector<std::reference_wrapper<AudioSource>> m_audioSources;
	std::vector<std::reference_wrapper<AudioListener>> m_audioListeners;

	irrklang::ISoundEngine* m_irrklangEngine = nullptr;
};