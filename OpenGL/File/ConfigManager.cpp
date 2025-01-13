#include "ConfigManager.h"
#include <cstdlib>
#include <filesystem>

ConfigManager::ConfigManager()
{

}

ConfigManager::~ConfigManager()
{

}

std::string ConfigManager::GetExecutePath() const
{
	char const* envRoot = getenv("ASSIMP");
	std::string path = "";
	if (envRoot != nullptr)
		path = std::string(envRoot) + "/../../../Bin";
	else
		path = std::filesystem::current_path().generic_string();
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
	std::string editorPath = GetEditorPath();
	std::string path = editorPath + "/Script";
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




