#include "../Util/common.h"
class CShader;
class RenderTarget;
class Texture;
class Renderer;

class PostProcess
{
public:
	//Texture* DownSampledHalfOutput;
	//Texture* DownSampledQuarterOutput;
	//Texture* DownSampledEightOutput;
	//Texture* DownSampledSixteenthOutput;
	//Texture* BlurredEightOutput;
	//Texture* BlurredSixteenOutput;
	Texture* SSAOOutput;
	Texture* BloomOutput1;
	Texture* BloomOutput2;
	Texture* BloomOutput3;
	Texture* BloomOutput4;

	CShader* m_ssaoShader;

	CShader* m_downSampleShader;

	CShader* m_bloomShader;

	CShader* m_onePassGaussianShader;

	CShader* m_postProcessShader;

	Renderer* m_renderer;

	bool SSAO = true;
	bool SSR = true;
	bool Bloom = true;
	bool MotionBlur = true;

	RenderTarget* m_ssaoRenderTarget;
	RenderTarget* m_bloomRenderTarget0;
	RenderTarget* m_bloomRenderTarget1;
	RenderTarget* m_bloomRenderTarget2;
	RenderTarget* m_bloomRenderTarget3;
	RenderTarget* m_bloomRenderTarget4;

	RenderTarget* m_gaussianRTHalf_H;
	RenderTarget* m_gaussianRTQuarter_H;
	RenderTarget* m_gaussianRTEight_H;
	RenderTarget* m_gaussianRTSixteenth_H;

	Texture* m_ssaoNoise;

	PostProcess(Renderer* render);
	~PostProcess();

	Texture* Blur(Texture* texture, RenderTarget* renderTarget, int count);

	void DebugDisplayTexture(Texture* source);

	void ProcessPreLighting();

	void ProcessPostLighting(RenderTarget* renderTarget);

	void Resize(uint32 width, uint32 height);

	void Blit(RenderTarget* renderTarget);
};
