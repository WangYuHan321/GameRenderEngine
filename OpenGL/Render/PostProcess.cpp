#include <random>
#include "PostProcess.h"
#include "Renderer.h"
#include "ShaderConfig.h"
#include "../Math/Math.h"
#include "../Render/RenderTarget.h"
#include "Resource/ResourceManager.h"

PostProcess::PostProcess(Renderer* render):
    m_renderer(render)
{
    {
        m_downSampleShader = ResourceManager::getInstance()->LoadShader("down sample",
            "Shader\\scene\\screen_quad.vs", "Shader\\scene\\screen_quad.fs");
        m_downSampleShader->activeShader();
        m_downSampleShader->SetInt("TexSrc", 0);
    }

    {
        m_ssaoRenderTarget = new RenderTarget(SSAO_WIDTH, SSAO_HEIGHT, GL_HALF_FLOAT, 1, false);

        m_ssaoShader = ResourceManager::getInstance()->LoadShader("ssao",
            "Shader\\ssao\\ssao.vs", "Shader\\ssao\\ssao.fs");
        m_ssaoShader->activeShader();
        m_ssaoShader->SetInt("gPositionMetallic", 0);
        m_ssaoShader->SetInt("gNormalRoughness", 1);
        m_ssaoShader->SetInt("texNoise", 2);
        
        //生成随机数
        std::uniform_real_distribution<float> randomsFloats(0.0f, 1.0f);
        std::default_random_engine generator;
        std::vector<glm::vec3> ssaoKernel;
        for (int i = 0; i < SSAOKernelSize; i++)
        {
            glm::vec3 sample(
                randomsFloats(generator) * 2.0f - 1.0f,
                randomsFloats(generator) * 2.0f - 1.0f,
                randomsFloats(generator)
            );
            sample = glm::normalize(sample);
            sample = sample * randomsFloats(generator);
            float scale = (float)i / (float)SSAOKernelSize;
            scale = lerp(0.1f, 1.0f, scale * scale);
            sample = sample * scale;
            ssaoKernel.push_back(sample);
        }
        std::vector<glm::vec3> ssaoNoise;
        for (unsigned int i = 0; i < 16; i++)
        {
            glm::vec3 noise(
                randomsFloats(generator) * 2.0 - 1.0,
                randomsFloats(generator) * 2.0 - 1.0,
                0.0f);
            ssaoNoise.push_back(noise);
        }

        m_ssaoNoise = new Texture();
        m_ssaoNoise->Generate(4, 4, GL_RGBA16F, GL_RGB, GL_HALF_FLOAT, &ssaoNoise[0]);

        m_ssaoShader->SetVectorArray("kernel", ssaoKernel.size(), ssaoKernel);
        m_ssaoShader->SetInt("sampleCount", SSAOKernelSize);
    }
}

void PostProcess::ProcessPreLighting()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_ssaoRenderTarget->ID);
    m_ssaoShader->activeShader();
    m_renderer->m_gBuffer->GetColorTexture(0)->Bind(0);
    m_renderer->m_gBuffer->GetColorTexture(1)->Bind(1);
    m_ssaoNoise->Bind(2);
    m_ssaoShader->SetVector("renderSize", m_renderer->m_renderSize);
    m_renderer->RenderMesh((Mesh*)m_renderer->m_quadNDC);
}

PostProcess::~PostProcess()
{
    delete m_ssaoRenderTarget;
}

void PostProcess::DebugDisplayTexture(Texture* src)
{
    //屏幕显示纹理
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, m_renderer->m_renderSize.x, m_renderer->m_renderSize.y);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    src->Bind(0);
    m_downSampleShader->activeShader();
    m_renderer->RenderMesh((Mesh*)m_renderer->m_quadNDC);
}
