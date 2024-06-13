#pragma once

#include<string>

class Sound
{
	friend class SoundLoader;

private:
	Sound(const std::string& p_path);
public:
	const std::string path;

};

