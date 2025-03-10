#include "EShader.h"
#include"../../Util/common.h"
#include"../../Util/Utils.h"

extern string G_GetTextFromFile(string str);

//EShader::EShader(const string& vertexFile, const string& fragementFile, const string& geometryFile)
//{
//	if (m_ShaderProgram)
//		return;
//	m_ShaderProgram = glCreateProgram();
//	GLint ShaderVID, ShaderFID, ShaderGID;
//
//	if (vertexFile != "" && vertexFile.length() != 0)
//	{
//		string shaderSource;
//		ShaderVID = glCreateShader(GL_VERTEX_SHADER);
//		try {
//			std::ifstream streamV(vertexFile);
//			Assert(streamV.fail(), "Error ifstream");
//			std::stringstream strStreamV;
//			strStreamV << streamV.rdbuf();
//			shaderSource = strStreamV.str();
//			const char* pShaderSource = shaderSource.c_str();
//			glShaderSource(ShaderVID, 1, &pShaderSource, nullptr);
//			glAttachShader(m_ShaderProgram, ShaderVID);
//		}
//		catch(std::exception e){
//			
//		}
//	}
//
//	if (fragementFile != "" && fragementFile.length() != 0)
//	{
//		string shaderSource;
//		ShaderFID = glCreateShader(GL_FRAGMENT_SHADER);
//		try {
//			std::ifstream streamV(fragementFile);
//			Assert(streamV.fail(), "Error ifstream");
//			std::stringstream strStreamV;
//			strStreamV << streamV.rdbuf();
//			shaderSource = strStreamV.str();
//			const char* pShaderSource = shaderSource.c_str();
//			glShaderSource(ShaderFID, 1, &pShaderSource, nullptr);
//			glAttachShader(m_ShaderProgram, ShaderFID);
//		}
//		catch (std::exception e) {
//
//		}
//	}
//
//	if (geometryFile != "" && geometryFile.length() != 0)
//	{
//		string shaderSource;
//		ShaderGID = glCreateShader(GL_GEOMETRY_SHADER);
//		try {
//			std::ifstream streamV(geometryFile);
//			Assert(streamV.fail(), "Error ifstream");
//			std::stringstream strStreamV;
//			strStreamV << streamV.rdbuf();
//			shaderSource = strStreamV.str();
//			const char* pShaderSource = shaderSource.c_str();
//			glShaderSource(ShaderGID, 1, &pShaderSource, nullptr);
//			glAttachShader(m_ShaderProgram, ShaderGID);
//		}
//		catch (std::exception e) {
//
//		}
//	}
//	glLinkProgram(m_ShaderProgram);
//	
//	if (ShaderVID)
//		glDeleteShader(ShaderVID);
//	if (ShaderFID)
//		glDeleteShader(ShaderFID);
//	if (ShaderGID)
//		glDeleteShader(ShaderGID);
//
//
//}
//EShader::EShader(const string& computeFile)
//{
//	if (m_ShaderProgram)
//		return;
//	m_ShaderProgram = glCreateProgram();
//	GLint ShaderCID;
//	if (computeFile != "" && computeFile.length() != 0)
//	{
//		string shaderSource;
//		ShaderCID = glCreateShader(GL_COMPUTE_SHADER);
//		try {
//			std::ifstream streamV(computeFile);
//			Assert(streamV.fail(), "Error ifstream");
//			std::stringstream strStreamV;
//			strStreamV << streamV.rdbuf();
//			shaderSource = strStreamV.str();
//			const char* pShaderSource = shaderSource.c_str();
//			glShaderSource(ShaderCID, 1, &pShaderSource, nullptr);
//			glAttachShader(m_ShaderProgram, ShaderCID);
//		}
//		catch (std::exception e) {
//
//		}
//	}
//	glLinkProgram(m_ShaderProgram);
//	if (ShaderCID)
//		glDeleteShader(ShaderCID);
//}
//
//void EShader::actvieShader()
//{
//	glUseProgram(m_ShaderProgram);
//}

CShader::CShader()
{
	m_ID = 0;
	m_shaderPath = "";
}

