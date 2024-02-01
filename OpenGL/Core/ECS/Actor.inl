#include "Actor.h"

template<typename T, typename ... Args>
inline T& Actor::AddComponent(Args&& ... p_args)
{
	static_assert(std::is_base_of<AComponent, T>::value, "T should derive from AComponent");

	if (auto found = GetComponent<T>(); !found)//如果没有组件
	{
		m_components.insert(m_components.begin(), std::make_shared<T>(*this, p_args ...));
		T& instance = *dynamic_cast<T*>(m_components.front().get());
		ComponentAddedEvent.Invoke(instance);
		if (m_playing && IsActive())
		{
			reinterpret_cast<AComponent&>(instance).OnAwake();
			reinterpret_cast<AComponent&>(instance).OnEnable();
			reinterpret_cast<AComponent&>(instance).OnStart();
		}
		return instance;
	}
	else
	{
		return *found;
	}
}

template<typename T>
bool Actor::RemoveComponent(T& type)
{
	static_assert(std::is_base_of<AComponent, T>::value, "T should derive from AComponent");

	std::shared_ptr<T> result(nullptr);

	for (auto it = m_components.begin(); it != m_components.end(); ++it)
	{
		result = std::dynamic_pointer_cast<T>(*it);
		if (result)
		{
			ComponentRemovedEvent.Invoke(*result.get());
			m_components.erase(it);
			return true;
		}
	}
	return false;
}

template<typename T>
inline T* Actor::GetComponent()
{
	static_assert(std::is_base_of<AComponent, T>::value, "T should derive from AComponent");

	std::shared_ptr<T> result(nullptr);

	for (auto it = m_components.begin(); it != m_components.end(); ++it)
	{
		result = std::dynamic_pointer_cast<T>(*it);
		if (result)
		{
			return result.get();
		}
	}

	return nullptr;
}