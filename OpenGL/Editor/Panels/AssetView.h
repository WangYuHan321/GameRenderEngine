#pragma once

#include <variant>
#include "AViewControllable.h"

class Model;
class Texture;
class Material;

class AssetView : public AViewControllable
{
public:
	using ViewableResource = std::variant<Model*, Texture*, Material*>;

	AssetView(
		const std::string& p_title,
		bool p_opened,
		const PanelWindowSetting& p_windowSettings
	);
	~AssetView();
	virtual void _Render_Impl() override;

	void SetResource(ViewableResource p_viewResource);
	ViewableResource GetResource() const;

private:
	ViewableResource m_resource;
};

