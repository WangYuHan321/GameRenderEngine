#include "LuaFileChangeHandler.h"
#include "Path/PathParser.h"


bool LuaFileChangeHandler::CheckFileType(const string& path)
{
	return EFileType::SCRIPT == PathParser::getInstance()->GetFileType(path);
}

bool LuaFileChangeHandler::OnFileChanged(const FileChangeArgs & arg)
{
	if (CheckFileType(arg.filePath))
	{
		LOG_INFO("path %s", arg.filePath);
		return true;
	}
	return false;
}