//CShader::CShader(string name, string vsPath, string fsPath)
//{
//	m_shaderPath = name;
//	m_ID = glCreateProgram();
//	uint32 vsID, fsID;
//
//	string vsStr = G_GetTextFromFile(vsPath);
//	string fsStr = G_GetTextFromFile(fsPath);
//	const char* vsp = vsStr.c_str();
//	const char* fsp = fsStr.c_str();
//	glShaderSource(vsID, 1, &vsp, nullptr);
//	glShaderSource(fsID, 1, &fsp, nullptr);
//	glAttachShader(m_ID, vsID);
//	glAttachShader(m_ID, fsID);
//	glLinkProgram(m_ID);
//
//	glDeleteShader(vsID);
//	glDeleteShader(fsID);
//
//	// query the number of active uniforms and attributes
//	int nrAttributes, nrUniforms;
//	glGetProgramiv(m_ID, GL_ACTIVE_ATTRIBUTES, &nrAttributes);
//	glGetProgramiv(m_ID, GL_ACTIVE_UNIFORMS, &nrUniforms);
//	VertexAttrs.resize(nrAttributes);
//	Uniforms.resize(nrUniforms);
//
//	// iterate over all active attributes
//	char buffer[128];
//	for (unsigned int i = 0; i < nrAttributes; ++i)
//	{
//		GLenum glType;
//		glGetActiveAttrib(m_ID, i, sizeof(buffer), 0, (GLint*)&VertexAttrs[i].Size, &glType, buffer);
//		VertexAttrs[i].Name = std::string(buffer);
//		VertexAttrs[i].Type = SHADER_BOOL;
//
//		VertexAttrs[i].Location = glGetAttribLocation(m_ID, buffer);
//	}
//
//	// iterate over all active uniforms
//	for (unsigned int i = 0; i < nrUniforms; ++i)
//	{
//		GLenum glType;
//		glGetActiveUniform(m_ID, i, sizeof(buffer), 0, (GLint*)&Uniforms[i].Size, &glType, buffer);
//		Uniforms[i].Name = std::string(buffer);
//		Uniforms[i].Type = SHADER_BOOL;
//
//		Uniforms[i].Location = glGetUniformLocation(m_ID, buffer);
//	}
//
//}

SHADER_TYPE GetShaderTypeByGLType(GLenum type, bool isArray)
{
	SHADER_TYPE curType;
	switch (type)
	{
	case GL_BOOL:
		curType = SHADER_BOOL;
		break;
	case GL_INT:
		curType = isArray ? SHADER_INT_ARRAY : SHADER_INT;
		break;
	case GL_FLOAT:
		curType = isArray ? SHADER_FLOAT_ARRAY : SHADER_FLOAT;
		break;
	case GL_FLOAT_VEC2:
		curType = isArray ? SHADER_VEC2_ARRAY : SHADER_VEC2;
		break;
	case GL_FLOAT_VEC3:
		curType = isArray ? SHADER_VEC3_ARRAY : SHADER_VEC3;
		break;
	case GL_FLOAT_VEC4:
		curType = isArray ? SHADER_VEC4_ARRAY : SHADER_VEC4;
		break;
	case GL_FLOAT_MAT2:
		curType = isArray ? SHADER_MAT2_ARRAY : SHADER_MAT2;
		break;
	case GL_FLOAT_MAT3:
		curType = isArray ? SHADER_MAT3_ARRAY : SHADER_MAT3;
		break;
	case GL_FLOAT_MAT4:
		curType = isArray ? SHADER_MAT4_ARRAY : SHADER_MAT4;
		break;
	case GL_SAMPLER_CUBE:
		curType = SHADER_SAMPLERCUBE;
		break;
	case GL_SAMPLER_1D:
		curType = SHADER_SAMPLER1D;
		break;
	case GL_SAMPLER_2D:
		curType = SHADER_SAMPLER2D;
		break;
	case GL_SAMPLER_3D:
		curType = SHADER_SAMPLER3D;
		break;
	case GL_INT_VEC2:
		curType = SHADER_IVEC2;
		break;
	case GL_INT_VEC3:
		curType = SHADER_IVEC3;
		break;
	case GL_INT_VEC4:
		curType = SHADER_IVEC4;
		break;

	}

	return curType;
}


