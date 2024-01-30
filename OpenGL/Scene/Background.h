#pragma once
#include "SceneNode.h"
#include "Scene.h"

class GlobalContext;
class TextureCube;
class CShader;

class Background : public SceneNode
{
private:
	TextureCube* m_cubeMap;
	CShader* m_shader;
	GlobalContext& m_context;
public:
	Background(GlobalContext& p_context);
	~Background();

	void SetCubeMap(TextureCube* cubeMap);

};

