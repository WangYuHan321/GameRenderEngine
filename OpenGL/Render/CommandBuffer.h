#include<vector>
#include<map>
#include<algorithm>
#include<GLM/glm.hpp>

class Mesh;
class Camera;
class Material;
class Renderer;
class RenderCommand;
class RenderTarget;

class CommandBuffer
{
private:
	Renderer* m_renderer;

	std::vector<RenderCommand> m_deferredRenderCommand;//延迟渲染
	std::vector<RenderCommand> m_alphaRenderCommand;//透明混合
	std::vector<RenderCommand> m_postProcessRenderCommand;//后处理
	std::map<RenderTarget*, std::vector<RenderCommand>> m_customRenderComamnd;//自定义

public:
	CommandBuffer(Renderer* render);
	void Push(Mesh* mesh, Material* material, glm::mat4 transform = glm::mat4(1.0f), glm::mat4 prevTransform = glm::mat4(1.0f),
		glm::vec3 boxMin = glm::vec3(-99999.0f), glm::vec3 boxMax = glm::vec3(99999.0f), RenderTarget * target = nullptr);

	void Push();
	void Clear();
	void Sort();

	std::vector<RenderCommand> GetDeferredRenderCommand(Camera& cam, bool isCull = false);
	std::vector<RenderCommand> GetAlphaRenderCommand();
	std::vector<RenderCommand> GetPostProcessRenderCommand();
	std::vector<RenderCommand> GetCustomRenderCommand(RenderTarget* target, Camera& cam, bool cull = false);
	std::vector<RenderCommand> GetShadowCastRenderCommands();
};