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

void Material::Bind()
{
    if (m_Shader)
    {
        m_Shader->activeShader();

        for (auto& [name, value]: m_uniforms)
        {
            switch (value.Type)
            {
            case SHADER_TYPE::SHADER_BOOL: m_Shader->SetBool(name, value.BOOL); break;
            case SHADER_TYPE::SHADER_FLOAT:m_Shader->SetFloat(name, value.FLOAT); break;
            case SHADER_TYPE::SHADER_INT:m_Shader->SetInt(name, value.INT); break;
            case SHADER_TYPE::SHADER_VEC2:m_Shader->SetVector(name, value.VEC2); break;
            case SHADER_TYPE::SHADER_VEC3:m_Shader->SetVector(name, value.VEC3); break;
            case SHADER_TYPE::SHADER_VEC4:m_Shader->SetVector(name, value.VEC4); break;
            case SHADER_TYPE::SHADER_MAT2:m_Shader->SetMatrix(name, value.MAT2); break;
            case SHADER_TYPE::SHADER_MAT3:m_Shader->SetMatrix(name, value.MAT3); break;
            case SHADER_TYPE::SHADER_MAT4:m_Shader->SetMatrix(name, value.MAT4); break;
            }
        }

        int textureSlot = 0;
        for (auto& [name, value] : m_uniformSampler)
        {
            switch (value.Type)
            {
            case SHADER_TYPE::SHADER_SAMPLER1D: { value.TEXTURE->Bind(textureSlot); m_Shader->SetInt(name, textureSlot++); break; }
            case SHADER_TYPE::SHADER_SAMPLER2D: { value.TEXTURE->Bind(textureSlot); m_Shader->SetInt(name, textureSlot++); break; }
            case SHADER_TYPE::SHADER_SAMPLER3D: { value.TEXTURE->Bind(textureSlot); m_Shader->SetInt(name, textureSlot++); break; }
            case SHADER_TYPE::SHADER_SAMPLERCUBE: { value.TEXTURE_CUBE->Bind(textureSlot); m_Shader->SetInt(name, textureSlot++); break; }
            }
        }


    }

    
}

void Material::UnBind()
{
    m_Shader->inactiveShader();
}

void Material::SetShader(CShader* pShader)
{
    m_Shader = pShader;
}

void Material::SetInt(std::string name, int value)
{
    m_uniforms[name].Type = SHADER_INT;
    m_uniforms[name].INT = value;
}

void Material::SetFloat(std::string name, float value)
{
    m_uniforms[name].Type = SHADER_FLOAT;
    m_uniforms[name].FLOAT = value;
}

void Material::SetVector(std::string name, glm::vec2 value)
{
    m_uniforms[name].Type = SHADER_VEC2;
    m_uniforms[name].VEC2 = value;
}

void Material::SetVector(std::string name, glm::vec3 value)
{
    m_uniforms[name].Type = SHADER_VEC3;
    m_uniforms[name].VEC3 = value;
}

void Material::SetVector(std::string name, glm::vec4 value)
{
    m_uniforms[name].Type = SHADER_VEC4;
    m_uniforms[name].VEC4 = value;
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

uint8_t Material::GenerateStateMask() const
{
    uint8_t result = 0;

    if (DepthWrite) result |= 0b0000'0001;
    if(ColorWrite) result |= 0b0000'0010;
    if(Blend) result |= 0b0000'0100;
    if(Cull) result |= 0b0000'1000;

    if (DepthTest) result |= 0b0001'0000;
    if (CullFace == GL_BACK) result |= 0b0010'0000;
    if (CullFace == GL_FRONT) result |= 0b0100'0000;

    return result;
}

std::map<string, UniformSampler>* Material::GetSamplerUniforms()
{
	return &m_uniformSampler;
}