CShader::CShader(string name, string vsPath, string fsPath, std::vector<std::string> defines)
{
	m_shaderPath = name;
	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	m_ID = glCreateProgram();
	int status;
	char log[1024];

	if (defines.size() > 0)
	{
		std::vector<std::string> vsMergedCode;
		std::vector<std::string> fsMergedCode;

		std::string firstLine = vsPath.substr(0, vsPath.find("\n"));
		if (firstLine.find("#version") != std::string::npos)
		{
			// strip shader code of first line and add to list of shader code strings.
			vsPath = vsPath.substr(vsPath.find("\n") + 1, vsPath.length() - 1);
			vsMergedCode.push_back(firstLine + "\n");
		}
		firstLine = fsPath.substr(0, fsPath.find("\n"));
		if (firstLine.find("#version") != std::string::npos)
		{
			// strip shader code of first line and add to list of shader code strings.
			fsPath = fsPath.substr(fsPath.find("\n") + 1, fsPath.length() - 1);
			fsMergedCode.push_back(firstLine + "\n");
		}
		// then add define statements to the shader string list.
		for (unsigned int i = 0; i < defines.size(); ++i)
		{
			std::string define = "#define " + defines[i] + "\n";
			vsMergedCode.push_back(define);
			fsMergedCode.push_back(define);
		}
		vsMergedCode.push_back(vsPath);
		fsMergedCode.push_back(fsPath);

		const char** vsStringsC = new const char* [vsMergedCode.size()];
		const char** fsStringsC = new const char* [fsMergedCode.size()];
		for (unsigned int i = 0; i < vsMergedCode.size(); ++i)
			vsStringsC[i] = vsMergedCode[i].c_str();
		for (unsigned int i = 0; i < fsMergedCode.size(); ++i)
			fsStringsC[i] = fsMergedCode[i].c_str();
		glShaderSource(vs, vsMergedCode.size(), vsStringsC, NULL);
		glShaderSource(fs, fsMergedCode.size(), fsStringsC, NULL);
		delete[] vsStringsC;
		delete[] fsStringsC;
	}
	else
	{
		const char* vsSourceC = vsPath.c_str();
		const char* fsSourceC = fsPath.c_str();
		glShaderSource(vs, 1, &vsSourceC, NULL);
		glShaderSource(fs, 1, &fsSourceC, NULL);
	}
	glCompileShader(vs);
	glCompileShader(fs);

	glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		glGetShaderInfoLog(vs, 1024, NULL, log);
		Log("Vertex shader compilation error at: " + name + "!\n" + std::string(log));
	}
	glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		glGetShaderInfoLog(fs, 1024, NULL, log);
		Log("Fragment shader compilation error at: " + name + "!\n" + std::string(log));
	}

	glAttachShader(m_ID, vs);
	glAttachShader(m_ID, fs);
	glLinkProgram(m_ID);

	glGetProgramiv(m_ID, GL_LINK_STATUS, &status);
	if (!status)
	{
		glGetProgramInfoLog(m_ID, 1024, NULL, log);
		Log("Shader program linking error: \n" + std::string(log));
	}

	glDeleteShader(vs);
	glDeleteShader(fs);

	// query the number of active uniforms and attributes
	int nrAttributes, nrUniforms;
	glGetProgramiv(m_ID, GL_ACTIVE_ATTRIBUTES, &nrAttributes);
	glGetProgramiv(m_ID, GL_ACTIVE_UNIFORMS, &nrUniforms);
	VertexAttrs.resize(nrAttributes);
	Uniforms.resize(nrUniforms);

	// iterate over all active attributes
	char buffer[128];
	for (unsigned int i = 0; i < nrAttributes; ++i)
	{
		GLenum glType;
		glGetActiveAttrib(m_ID, i, sizeof(buffer), 0, (GLint*)&VertexAttrs[i].Size, &glType, buffer);
		VertexAttrs[i].Name = std::string(buffer);
		VertexAttrs[i].Type = GetShaderTypeByGLType(glType, Uniforms[i].Size != 1);

		VertexAttrs[i].Location = glGetAttribLocation(m_ID, buffer);
	}

	// iterate over all active uniforms
	for (unsigned int i = 0; i < nrUniforms; ++i)
	{
		GLenum glType;
		glGetActiveUniform(m_ID, i, sizeof(buffer), 0, (GLint*)&Uniforms[i].Size, &glType, buffer);
		Uniforms[i].Name = std::string(buffer);
		Uniforms[i].Type = GetShaderTypeByGLType(glType, Uniforms[i].Size != 1);

		Uniforms[i].Location = glGetUniformLocation(m_ID, buffer);
	}
}

