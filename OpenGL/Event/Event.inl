#include"Event.h"

template <class... ArgTypes>
listenerID Event<ArgTypes...>::AddListenerID(Callback callback)
{
	listenerID listenerID = m_activeIDCount++;
	m_callback.emplace(listenerID, callback);
	return listenerID;
}

template <class... ArgTypes>
listenerID Event<ArgTypes...>::operator +=(Callback callback)
{
	return AddListenerID(callback);
}

template <class... ArgTypes>
bool Event<ArgTypes...>::RemoveListenerID(listenerID listenerID)
{
	return m_callback.erase(listenerID);
}

template <class... ArgTypes>
bool Event<ArgTypes...>::operator -=(listenerID listenerID)
{
	return RemoveListenerID(listenerID);
}

template <class... ArgTypes>
void Event<ArgTypes...>::RemoveAllListeners()
{
	m_callback.clear();
}

template <class... ArgTypes>
listenerID Event<ArgTypes...>::GetListenerCount()
{
	return m_activeIDCount;
}

template <class... ArgTypes>
void Event<ArgTypes...>::Invoke(ArgTypes... arg)
{
	for (auto const& [key, value] : m_callback)
		value(arg...);
}