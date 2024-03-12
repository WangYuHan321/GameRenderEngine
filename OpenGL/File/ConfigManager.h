#pragma once

#include"../Util/Singleton.h"
#include "../Util/common.h"

class ConfigManager : public CSingleton<ConfigManager>
{
private:
	string m_engineInIPath;

	uint32 m_Width;
	uint32 m_Height;
	bool m_isMax;
public:
	ConfigManager();
	~ConfigManager();

	std::string GetExecutePath() const;
	std::string GetEnginePath() const;
	std::string GetEditorPath() const;

};