CShader::CShader(string name, string cmPath)
{
	m_shaderPath = name;
	m_ID = glCreateProgram();

	string cmStr = G_GetTextFromFile(cmPath);
	const char* cmp = cmStr.c_str();
	GLint cmID;
	glShaderSource(cmID, 1, &cmp, nullptr);
	glAttachShader(m_ID, cmID);
	glLinkProgram(m_ID);

	glDeleteShader(cmID);

	// query the number of active uniforms and attributes
	int nrAttributes, nrUniforms;
	glGetProgramiv(m_ID, GL_ACTIVE_ATTRIBUTES, &nrAttributes);
	glGetProgramiv(m_ID, GL_ACTIVE_UNIFORMS, &nrUniforms);
	VertexAttrs.resize(nrAttributes);
	Uniforms.resize(nrUniforms);

	// iterate over all active attributes
	char buffer[128];
	for (unsigned int i = 0; i < nrAttributes; ++i)
	{
		GLenum glType;
		glGetActiveAttrib(m_ID, i, sizeof(buffer), 0, (GLint*)&VertexAttrs[i].Size, &glType, buffer);
		VertexAttrs[i].Name = std::string(buffer);
		VertexAttrs[i].Type = GetShaderTypeByGLType(glType, Uniforms[i].Size != 1);

		VertexAttrs[i].Location = glGetAttribLocation(m_ID, buffer);
	}

	// iterate over all active uniforms
	for (unsigned int i = 0; i < nrUniforms; ++i)
	{
		GLenum glType;
		glGetActiveUniform(m_ID, i, sizeof(buffer), 0, (GLint*)&Uniforms[i].Size, &glType, buffer);
		Uniforms[i].Name = std::string(buffer);
		Uniforms[i].Type = GetShaderTypeByGLType(glType, Uniforms[i].Size != 1);

		Uniforms[i].Location = glGetUniformLocation(m_ID, buffer);
	}
}

void CShader::CreateFromSource(string name, string vsSource, string fsSource)
{
	m_shaderPath = name;
	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	int status;
	char log[1024];
	m_ID = glCreateProgram();

	const char* vsSourceC = vsSource.c_str();
	const char* fsSourceC = fsSource.c_str();
	glShaderSource(vs, 1, &vsSourceC, NULL);
	glShaderSource(fs, 1, &fsSourceC, NULL);

	glCompileShader(vs);
	glCompileShader(fs);

	glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		glGetShaderInfoLog(vs, 1024, NULL, log);
		Log("Vertex shader compilation error at: " + name + "!\n" + std::string(log));
	}
	glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		glGetShaderInfoLog(fs, 1024, NULL, log);
		Log("Fragment shader compilation error at: " + name + "!\n" + std::string(log));
	}

	glAttachShader(m_ID, vs);
	glAttachShader(m_ID, fs);
	glLinkProgram(m_ID);

	glGetProgramiv(m_ID, GL_LINK_STATUS, &status);
	if (!status)
	{
		glGetProgramInfoLog(m_ID, 1024, NULL, log);
		Log("Shader program linking error: \n" + std::string(log));
	}

	glDeleteShader(vs);
	glDeleteShader(fs);

	// query the number of active uniforms and attributes
	int nrAttributes, nrUniforms;
	glGetProgramiv(m_ID, GL_ACTIVE_ATTRIBUTES, &nrAttributes);
	glGetProgramiv(m_ID, GL_ACTIVE_UNIFORMS, &nrUniforms);
	VertexAttrs.resize(nrAttributes);
	Uniforms.resize(nrUniforms);

	// iterate over all active attributes
	char buffer[128];
	for (unsigned int i = 0; i < nrAttributes; ++i)
	{
		GLenum glType;
		glGetActiveAttrib(m_ID, i, sizeof(buffer), 0, (GLint*)&VertexAttrs[i].Size, &glType, buffer);
		VertexAttrs[i].Name = std::string(buffer);
		VertexAttrs[i].Type = GetShaderTypeByGLType(glType, Uniforms[i].Size != 1);

		VertexAttrs[i].Location = glGetAttribLocation(m_ID, buffer);
	}

	// iterate over all active uniforms
	for (unsigned int i = 0; i < nrUniforms; ++i)
	{
		GLenum glType;
		glGetActiveUniform(m_ID, i, sizeof(buffer), 0, (GLint*)&Uniforms[i].Size, &glType, buffer);
		Uniforms[i].Name = std::string(buffer);
		Uniforms[i].Type = GetShaderTypeByGLType(glType, Uniforms[i].Size != 1);

		Uniforms[i].Location = glGetUniformLocation(m_ID, buffer);
	}
}

