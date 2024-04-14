#pragma once
#include "../Thread/Runable.h"
#include "../Util/common.h"

class ResourceChangeHandler;
struct FileChangeArgs;

class FileMonitor : public IRunable
{

public:
	FileMonitor();
	~FileMonitor();

	void SetDirectory(std::string directoryName);
	virtual void Run() override;

	void ResgisterHandler(ResourceChangeHandler* other);

	void NotifyHandler();

private:
	std::string m_directoryStr;

	std::vector<ResourceChangeHandler*> m_pOwnders;
	FileChangeArgs* m_pArg;

	char m_readBuffer[1024];

};

