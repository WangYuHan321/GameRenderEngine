#pragma once

#include"../Shader/EShader.h"

enum MaterialType
{
	MATERIAL_DEFAULT,//defferd 
	MATERIAL_CUSTOM,//custom
	MATERIAL_POSTPROCESS,//postprocess
};

class Material
{

private:
	CShader* m_Shader;

	std::map<string, UniformValue> m_uniforms;
	std::map<string, UniformSampler> m_uniformSampler;

public:

	MaterialType Type = MATERIAL_CUSTOM;
	
	//
	bool DepthTest = true;
	bool DepthWrite = true;
	GLenum DepthCompare = GL_LESS;

	//
	bool Cull = true;
	GLenum CullFace = GL_BACK;
	GLenum CullWindingOrder = GL_CCW;

	//
	bool Blend = false;
	GLenum BlendSrc = GL_ONE;
	GLenum BlendDst = GL_ONE_MINUS_SRC_ALPHA;
	GLenum BlendEquation = GL_FUNC_ADD;

	//
	bool ShadowCast = true;
	bool ShadowReceive = true;

public:
	Material();
	Material(CShader* shader);

	Material Copy();
	CShader* GetShader();

	void SetFloat(std::string name, float value);
	void SetVector(std::string name, glm::vec3 value);
	void SetTexture(std::string name, Texture* value, unsigned int unit);
	void SetTextureCube(std::string name, TextureCube* value, unsigned int unit);

	std::map<string, UniformValue>* GetUniforms();
	std::map<string, UniformSampler>* GetSamplerUniforms();


};