void CShader::ActiveShader()
{
	glUseProgram(m_ID);
}

void CShader::InActiveShader()
{
	glUseProgram(0);
}

void CShader::SetInt(std::string location, int value)
{
    int loc = GetUniformLocation(location);
    if (loc >= 0)
        glUniform1i(loc, value);
}

void CShader::SetBool(std::string location, bool value)
{
    int loc = GetUniformLocation(location);
    if (loc >= 0)
        glUniform1i(loc, (int)value);
}

void CShader::SetFloat(std::string location, float value)
{
    int loc = GetUniformLocation(location);
    if (loc >= 0)
        glUniform1f(loc, value);
}

void CShader::SetVector(std::string location, Vector2 value)
{
    int loc = GetUniformLocation(location);
    if (loc >= 0)
        glUniform2fv(loc, 1, &value[0]);
}

void CShader::SetVector(std::string location, Vector3 value)
{
    int loc = GetUniformLocation(location);
    if (loc >= 0)
        glUniform3fv(loc, 1, &value[0]);
}

void CShader::SetVector(std::string location, Vector4 value)
{
	int loc = GetUniformLocation(location);
	if (loc >= 0)
		glUniform4fv(loc, 1, &value[0]);
}

void CShader::SetVector(std::string location, IVector2  value)
{
	int loc = GetUniformLocation(location);
	if (loc >= 0)
		glUniform2iv(loc, 1, &value[0]);
}

void CShader::SetVector(std::string location, IVector3  value)
{
	int loc = GetUniformLocation(location);
	if (loc >= 0)
		glUniform3iv(loc, 1, &value[0]);
}

void CShader::SetVector(std::string location, IVector4  value)
{
	int loc = GetUniformLocation(location);
	if (loc >= 0)
		glUniform4iv(loc, 1, &value[0]);
}

void CShader::SetVector(std::string location, Color3 value)
{
	int loc = GetUniformLocation(location);
	Vector3 val(value.r, value.g, value.b);

	if (loc >= 0)
		glUniform3fv(loc, 1, &val[0]);
}

void CShader::SetVector(std::string location, Color4 value)
{
	int loc = GetUniformLocation(location);
	Vector4 val(value.r, value.g, value.b, value.a);

	if (loc >= 0)
		glUniform4fv(loc, 1, &val[0]);
}

void CShader::SetMatrix(std::string location, Matrix2 value)
{
    int loc = GetUniformLocation(location);
    if (loc >= 0)
        glUniformMatrix2fv(loc, 1, GL_FALSE, &value[0][0]);
}

void CShader::SetMatrix(std::string location, Matrix3 value)
{
    int loc = GetUniformLocation(location);
    if (loc >= 0)
        glUniformMatrix3fv(loc, 1, GL_FALSE, &value[0][0]);
}

void CShader::SetMatrix(std::string location, Matrix4 value)
{
    int loc = GetUniformLocation(location);
    if (loc >= 0)
        glUniformMatrix4fv(loc, 1, GL_FALSE, &value[0][0]);
}

void CShader::SetIntArray(std::string location, const std::vector<int32>& values)
{
	int loc = GetUniformLocation(location);
	if (loc >= 0)
		glUniform1iv(loc, values.size(), (int32*)&values[0]);
}

void CShader::SetFloatArray(std::string location, const std::vector<float>& values)
{
	int loc = GetUniformLocation(location);
	if (loc >= 0)
		glUniform1fv(loc, values.size(), (float*)&values[0]);
}
void CShader::SetVectorArray(std::string location, const std::vector<Vector2>& values)
{
	unsigned int loc = glGetUniformLocation(m_ID, location.c_str());
	if (loc >= 0)
	{
		glUniform2fv(loc, values.size(), (float*)(&values[0]));
	}
}
void CShader::SetVectorArray(std::string location, const std::vector<Vector3>& values)
{
	unsigned int loc = glGetUniformLocation(m_ID, location.c_str());
	if (loc >= 0)
	{
		glUniform3fv(loc, values.size(), (float*)(&values[0]));
	}
}

