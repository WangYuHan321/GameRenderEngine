#pragma once

#include "../../Util/common.h"
#include"../Shader/EShader.h"
#include "../../Core/API/ISerializable.h"

enum MaterialType
{
	MATERIAL_DEFAULT,//defferd 
	MATERIAL_CUSTOM,//custom
	MATERIAL_POSTPROCESS,//postprocess
};

#ifdef USE_EDITOR
class Material : public ISerializable
{

private:
	CShader* m_Shader;

	std::map<string, UniformValue> m_uniforms;
	std::map<string, UniformSampler> m_uniformSampler;

public:

	std::string Path = "";

	MaterialType Type = MATERIAL_CUSTOM;

	//
	bool DepthTest = true;
	bool DepthWrite = true;
	GLenum DepthCompare = GL_LESS; // 513

	//
	bool Cull = true;
	GLenum CullFace = GL_BACK; // 1029
	GLenum CullWindingOrder = GL_CCW; // 2305

	//
	bool Blend = false;
	GLenum BlendSrc = GL_ONE; //1
	GLenum BlendDst = GL_ONE_MINUS_SRC_ALPHA;//771
	GLenum BlendEquation = GL_FUNC_ADD;//32774

	bool ColorWrite = true;

	//
	bool ShadowCast = true;
	bool ShadowReceive = true;

	uint32 GPUInstance = 1;

public:
	Material();
	Material(CShader* shader);

	Material Copy();
	CShader* GetShader();


	void Bind();
	void UnBind();

	void SetShader(CShader* p_Shader);
	void SetInt(std::string name, int value);
	void SetFloat(std::string name, float value);
	void SetBoolean(std::string name, bool value);
	void SetVector(std::string name, glm::vec2 value);
	void SetVector(std::string name, glm::vec3 value);
	void SetVector(std::string name, glm::vec4 value);
	void SetTexture(std::string name, Texture* value, unsigned int unit);
	void SetTextureCube(std::string name, TextureCube* value, unsigned int unit);
	
	uint8_t GenerateStateMask() const;

	std::map<string, UniformValue>* GetUniforms();
	std::map<string, UniformSampler>* GetSamplerUniforms();

public:
	void OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;
	virtual void OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;
};
#else
class Material
{

private:
	CShader* m_Shader;

	std::map<string, UniformValue> m_uniforms;
	std::map<string, UniformSampler> m_uniformSampler;

public:

	std::string Path = "";

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

	bool ColorWrite = true;

	//
	bool ShadowCast = true;
	bool ShadowReceive = true;

	uint32 GPUInstance = 1;

public:
	Material();
	Material(CShader* shader);

	Material Copy();
	CShader* GetShader();


	void Bind();
	void UnBind();

	void SetShader(CShader* p_Shader);
	void SetInt(std::string name, int value);
	void SetFloat(std::string name, float value);
	void SetBoolean(std::string name, bool value);
	void SetVector(std::string name, glm::vec2 value);
	void SetVector(std::string name, glm::vec3 value);
	void SetVector(std::string name, glm::vec4 value);
	void SetTexture(std::string name, Texture* value, unsigned int unit);
	void SetTextureCube(std::string name, TextureCube* value, unsigned int unit);

	uint8_t GenerateStateMask() const;

	std::map<string, UniformValue>* GetUniforms();
	std::map<string, UniformSampler>* GetSamplerUniforms();
};

#endif
