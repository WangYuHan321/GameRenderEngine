#pragma once
#include "../API/IDrawable.h"
#include "../Plugin/Pluginable.h"
//#include "../Internel/WidgetContainer.h"
class WidgetContainer;

class AWidget : public IDrawable , public Pluginable
{
public:

	AWidget();

	virtual void Draw() override;

	void Destroy();

	void SetParent(WidgetContainer* p_container) { m_parent = p_container; }

	bool IsDestroyed() { return m_destroyed; }//WidgwetContainer

protected:

	virtual void _Draw_Impl() = 0;

public:

	bool enabled = true; //是否启用这个控件
	bool lineBreak = true;//在一行
	std::string m_widgetID = "?";
	bool m_autoExecutePlugins = true;

protected:
	WidgetContainer* m_parent;

private:

	static uint64_t _WIDGET_ID_INCREMENT;
	bool m_destroyed = false;

};