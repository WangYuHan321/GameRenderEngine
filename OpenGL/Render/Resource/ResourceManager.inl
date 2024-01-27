#include "ResourceManager.h"

template<typename T>
std::string AResourceManager<T>::__ENGINE_ASSET_PATH = "Data\\Engine\\";

template<typename T>
T* AResourceManager<T>::LoadResource(const std::string& p_path)
{
	if (auto resource = GetResource(p_path, false); resource)
		return resource;
	else
	{
		auto newResource = CreateResource(p_path);
		if (newResource)
		{
			m_resources[SID(p_path)] = newResource;
			return newResource;
		}
		return nullptr;
	}

}

template<typename T>
T* AResourceManager<T>::GetResource(const std::string& p_path)
{
	if (m_resources.find(p_path))
	{
		return m_resources[p_path];
	}
	return nullptr;
}

template<typename T>
void AResourceManager<T>::UnloadResource(const std::string& p_path)
{
	DestroyResource(p_path);
	m_resources.erase(SID(p_path));
}

template<typename T>
T* AResourceManager<T>::operator[](const std::string& p_path)
{
	return LoadResource(p_path);
}

