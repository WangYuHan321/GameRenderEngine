#pragma once
#include "SceneNode.h"
#include "Scene.h"

class TextureCube;
class CShader;

class Background : public SceneNode
{
private:
	TextureCube* m_cubeMap;
	CShader* m_shader;
public:
	Background();
	~Background();

	void SetCubeMap(TextureCube* cubeMap);

};

