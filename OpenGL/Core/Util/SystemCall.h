#pragma once

#include "../../Util/common.h"

class SystemCall
{
public:
	SystemCall() = default;

	static void ShowInExplorer(const std::string& p_path);

	static void ShowSaveFileDialog(const std::string& p_path);

	static void ShowOpenFileDialog(const std::string& p_path);
};

