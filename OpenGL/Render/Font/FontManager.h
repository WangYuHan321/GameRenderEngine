#pragma once

#include "Font.h"
#include "../Shader/Texture.h"
#include "../Mesh/Material.h"
#include "../../Util/common.h"
#include "../../Core/ECS/Actor.h"

class Mesh;
class CShader;

class FontManager
{
public:
	FontManager();
	~FontManager();

	void Initialize();

	void CreateFontActor();
	void ModifyFontStr(Actor& p_actor);
	void LoadAllFontList();

protected:

	//FT_Library m_library;
	//std::map<std::string, Font*> m_fontList;

	Material m_fontMaterial;
	CShader* m_fontShader;
};

