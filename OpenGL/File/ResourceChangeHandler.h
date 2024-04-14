#pragma once

#include "../../Util/common.h"

struct FileOperate
{
	enum Type
	{
		None,
		Added,
		Removed,
		Modified
	};
};


struct FileChangeArgs
{
	FileOperate::Type Operator;
	std::string filePath;
	bool operator == (const FileChangeArgs& r)
	{
		return Operator == FileChangeArgs::Operator;
	}
};

class ResourceChangeHandler
{
public:
	ResourceChangeHandler() {};
	~ResourceChangeHandler() {};


	virtual bool CheckFileType(const string& path) = 0;

	virtual bool OnFileChanged(const FileChangeArgs& arg) = 0;

};

