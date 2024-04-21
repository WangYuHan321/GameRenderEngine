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

std::string ConfigManager::GetFontPath() const
{
	std::string enginePath = GetEnginePath();
	std::string path = enginePath + "/Font";
	return path;
}

std::string ConfigManager::GetScriptPath() const
{
	std::string enginePath = GetEnginePath();
	std::string path = enginePath + "/Script";
	return path;
}

std::string ConfigManager::GetXmlPath() const
{
	return GetEditorPath() + "/Xml";
}

std::string ConfigManager::GetProjectPath() const
{
	return GetEditorPath();
}




