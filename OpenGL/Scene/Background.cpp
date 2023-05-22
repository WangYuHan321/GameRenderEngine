#include "Background.h"
#include "../Render/Mesh/Cube.h"
#include "../Render/Mesh/Material.h"
#include "../Render/Resource/ResourceManager.h"


Background::Background() : SceneNode(Scene::getInstance()->CounterID++)
{
	Scene::getInstance()->Root->AddChild(this);

    m_shader = ResourceManager::getInstance()->LoadShader("background",
        "Shader\\background.vs", "Shader\\background.fs");
    Material = ResourceManager::getInstance()->LoadMaterial("background", m_shader);
    Mesh = new Cube;
    m_BoxMin = glm::vec3(-99999.0);
    m_BoxMax = glm::vec3(99999.0);

    Material->SetFloat("Exposure", 1.0f);
    Material->DepthCompare = GL_LEQUAL;
    Material->Cull = false;
    Material->ShadowCast = false;
    Material->ShadowReceive = false;
}

Background::~Background()
{

}

void Background::SetCubeMap(TextureCube* cubeMap)
{
    m_cubeMap = cubeMap;
    Material->SetTextureCube("background", m_cubeMap, 0);
}