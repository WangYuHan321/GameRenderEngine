#include "Material.h"
#include "../../Core/Helper/Serializer.h"

Material::Material()
{
    m_uniforms = std::map<string, UniformValue>();
    m_uniformSampler = std::map<string, UniformSampler>();
}

Material::Material(CShader* shader)
{
    SetShader(shader);
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
        m_Shader->ActiveShader();

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
    m_Shader->InActiveShader();
}

void Material::SetShader(CShader* pShader)
{
    m_Shader = pShader;

    for (auto item : pShader->GetUniforms())
    {
        if (pShader->IsEngineUBOMember(item.Name))
            continue;

        switch (item.Type)
        {
            case SHADER_BOOL:
            {
                UniformValue value;
                value.Type = SHADER_BOOL;
                value.BOOL = (bool)m_Shader->GetInt(item.Name);
                m_uniforms.emplace(item.Name, value);
                break;
            }

            case SHADER_INT:
            {
                UniformValue value;
                value.Type = SHADER_INT;
                value.INT = m_Shader->GetInt(item.Name);
                m_uniforms.emplace(item.Name, value);
                break;
            }

            case SHADER_FLOAT:
            {
                UniformValue value;
                value.Type = SHADER_FLOAT;
                value.FLOAT = m_Shader->GetFloat(item.Name);
                m_uniforms.emplace(item.Name, value);
                break;
            }

            case SHADER_VEC2:
            {
                UniformValue value;
                value.Type = SHADER_VEC2;
                value.VEC2 = m_Shader->GetVector2(item.Name);
                m_uniforms.emplace(item.Name, value);
                break;
            }

            case SHADER_VEC3:
            {
                UniformValue value;
                value.Type = SHADER_VEC3;
                value.VEC3 = m_Shader->GetVector3(item.Name);
                m_uniforms.emplace(item.Name, value);
                break;
            }

            case SHADER_VEC4:
            {
                UniformValue value;
                value.Type = SHADER_VEC4;
                value.VEC4 = m_Shader->GetVector4(item.Name);
                m_uniforms.emplace(item.Name, value);
                break;
            }

            case SHADER_MAT2:
            {
                UniformValue value;
                value.Type = SHADER_MAT2;
                value.MAT2 = m_Shader->GetMatrix2(item.Name);
                m_uniforms.emplace(item.Name, value);
                break;
            }

            case SHADER_MAT3:
            {
                UniformValue value;
                value.Type = SHADER_MAT3;
                value.MAT3 = m_Shader->GetMatrix3(item.Name);
                m_uniforms.emplace(item.Name, value);
                break;
            }

            case SHADER_MAT4:
            {
                UniformValue value;
                value.Type = SHADER_MAT4;
                value.MAT4 = m_Shader->GetMatrix4(item.Name);
                m_uniforms.emplace(item.Name, value);
                break;
            }

            case SHADER_SAMPLER2D:
            {
                UniformSampler value;
                value.Type = SHADER_SAMPLER2D;
                value.TEXTURE = nullptr;
                m_uniformSampler.emplace(item.Name, value);
                break;
            }

            case SHADER_SAMPLER3D:
            {
                UniformSampler value;
                value.Type = SHADER_SAMPLER3D;
                value.TEXTURE_CUBE = nullptr;
                m_uniformSampler.emplace(item.Name, value);
                break;
            }

        }
    }

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

void Material::SetBoolean(std::string name, bool value)
{
    m_uniforms[name].Type = SHADER_BOOL;
    m_uniforms[name].BOOL = value;
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
        m_Shader->ActiveShader();
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
        m_Shader->ActiveShader();
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

#ifdef USE_EDITOR

void Material::OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{
    Serializer::SerializeShader(p_doc, p_node, "Shader", m_Shader);

    tinyxml2::XMLNode* settingsNode = p_doc.NewElement("Settings");

    Serializer::SerializeBoolean(p_doc, settingsNode, "DepthTest", DepthTest);
    Serializer::SerializeBoolean(p_doc, settingsNode, "DepthWrite", DepthWrite);
    Serializer::SerializeUInt(p_doc, settingsNode, "DepthCompare", DepthCompare);

    Serializer::SerializeBoolean(p_doc, settingsNode, "Cull", Cull);
    Serializer::SerializeUInt(p_doc, settingsNode, "CullFace", CullFace);
    Serializer::SerializeUInt(p_doc, settingsNode, "CullWindingOrder", CullWindingOrder);

    Serializer::SerializeBoolean(p_doc, settingsNode, "Blend", Blend);
    Serializer::SerializeUInt(p_doc, settingsNode, "BlendSrc", BlendSrc);
    Serializer::SerializeUInt(p_doc, settingsNode, "BlendDst", BlendDst);
    Serializer::SerializeUInt(p_doc, settingsNode, "BlendEquation", BlendEquation);

    Serializer::SerializeBoolean(p_doc, settingsNode, "ColorWrite", ColorWrite);

    Serializer::SerializeBoolean(p_doc, settingsNode, "ShadowCast", ShadowCast);
    Serializer::SerializeBoolean(p_doc, settingsNode, "ShadowReceive", ShadowReceive);

    Serializer::SerializeUInt(p_doc, settingsNode, "GPUInstance", GPUInstance);

    tinyxml2::XMLNode* uniformsNode = p_doc.NewElement("uniforms");

    p_node->InsertEndChild(uniformsNode);



    for (auto& [name, value] : m_uniformSampler)
    {
        tinyxml2::XMLNode* uniform = p_doc.NewElement("uniform");
        uniformsNode->InsertEndChild(uniform);

        Serializer::SerializeString(p_doc, uniform, "name", name);
        switch (value.Type)
        {
        case SHADER_TYPE::SHADER_SAMPLER1D: break;
        case SHADER_TYPE::SHADER_SAMPLER2D: Serializer::SerializeTexture(p_doc, uniform, "value", value.TEXTURE); break;
        case SHADER_TYPE::SHADER_SAMPLER3D: break;
        case SHADER_TYPE::SHADER_SAMPLERCUBE: Serializer::SerializeTextureCube(p_doc, uniform, "value", value.TEXTURE_CUBE); break;
        }
    }

    for (auto& [name, value] : m_uniforms)
    {
        tinyxml2::XMLNode* uniform = p_doc.NewElement("uniform");
        uniformsNode->InsertEndChild(uniform);
        // Instead of p_node, use uniformNode (To create)

        Serializer::SerializeString(p_doc, uniform, "name", name);
        switch (value.Type)
        {
        case SHADER_TYPE::SHADER_BOOL:
            Serializer::SerializeBoolean(p_doc, uniform, "value", value.BOOL);
            break;

        case SHADER_TYPE::SHADER_INT:
            Serializer::SerializeUInt(p_doc, uniform, "value", value.INT);
            break;

        case SHADER_TYPE::SHADER_FLOAT:
            Serializer::SerializeFloat(p_doc, uniform, "value", value.FLOAT);
            break;

        case SHADER_TYPE::SHADER_VEC2:
            Serializer::SerializeVec2(p_doc, uniform, "value", value.VEC2);
            break;

        case SHADER_TYPE::SHADER_VEC3:
            Serializer::SerializeVec3(p_doc, uniform, "value", value.VEC3);
            break;

        case SHADER_TYPE::SHADER_VEC4:
            Serializer::SerializeVec4(p_doc, uniform, "value", value.VEC4);
            break;
        case SHADER_TYPE::SHADER_MAT2:
            //Serializer::Ser(p_doc, uniform, "value", value.MAT2);
            break;
        case SHADER_TYPE::SHADER_MAT3:
            //Serializer::SerializeVec4(p_doc, uniform, "value", value.VEC4);
            break;
        case SHADER_TYPE::SHADER_MAT4:
            //Serializer::SerializeVec4(p_doc, uniform, "value", value.VEC4);
            break;
        }
    }
}

void Material::OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{
    tinyxml2::XMLNode* settingsNode = p_node->FirstChildElement("Settings");

    if (settingsNode)
    {
        Serializer::DeserializeBoolean(p_doc, settingsNode, "DepthTest", DepthTest);
        Serializer::DeserializeBoolean(p_doc, settingsNode, "DepthWrite", DepthWrite);
        Serializer::DeserializeUInt(p_doc, settingsNode, "DepthCompare", DepthCompare);

        Serializer::DeserializeBoolean(p_doc, settingsNode, "Cull", Cull);
        Serializer::DeserializeUInt(p_doc, settingsNode, "CullFace", CullFace);
        Serializer::DeserializeUInt(p_doc, settingsNode, "CullWindingOrder", CullWindingOrder);

        Serializer::DeserializeBoolean(p_doc, settingsNode, "Blend", Blend);
        Serializer::DeserializeUInt(p_doc, settingsNode, "BlendSrc", BlendSrc);
        Serializer::DeserializeUInt(p_doc, settingsNode, "BlendDst", BlendDst);
        Serializer::DeserializeUInt(p_doc, settingsNode, "BlendEquation", BlendEquation);

        Serializer::DeserializeBoolean(p_doc, settingsNode, "ColorWrite", ColorWrite);

        Serializer::DeserializeBoolean(p_doc, settingsNode, "ShadowCast", ShadowCast);
        Serializer::DeserializeBoolean(p_doc, settingsNode, "ShadowReceive", ShadowReceive);

        Serializer::DeserializeUInt(p_doc, settingsNode, "GPUInstance", GPUInstance);
    }

    CShader* deserializedShader = Serializer::DeserializeShader(p_doc, p_node, "Shader");
    if (deserializedShader)
    {
        SetShader(deserializedShader);
        tinyxml2::XMLNode* uniformsNode = p_node->FirstChildElement("uniforms");


        if (uniformsNode)
        {
            for (auto uniform = uniformsNode->FirstChildElement("uniform"); uniform; uniform = uniform->NextSiblingElement("uniform"))
            {
                if (auto uniformNameElement = uniform->FirstChildElement("name"); uniformNameElement)
                {
                    const std::string uniformName = uniformNameElement->GetText();
                    if (m_Shader->GetShaderType(uniformName) != SHADER_NONE)
                    {
                        switch (m_Shader->GetShaderType(uniformName))
                        {
                        case SHADER_TYPE::SHADER_BOOL: m_uniforms[uniformName].BOOL = Serializer::DeserializeBoolean(p_doc, uniform, "value"); break;
                            case SHADER_TYPE::SHADER_FLOAT:m_uniforms[uniformName].FLOAT = Serializer::DeserializeFloat(p_doc, uniform, "value"); break;
                            case SHADER_TYPE::SHADER_VEC2:m_uniforms[uniformName].VEC2 = Serializer::DeserializeVec2(p_doc, uniform, "value"); break;
                            case SHADER_TYPE::SHADER_VEC3:m_uniforms[uniformName].VEC3 = Serializer::DeserializeVec3(p_doc, uniform, "value"); break;
                            case SHADER_TYPE::SHADER_VEC4:m_uniforms[uniformName].VEC4 = Serializer::DeserializeVec4(p_doc, uniform, "value"); break;
                            //case SHADER_TYPE::SHADER_MAT2:m_uniforms[uniformName].MAT2 = Serializer::DeserializeMat2(p_doc, uniform, "value"); break;
                            //case SHADER_TYPE::SHADER_MAT3:m_uniforms[uniformName].MAT3 = Serializer::DeserializeMat3(p_doc, uniform, "value"); break;
                            //case SHADER_TYPE::SHADER_MAT4:m_uniforms[uniformName].MAT4 = Serializer::DeserializeMat4(p_doc, uniform, "value"); break;
                            //case SHADER_TYPE::SHADER_SAMPLER1D:m_uniformSampler[uniformName] = Serializer::DeserializeSampler1D(p_doc, uniform, "value"); break;
                            case SHADER_TYPE::SHADER_SAMPLER2D:m_uniformSampler[uniformName].TEXTURE = Serializer::DeserializeTexture(p_doc, uniform, "value"); break;
                            //case SHADER_TYPE::SHADER_SAMPLER3D:m_uniformSampler[uniformName] = Serializer::DeserializeSampler3D(p_doc, uniform, "value"); break;
                            case SHADER_TYPE::SHADER_SAMPLERCUBE:m_uniformSampler[uniformName].TEXTURE_CUBE = Serializer::DeserializeTextureCube(p_doc, uniform, "value"); break;
                        }
                    }
                }
            }
        }

    }

}

#endif