#include"../Util/common.h"

class Material;

class GLCache
{
private:

	//È«¾Ö×´Ì¬
	bool m_depthTest = true;
	bool m_blend = false;;
	bool m_cull = true;

	GLenum m_DepthFunc = GL_LESS;
	GLenum m_BleandSrc = GL_ZERO;
	GLenum m_BlendDst = GL_ZERO;
	GLenum m_CullFace = GL_BACK;
	GLenum m_ForntFace = GL_CCW;
	GLenum m_PolygonMode = GL_FILL;

	bool m_DepthWrite = true;
	bool m_ColorWrite = true;

	uint32 m_actieveShaderID;

public:
	GLCache();
	~GLCache();


	void SetDepthTest(bool enable);
	void SetDepthFunction(GLenum depthFunc);
	void SetBlend(bool enbale);
	void SetBlendFunc(GLenum src, GLenum dst);
	void SetCull(bool enable);
	void SetCullFront(GLenum face);
	void SetCullFace(GLenum face);
	void SetPolyonMode(GLenum mode);
	void SetColorMask(bool enable);
	void SetDepthMask(bool enable);

	void ApplyMaterial(Material& p_material);
	void SwitchShader(uint32 id);

};