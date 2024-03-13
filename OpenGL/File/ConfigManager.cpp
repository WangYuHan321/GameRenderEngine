#include "ConfigManager.h"
#include <cstdlib>

ConfigManager::ConfigManager()
{

}

ConfigManager::~ConfigManager()
{

}

std::string ConfigManager::GetExecutePath() const
{
	char const* envRoot = getenv("ASSIMP");
	std::string path = std::string(envRoot) + "/../../../Bin";
	return path;
}

std::string ConfigManager::GetEnginePath() const
{
	std::string exePath = GetExecutePath();
	std::string path = exePath + "/Data/Engine";
	return path;
}

std::string ConfigManager::GetEditorPath() const
{
	std::string exePath = GetExecutePath();
	std::string path = exePath + "/Data/Editor";
	return path;
}




