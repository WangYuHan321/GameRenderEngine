#pragma once
#include <functional>
#include <unordered_map>
#include "../Util/common.h"
using listenerID = uint64_t;

template <class... ArgTypes>
class Event
{
public:
	using Callback = std::function<void(ArgTypes...)>;

	listenerID AddListenerID(Callback callback);

	listenerID operator +=(Callback callback);

	bool RemoveListenerID(listenerID listenerID);

	bool operator -=(listenerID listenerID);

	void RemoveAllListeners();

	listenerID GetListenerCount();

	void Invoke(ArgTypes... arg);

private:
	std::unordered_map<listenerID, Callback> m_callback;
	listenerID m_activeIDCount;
};

#include"Event.inl"