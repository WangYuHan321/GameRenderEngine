#pragma once

#include "../../Util/Singleton.h"
#include <unordered_map>
#include <any>

#define GLOBALSERVICE(Type) ServiceLocator::getInstance()->Get<Type>()

class ServiceLocator : public CSingleton<ServiceLocator>
{
public:

	template<typename T>
	void Provide(T& p_service)
	{
		__SERVICES[typeid(T).hash_code()] = std::any(&p_service);
	}

	template <typename T>
	T& Get()
	{
		return *std::any_cast<T*>(__SERVICES[typeid(T).hash_code()]);
	}

private:
	 std::unordered_map<size_t, std::any> __SERVICES;
};

