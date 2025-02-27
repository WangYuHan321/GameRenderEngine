#include "ConfigManager.h"
#include <cstdlib>
#include <filesystem>

string PathConCatDirAndFile(string srcDir, string dstDir)
{
	std::filesystem::path srcPath = srcDir;
	std::filesystem::path dstPath = dstDir;
	std::string path = std::filesystem::absolute((srcPath / dstPath)).string();
	
	return path;
}

ConfigManager::ConfigManager()
{

}

ConfigManager::~ConfigManager()
{

}

std::string ConfigManager::GetExecutePath() const
{
	char const* envRoot = getenv("ASSIMP");
	string path = "";
	path = std::filesystem::current_path().generic_string();
	return path;
}

std::string ConfigManager::GetEnginePath() const
{
	std::string exePath = GetExecutePath();
	std::string path = PathConCatDirAndFile(exePath, "Data/Engine");
	return path;
}

std::string ConfigManager::GetEditorPath() const
{
	std::string exePath = GetExecutePath();
	std::string path = PathConCatDirAndFile(exePath, "Data/Editor");
	return path;
}

std::string ConfigManager::GetFontPath() const
{
	std::string enginePath = GetEnginePath();
	std::string path = PathConCatDirAndFile(enginePath, "Font");
	return path;
}

std::string ConfigManager::GetScriptPath() const
{
	std::string editorPath = GetEditorPath();
	std::string path = PathConCatDirAndFile(editorPath, "Script");
	return path;
}

std::string ConfigManager::GetXmlPath() const
{
	return PathConCatDirAndFile(GetEditorPath(), "Xml");
}

std::string ConfigManager::GetProjectPath() const
{
	return GetEditorPath();
}




