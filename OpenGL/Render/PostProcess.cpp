#include <random>
#include "PostProcess.h"
#include "Renderer.h"
#include "ShaderConfig.h"
#include "../Math/Math.h"
#include "../Camera/Camera.h"
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
        SSAOOutput = m_ssaoRenderTarget->GetColorTexture(0);

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

    {
        m_bloomRenderTarget0 = new RenderTarget(1, 1, GL_HALF_FLOAT, 1, false);
        m_bloomRenderTarget1 = new RenderTarget(1, 1, GL_HALF_FLOAT, 1, false);
        m_bloomRenderTarget2 = new RenderTarget(1, 1, GL_HALF_FLOAT, 1, false);
        m_bloomRenderTarget3 = new RenderTarget(1, 1, GL_HALF_FLOAT, 1, false);
        m_bloomRenderTarget4 = new RenderTarget(1, 1, GL_HALF_FLOAT, 1, false);

        m_bloomShader = ResourceManager::getInstance()->LoadShader("bloom",
            "Shader\\scene\\screen_quad.vs", "Shader\\post\\bloom.fs");
        m_bloomShader->activeShader();
        m_bloomShader->SetInt("HDRScene", 0);

        BloomOutput1 = m_bloomRenderTarget1->GetColorTexture(0);
        BloomOutput2 = m_bloomRenderTarget2->GetColorTexture(0);
        BloomOutput3 = m_bloomRenderTarget3->GetColorTexture(0);
        BloomOutput4 = m_bloomRenderTarget4->GetColorTexture(0);
    }

    //gaussian blur shader
    {
        m_gaussianRTHalf_H = new RenderTarget(1, 1, GL_HALF_FLOAT, 1, false);
        m_gaussianRTQuarter_H = new RenderTarget(1, 1, GL_HALF_FLOAT, 1, false);
        m_gaussianRTEight_H = new RenderTarget(1, 1, GL_HALF_FLOAT, 1, false);
        m_gaussianRTSixteenth_H = new RenderTarget(1, 1, GL_HALF_FLOAT, 1, false);

        m_onePassGaussianShader = ResourceManager::getInstance()->LoadShader("gaussian blur",
            "Shader\\scene\\screen_quad.vs", "Shader\\post\\blur_guassian.fs");
        m_onePassGaussianShader->activeShader();
        m_onePassGaussianShader->SetInt("TexSrc", 0);
    }

    {
        m_postProcessShader = ResourceManager::getInstance()->LoadShader("PostProcess",
            "Shader\\scene\\screen_quad.vs", "Shader\\post_processing.fs");
        m_postProcessShader->activeShader();
        m_postProcessShader->SetInt("TexSrc", 0);
        m_postProcessShader->SetInt("TexBloom1", 1);
        m_postProcessShader->SetInt("TexBloom2", 2);
        m_postProcessShader->SetInt("TexBloom3", 3);
        m_postProcessShader->SetInt("TexBloom4", 4);
        m_postProcessShader->SetInt("gMotion", 5);
    }
}

void PostProcess::ProcessPreLighting()
{
    if (SSAO)
    {
        m_renderer->m_gBuffer->GetColorTexture(0)->Bind(0);
        m_renderer->m_gBuffer->GetColorTexture(1)->Bind(1);
        m_ssaoNoise->Bind(2);

        m_ssaoShader->activeShader();
        m_ssaoShader->SetVector("renderSize", m_renderer->m_renderSize);
        m_ssaoShader->SetMatrix("projection", m_renderer->m_camera->Projection);
        m_ssaoShader->SetMatrix("view", m_renderer->m_camera->View);

        glBindFramebuffer(GL_FRAMEBUFFER, m_ssaoRenderTarget->ID);
        glViewport(0, 0, m_ssaoRenderTarget->Width, m_ssaoRenderTarget->Height);
        glClear(GL_COLOR_BUFFER_BIT);
        m_renderer->RenderMesh((Mesh*)m_renderer->m_quadNDC);
    }
}

void PostProcess::ProcessPostLighting(RenderTarget* renderTarget)
{
    if (Bloom)
    {
        m_bloomShader->activeShader();
        renderTarget->GetColorTexture(0)->Bind(0);
        glBindFramebuffer(GL_FRAMEBUFFER, m_bloomRenderTarget0->ID);
        glViewport(0, 0, m_bloomRenderTarget0->Width, m_bloomRenderTarget0->Height);
        glClear(GL_COLOR_BUFFER_BIT);
        m_bloomShader->activeShader();
        m_renderer->RenderMesh((Mesh*)m_renderer->m_quadNDC);

        Blur(m_bloomRenderTarget0->GetColorTexture(0), m_bloomRenderTarget1, 8);
        Blur(m_bloomRenderTarget1->GetColorTexture(0), m_bloomRenderTarget2, 8);
        Blur(m_bloomRenderTarget2->GetColorTexture(0), m_bloomRenderTarget3, 8);
        Blur(m_bloomRenderTarget3->GetColorTexture(0), m_bloomRenderTarget4, 8);
    }
}

