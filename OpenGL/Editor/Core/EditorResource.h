#pragma once
#include <unordered_map>

class Texture;
class Model;
class CShader;

class EditorResource
{
public:
	EditorResource(const std::string& p_editorAssetPath);
	~EditorResource();

	Model* GetModel(const std::string& p_modelName);
	CShader* GetShader(const std::string& p_shaderName);
	Texture* GetTexture(const std::string& p_textureName);

private:
	std::unordered_map<std::string, Texture*> m_textures;
	std::unordered_map<std::string, Model*> m_models;
	std::unordered_map<std::string, CShader*> m_shaders;
};

