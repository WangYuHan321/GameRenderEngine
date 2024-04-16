#pragma once

#include "ResourceChangeHandler.h"

class ShaderFileChangeHandler : public ResourceChangeHandler
{
public:
	ShaderFileChangeHandler() {}
	~ShaderFileChangeHandler() {}

	virtual bool CheckFileType(const string& path) override;

	virtual bool OnFileChanged(const FileChangeArgs& arg) override;
};

