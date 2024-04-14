#pragma once

#include "ResourceChangeHandler.h"

class LuaFileChangeHandler : public ResourceChangeHandler
{
public:
	LuaFileChangeHandler() {}
	~LuaFileChangeHandler() {}

	virtual bool CheckFileType(const string& path) override;

	virtual bool OnFileChanged(const FileChangeArgs& arg) override;

};