PostProcess::~PostProcess()
{
    delete m_ssaoRenderTarget;
    
    delete m_bloomRenderTarget0;
    delete m_bloomRenderTarget1;
    delete m_bloomRenderTarget2;
    delete m_bloomRenderTarget3;
    delete m_bloomRenderTarget4;
   
    delete m_gaussianRTHalf_H;
    delete m_gaussianRTQuarter_H;
    delete m_gaussianRTEight_H;
    delete m_gaussianRTSixteenth_H;
}

void PostProcess::Resize(uint32 width, uint32 height)
{
    m_ssaoRenderTarget->Resize(width, height);

    m_bloomRenderTarget0->Resize(uint32(width*2), uint32(height * 2));
    m_bloomRenderTarget1->Resize(uint32(width * 2), uint32(height * 2));
    m_bloomRenderTarget2->Resize(uint32(width * 2), uint32(height * 2));
    m_bloomRenderTarget3->Resize(uint32(width * 2), uint32(height * 2));
    m_bloomRenderTarget4->Resize(uint32(width * 2), uint32(height * 2));

    m_gaussianRTHalf_H->Resize(uint32(width * 2), uint32(height * 2));
    m_gaussianRTQuarter_H->Resize(uint32(width * 2), uint32(height * 2));
    m_gaussianRTEight_H->Resize(uint32(width * 2), uint32(height * 2));
    m_gaussianRTSixteenth_H->Resize(uint32(width * 2), uint32(height * 2));
    
    //m_bloomRenderTarget0->Resize(uint32(width * 0.5f), uint32(height * 0.5f));
    //m_bloomRenderTarget1->Resize(uint32(width * 0.5f), uint32(height * 0.5f));
    //m_bloomRenderTarget2->Resize(uint32(width * 0.25f), uint32(height * 0.25f));
    //m_bloomRenderTarget3->Resize(uint32(width * 0.125f), uint32(height * 0.125f));
    //m_bloomRenderTarget4->Resize(uint32(width * 0.0675f), uint32(height * 0.0675f));
    //
    //m_gaussianRTHalf_H->Resize(uint32(width * 0.5f), uint32(height * 0.5f));
    //m_gaussianRTQuarter_H->Resize(uint32(width * 0.25f), uint32(height * 0.25f));
    //m_gaussianRTEight_H->Resize(uint32(width * 0.125f), uint32(height * 0.125f));
    //m_gaussianRTSixteenth_H->Resize(uint32(width * 0.0675f), uint32(height * 0.0675f));
}

Texture* PostProcess::Blur(Texture* texture, RenderTarget* renderTarget, int count)
{
    
    RenderTarget* rtHorizontal;
    RenderTarget* rtVertical;
    if (renderTarget->Width == m_gaussianRTHalf_H->Width)
    {
        rtHorizontal = m_gaussianRTHalf_H;
    }
    else if (renderTarget->Width == m_gaussianRTQuarter_H->Width)
    {
        rtHorizontal = m_gaussianRTQuarter_H;
    }
    else if (renderTarget->Width == m_gaussianRTEight_H->Width)
    {
        rtHorizontal = m_gaussianRTEight_H;
    }
    else
    {
        rtHorizontal = m_gaussianRTSixteenth_H;
    }

    rtVertical = renderTarget;

    glViewport(0, 0, renderTarget->Width, renderTarget->Height);

    bool horizontal = true;
    m_onePassGaussianShader->activeShader();
    for (int i = 0; i < count; ++i, horizontal = !horizontal)
    {
        m_onePassGaussianShader->SetBool("horizontal", horizontal);
        if (i == 0)
        {
            texture->Bind(0);
        }
        else if (horizontal)
        {
            rtVertical->GetColorTexture(0)->Bind(0);
        }
        else if (!horizontal)
        {
            rtHorizontal->GetColorTexture(0)->Bind(0);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, horizontal ? rtHorizontal->ID : rtVertical->ID);
        m_onePassGaussianShader->activeShader();
        m_renderer->RenderMesh((Mesh*)m_renderer->m_quadNDC);
    }

    // output resulting (blurred) texture
    return renderTarget->GetColorTexture(0);
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

void PostProcess::Blit(RenderTarget* renderTarget)
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, renderTarget->Width, renderTarget->Height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    renderTarget->GetColorTexture(0)->Bind(0);
    BloomOutput1->Bind(1);
    BloomOutput2->Bind(2);
    BloomOutput3->Bind(3);
    BloomOutput4->Bind(4);
    m_renderer->m_gBuffer->GetColorTexture(3)->Bind(5);

    m_postProcessShader->activeShader();
    m_postProcessShader->SetBool("SSAO", SSAO);
    m_postProcessShader->SetBool("Bloom", Bloom);

    m_postProcessShader->SetBool("MotionBlur", MotionBlur);
    m_postProcessShader->SetFloat("MotionScale", 0.2);
    m_postProcessShader->SetInt("MotionSamples", 8);

    m_postProcessShader->activeShader();
    m_renderer->RenderMesh((Mesh*)m_renderer->m_quadNDC);
}
