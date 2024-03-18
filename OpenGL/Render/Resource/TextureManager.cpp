#include "TextureManager.h"
#include "../../File/ConfigManager.h"
#include "Loader/TextureLoader.h"

Texture* TextureManager::CreateResource(const std::string& p_path)
{
	string realPath = ConfigManager::getInstance()->GetEditorPath() + "\\Texture\\" + p_path;
	Texture* pTexture = TextureLoader::getInstance()->LoadTexture(realPath, GL_TEXTURE_2D, GL_RGBA);
	return pTexture;
}


void TextureManager::DestroyResource(const std::string& p_path)
{

}