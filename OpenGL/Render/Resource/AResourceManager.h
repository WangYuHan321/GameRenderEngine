#pragma once

#include <string>
#include <unordered_map>
#include "../../Event/Event.h"
#include "../../Util/common.h"

template<typename T>
class AResourceManager
{
public:
	virtual T* CreateResource(const std::string& p_path) = 0;

	virtual void DestroyResource(const std::string& p_path) = 0;

	T* operator[](const std::string& p_path);

	T* LoadResource(const std::string& p_path);

	void UnloadResource(const std::string& p_path);

	T* GetResource(const std::string& p_path);

	// for async load
	T* GetDefaultResource(const std::string& p_path);

	void SetNewResource(const std::string& p_path, T* value);

	Event<> m_resourceChangedEvent;

protected:
	static std::string __ENGINE_ASSET_PATH;

	std::unordered_map<uint32, T*> m_resources;
};

#include "AResourceManager.inl"

