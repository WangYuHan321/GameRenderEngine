#include "ShaderFileChangeHandler.h"
#include "Path/PathParser.h"

bool ShaderFileChangeHandler::CheckFileType(const string& path)
{
	return EFileType::SHADER == PathParser::getInstance()->GetFileType(path);
}

bool ShaderFileChangeHandler::OnFileChanged(const FileChangeArgs& arg)
{
	if (CheckFileType(arg.filePath))
	{
		LOG_INFO("path %s", arg.filePath);
		return true;
	}
	return false;
}