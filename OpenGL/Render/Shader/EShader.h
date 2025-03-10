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
    void SetMatrix(std::string location, glm::mat2 value);
    void SetMatrix(std::string location, glm::mat3 value);
    void SetMatrix(std::string location, glm::mat4 value);
    void SetIntArray(std::string location, const std::vector<int32>& values);
    void SetFloatArray(std::string location, const std::vector<float>& values);
    void SetVectorArray(std::string location, const std::vector<Vector2>& values);
    void SetVectorArray(std::string location, const std::vector<Vector3>& values);
    void SetVectorArray(std::string location, const std::vector<Vector4>& values);
    void SetMatrixArray(std::string location, const std::vector<Matrix2>& values);
    void SetMatrixArray(std::string location, const std::vector<Matrix3>& values);
    void SetMatrixArray(std::string location, const std::vector<Matrix4>& values);

    int GetInt(std::string location);
    float GetFloat(std::string location);
    Vector2 GetVector2(std::string location);
    Vector3 GetVector3(std::string location);
    Vector4 GetVector4(std::string location);
    Matrix2 GetMatrix2(std::string location);
    Matrix3 GetMatrix3(std::string location);
    Matrix4 GetMatrix4(std::string location);

    int GetUniformLocation(std::string name);

    SHADER_TYPE GetShaderType(std::string name);
    std::string GetShaderPath();

    static bool IsEngineUBOMember(const std::string& p_uniformName);
    static bool IsEngineShadowMember(const std::string& p_uniformName);

    std::vector<Uniform> GetUniforms() { return Uniforms; }
    std::vector<VertexAttr> GetVertexAttr() { return VertexAttrs; }

	uint32 GetShaderID();
};
