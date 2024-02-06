#include"../Util/common.h"

class GLCache
{
private:

	//È«¾Ö×´Ì¬
	bool m_depthTest;
	bool m_blend;
	bool m_cullFace;

	GLenum m_depthFunc;
	GLenum m_BleandSrc = GL_ZERO;
	GLenum m_BlendDst = GL_ZERO;
	GLenum m_ForntFace;
	GLenum m_PolygonMode = GL_ZERO;

	uint32 m_actieveShaderID;

public:
	GLCache();
	~GLCache();


	void SetDepthTest(bool enable);
	void SetDepthFunction(GLenum depthFunc);
	void SetBlend(bool enbale);
	void SetBlendFunc(GLenum src, GLenum dst);
	void SetCull(bool enable);
	void SetCullFace(GLenum face);
	void SetPolyonMode(GLenum mode);
	void SetColorMask(bool enable);
	void SetDepthMask(bool enable);

	void SwitchShader(uint32 id);

};