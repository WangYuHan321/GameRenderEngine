#pragma once
#include"ShaderType.h"
#include"../../Util/common.h"

//class EShader
//{
//public:
//	EShader(const string& vertexFile, const string& fragementFile, const string& geometryFile = "");
//	EShader(const string& computeFile);
//
//	void actvieShader();
//private:
//	GLint m_ShaderProgram = -1;
//};

class CShader 
{
private:
	string m_shaderPath;
	uint32 m_ID;

	std::vector<Uniform> Uniforms;
	std::vector<VertexAttr> VertexAttrs;

public:
	CShader();
    /*CShader(string name, string vsPath, string fsPath);*/
    CShader(string name, string vsPath, string fsPath, std::vector<std::string> defines = std::vector<std::string>());
    CShader(string name, string cmPath);
    void CreateFromSource(string name, string vsSource, string fsSource);


	void ActiveShader();
    void InActiveShader();

	void SetInt(std::string location, int value);
    void SetBool(std::string location, bool  value);
    void SetFloat(std::string location, float value);
    void SetVector(std::string location, glm::vec2  value);
    void SetVector(std::string location, glm::vec3  value);
    void SetVector(std::string location, Color3 value);
    void SetVector(std::string location, glm::vec4  value);
    void SetVector(std::string location, Color4 value);
    void SetVectorArray(std::string location, int size, const std::vector<glm::vec2>& values);
    void SetVectorArray(std::string location, int size, const std::vector<glm::vec3>& values);
    void SetVectorArray(std::string location, int size, const std::vector<glm::vec4>& values);
    void SetMatrix(std::string location, glm::mat2 value);
    void SetMatrix(std::string location, glm::mat3 value);
    void SetMatrix(std::string location, glm::mat4 value);

    int GetInt(std::string location);
    float GetFloat(std::string location);
    glm::vec2 GetVector2(std::string location);
    glm::vec3 GetVector3(std::string location);
    glm::vec4 GetVector4(std::string location);
    glm::mat2 GetMatrix2(std::string location);
    glm::mat3 GetMatrix3(std::string location);
    glm::mat4 GetMatrix4(std::string location);

    void SetMatrixArray(std::string location, int size, glm::mat2* values);
    void SetMatrixArray(std::string location, int size, glm::mat3* values);
    void SetMatrixArray(std::string location, int size, glm::mat4* values);
    int GetUniformLocation(std::string name);

    SHADER_TYPE GetShaderType(std::string name);
    std::string GetShaderPath();

    static bool IsEngineUBOMember(const std::string& p_uniformName);

    std::vector<Uniform> GetUniforms() { return Uniforms; }
    std::vector<VertexAttr> GetVertexAttr() { return VertexAttrs; }

	uint32 GetShaderID();
};
