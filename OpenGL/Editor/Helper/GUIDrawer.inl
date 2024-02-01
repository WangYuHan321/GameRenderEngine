#include "GUIDrawer.h"

template<typename T>
inline void GUIDrawer::DrawScalar(WidgetContainer& p_root, const std::string& p_name, T& p_data, float p_step, T p_min, T p_max)
{

}

template<typename T>
inline void GUIDrawer::DrawScalar(WidgetContainer& p_root, const std::string& p_name, std::function<T(void)> p_gatherer, std::function<void(T)> p_provider, float p_step, T p_min, T p_max)
{

}