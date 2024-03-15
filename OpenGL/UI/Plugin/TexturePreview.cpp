#include "TexturePreview.h"
#include "../../Global/ServiceLocator.h"
#include "../../Render/Resource/TextureManager.h"

void TexturePreview::SetPath(const std::string path)
{
	pTexture = GLOBALSERVICE(TextureManager)[path];
}

void TexturePreview::Execute()
{
	if (ImGui::IsItemHovered())
	{
		if (pTexture)
			image.textureID.ID = pTexture->ID;

		ImGui::BeginTooltip();
		image.Draw();
		ImGui::EndTooltip();
	}
}