void CShader::SetVectorArray(std::string location, const std::vector<Vector4>& values)
{
	unsigned int loc = glGetUniformLocation(m_ID, location.c_str());
	if (loc >= 0)
	{
		glUniform4fv(loc, values.size(), (float*)(&values[0]));
	}
}

void CShader::SetMatrixArray(std::string location, const std::vector<glm::mat2>& values)
{
	unsigned int loc = glGetUniformLocation(m_ID, location.c_str());
	if (loc >= 0)
	{
		glUniformMatrix2fv(loc, values.size(), GL_FALSE, (float*)&values[0][0]);
	}
}

void CShader::SetMatrixArray(std::string location, const std::vector<glm::mat3>& values)
{
	unsigned int loc = glGetUniformLocation(m_ID, location.c_str());
	if (loc >= 0)
	{
		glUniformMatrix3fv(loc, values.size(), GL_FALSE, (float*)&values[0][0]);
	}
}

void CShader::SetMatrixArray(std::string location, const std::vector<glm::mat4>& values)
{
	unsigned int loc = glGetUniformLocation(m_ID, location.c_str());
	if (loc >= 0)
	{
		glUniformMatrix4fv(loc, values.size(), GL_FALSE, (float*)&values[0][0]);
	}
}

int CShader::GetInt(std::string location)
{
	int value;
	glGetUniformiv(m_ID, GetUniformLocation(location), &value);
	return value;
}

float CShader::GetFloat(std::string location)
{
	GLfloat value;
	glGetUniformfv(m_ID, GetUniformLocation(location), &value);
	return value;
}
glm::vec2 CShader::GetVector2(std::string location)
{
	GLfloat values[2];
	glGetUniformfv(m_ID, GetUniformLocation(location), values);
	return glm::vec2(values[0], values[1]);
}
glm::vec3 CShader::GetVector3(std::string location)
{
	GLfloat values[3];
	glGetUniformfv(m_ID, GetUniformLocation(location), values);
	return glm::vec3(values[0], values[1], values[2]);
}

glm::vec4 CShader::GetVector4(std::string location)
{
	GLfloat values[4];
	glGetUniformfv(m_ID, GetUniformLocation(location), values);
	return glm::vec4(values[0], values[1], values[2], values[3]);
}

glm::mat2 CShader::GetMatrix2(std::string location)
{
	GLfloat values[4];
	glGetUniformfv(m_ID, GetUniformLocation(location), values);
	return glm::mat2((float&)values);
}

glm::mat3 CShader::GetMatrix3(std::string location)
{
	GLfloat values[9];
	glGetUniformfv(m_ID, GetUniformLocation(location), values);
	return glm::mat3((float&)values);
}

glm::mat4 CShader::GetMatrix4(std::string location)
{
	GLfloat values[16];
	glGetUniformfv(m_ID, GetUniformLocation(location), values);
	return glm::mat4((float&)values);
}

int CShader::GetUniformLocation(std::string name)
{
	for (unsigned int i = 0; i < Uniforms.size(); ++i)
	{
		if (Uniforms[i].Name == name)
			return Uniforms[i].Location;
	}
	return -1;
}

SHADER_TYPE CShader::GetShaderType(std::string name)
{
	SHADER_TYPE shaderType = SHADER_NONE;

	for (auto it : Uniforms)
	{
		if (it.Name == name)
		{
			shaderType = it.Type;
		}
	}

	for (auto it : VertexAttrs)
	{
		if (it.Name == name)
		{
			shaderType = it.Type;
		}
	}

	return shaderType;
}

bool CShader::IsEngineUBOMember(const std::string& p_uniformName)
{
	return p_uniformName.rfind("ubo_", 0) == 0;
}

bool CShader::IsEngineShadowMember(const std::string& p_uniformName)
{
	return p_uniformName.rfind("shadow_", 0) == 0;
}

std::string CShader::GetShaderPath()
{
	return m_shaderPath;
}

uint32 CShader::GetShaderID()
{
	return m_ID;
}