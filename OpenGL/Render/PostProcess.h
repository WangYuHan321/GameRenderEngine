
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
	//Texture* BloomOutput1;
	//Texture* BloomOutput2;
	//Texture* BloomOutput3;
	//Texture* BloomOutput4;

	CShader* m_ssaoShader;

	CShader* m_downSampleShader;

	Renderer* m_renderer;

	bool SSAO = true;
	bool Bloom = true;

	RenderTarget* m_ssaoRenderTarget;
	Texture* m_ssaoNoise;

	PostProcess(Renderer* render);
	~PostProcess();

	void DebugDisplayTexture(Texture* source);

	void ProcessPreLighting();

};
