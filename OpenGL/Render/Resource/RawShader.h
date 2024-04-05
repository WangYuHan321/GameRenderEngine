#pragma once

#include<string>

class RawShader
{
public:
	static std::pair<std::string, std::string> GetGrid();

	static std::pair<std::string, std::string> GetGrizmo();

	static std::pair<std::string, std::string> GetBillboard();

	static std::pair<std::string, std::string> GetShadow();
};

