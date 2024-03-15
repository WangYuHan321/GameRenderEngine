#pragma once

#include <string>
#include "IPlugin.h"
#include "../Visual/Image.h"
#include "../../Event/Event.h"
#include "../../Render/Shader/Texture.h"

class TexturePreview : public IPlugin
{
public:

	TexturePreview() : image(0, { 80, 80 })
	{}
	
	void SetPath(const std::string path);

	virtual void Execute() override;


	Texture* pTexture = nullptr;
	Image image;
};

