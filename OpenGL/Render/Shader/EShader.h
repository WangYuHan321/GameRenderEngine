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


	void activeShader();
    void inactiveShader();

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
    void SetMatrixArray(std::string location, int size, glm::mat2* values);
    void SetMatrixArray(std::string location, int size, glm::mat3* values);
    void SetMatrixArray(std::string location, int size, glm::mat4* values);
    int getUniformLocation(std::string name);

	uint32 GetShaderID();
};
