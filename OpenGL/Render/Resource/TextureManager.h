#pragma once

#include "ResourceManager.h"
#include "../Shader/Texture.h"

class TextureManager : public AResourceManager<Texture>
{
public :
	virtual Texture* CreateResource(const std::string& p_path) override;

	virtual void DestroyResource(const std::string& p_path) override;

};

