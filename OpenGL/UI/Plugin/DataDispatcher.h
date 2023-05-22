#pragma once
#include <functional>
#include "IPlugin.h"

#define TRY_GATHER(type, output)	if (auto plugin = GetPlugin<DataDispatcher<type>>(); plugin) output = plugin->Gather();
#define TRY_PROVIDE(type, output)	if (auto plugin = GetPlugin<DataDispatcher<type>>(); plugin) plugin->Provide(output);
#define TRY_NOTIFY_CHANGE(type)		if (auto plugin = GetPlugin<DataDispatcher<type>>(); plugin) plugin->NotifyChange();

template<typename T>
class DataDispatcher :
    public IPlugin
{

public:

    //提供者 收集者 和 通知改变
    //收集负责 m_data = 提供新值
    //通知负责m_data是否改变
    //提供负责该 m_data
    void RegisterReference(T& p_reference)
    {
        m_dataPointer = &p_reference;
    }

    void RegisterProvider(std::function<void(T)> p_provider)
    {
        m_provider = p_provider;
    }

    void RegisterGatherer(std::function<T(void)> p_gatherer)
    {
        m_gatherer = p_gatherer;
    }

    void Provide(T p_data)
    {
        if (m_valueChanged)
        {
            if (m_dataPointer)
                *m_dataPointer = p_data;
            else
                m_provider(p_data);
            m_valueChanged = false;
        }
    }

    T Gather()
    {
        return m_dataPointer ? *m_dataPointer : m_gatherer();
    }

    void NotifyChange()
    {
        m_valueChanged = true;
    }

    virtual void Execute() override {}


private:
    bool m_valueChanged = false;
    T* m_dataPointer = nullptr;
    std::function<void(T)> m_provider;
    std::function<T(void)> m_gatherer;
};

