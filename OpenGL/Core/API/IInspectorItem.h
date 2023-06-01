#pragma once
#include "ISerializable.h"
#include "../../UI/Internel/WidgetContainer.h"
class IInspectorItem :
    public ISerializable
{
public:
    virtual void OnInspector(WidgetContainer& p_root) = 0;
};

