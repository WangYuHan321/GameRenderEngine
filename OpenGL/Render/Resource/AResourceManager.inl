#include "AResourceManager.h"

template<typename T>
std::string AResourceManager<T>::__ENGINE_ASSET_PATH = "Data\\Engine\\";

template<typename T>
T* AResourceManager<T>::LoadResource(const std::string& p_path)
{
	if (auto resource = GetResource(p_path); resource)
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
	if (m_resources.find(SID(p_path)) != m_resources.end())
	{
		return m_resources[SID(p_path)];
	}
	return nullptr;
}

//now have no default resource this call nullptr
template<typename T>
T* AResourceManager<T>::GetDefaultResource(const std::string& p_path)
{
	if (m_resources.size() != 0)
		m_resources[SID(p_path)] = m_resources[0];
	else
		m_resources[SID(p_path)] = nullptr;
	return m_resources[SID(p_path)];
}

template<typename T>
void AResourceManager<T>::SetNewResource(const std::string& p_path, T* value)
{
	m_resources[SID(p_path)] = value;
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

