#include"../Util/common.h"
#include"../Render/Shader/Texture.h"

class Renderer;

class RenderTarget
{
	friend Renderer;

public:
	uint32 ID;

	uint32 Width;
	uint32 Height;
	GLenum Type;

	bool hasDepthAndStenCil;

private:

	GLenum Target = GL_TEXTURE_2D;
	Texture m_depthStencil;
	std::vector<Texture> m_colorAttachments;

public:
	RenderTarget(uint32 width, uint32 height, GLenum type = GL_UNSIGNED_BYTE,
		uint32 attachemnts = 1, bool depthandstencil = false);
	
	Texture* GetColorTexture(unsigned int index);
	Texture* GetDepthStencilTexture();
	void Resize(uint32 width, uint32 height);

	void Bind();
	void Unbind();

	////深度测试必备函数
	//void SetFilterMin(GLenum filter);
	//void SetFilterMax(GLenum filter);
	//void SetWrapMode(GLenum depthModel);
};