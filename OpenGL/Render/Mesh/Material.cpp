#include "Material.h"

Material::Material()
{
    m_uniforms = std::map<string, UniformValue>();
    m_uniformSampler = std::map<string, UniformSampler>();
}

Material::Material(CShader* shader)
{
	m_Shader = shader;
}

Material Material::Copy()
{
    Material copy(m_Shader);

    copy.Type = this->Type;

    copy.DepthTest = this->DepthTest;
    copy.DepthWrite = this->DepthWrite;
    copy.DepthCompare = this->DepthCompare;

    copy.Cull = this->Cull;
    copy.CullFace = this->CullFace;
    copy.CullWindingOrder = this->CullWindingOrder;

    copy.Blend = this->Blend;
    copy.BlendSrc = this->BlendSrc;
    copy.BlendDst = this->BlendDst;
    copy.BlendEquation = this->BlendEquation;

    copy.m_uniforms = this->m_uniforms;
    copy.m_uniformSampler = this->m_uniformSampler;

    return copy;
}

std::map<string, UniformValue>* Material::GetUniforms()
{
	return &m_uniforms;
}

CShader* Material::GetShader()
{
    return m_Shader;
}

void Material::SetShader(CShader& pShader)
{
    m_Shader = &pShader;
}

void Material::SetFloat(std::string name, float value)
{
    m_uniforms[name].Type = SHADER_FLOAT;
    m_uniforms[name].FLOAT = value;
}

void Material::SetVector(std::string name, glm::vec3 value)
{
    m_uniforms[name].Type = SHADER_VEC3;
    m_uniforms[name].VEC3 = value;
}

void Material::SetTexture(std::string name, Texture* value, unsigned int unit)
{
    m_uniformSampler[name].ID = unit;
    m_uniformSampler[name].TEXTURE = value;

   switch (value->Target)
    {
    case GL_TEXTURE_1D:
        m_uniformSampler[name].Type = SHADER_SAMPLER1D;
        break;
    case GL_TEXTURE_2D:
        m_uniformSampler[name].Type = SHADER_SAMPLER2D;
        break;
    case GL_TEXTURE_3D:
        m_uniformSampler[name].Type = SHADER_SAMPLER3D;
        break;
    case GL_TEXTURE_CUBE_MAP:
        m_uniformSampler[name].Type = SHADER_SAMPLERCUBE;
        break;
    }

    if (m_Shader)
    {
        m_Shader->activeShader();
        m_Shader->SetInt(name, unit);
    }
}

void Material::SetTextureCube(std::string name, TextureCube* value, unsigned int unit)
{
    m_uniformSampler[name].ID = unit;
    m_uniformSampler[name].Type = SHADER_SAMPLERCUBE;
    m_uniformSampler[name].TEXTURE_CUBE = value;

    if (m_Shader)
    {
        m_Shader->activeShader();
        m_Shader->SetInt(name, unit);
    }
}

std::map<string, UniformSampler>* Material::GetSamplerUniforms()
{
	return &m_uniformSampler;
}
