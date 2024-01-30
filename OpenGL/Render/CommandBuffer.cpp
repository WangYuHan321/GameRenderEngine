#include "CommandBuffer.h"
#include "RenderCommand.h"
#include "RenderTarget.h"
#include "Renderer.h"
#include "../Camera/Camera.h"
#include "Mesh/Material.h"

CommandBuffer::CommandBuffer(Renderer* render)
{
	m_renderer = render;
}

void CommandBuffer::Push(Mesh* mesh, Material* material, glm::mat4 transform, glm::mat4 prevTransform,
	glm::vec3 boxMin, glm::vec3 boxMax, RenderTarget* target)
{
	RenderCommand command = {};
	command.mesh = mesh;
	command.material = material;
	command.Transfrom = transform;
	command.prevTransform = prevTransform;
	command.BoxMin = boxMin;
	command.BoxMax = boxMax;

	if (material->Blend)
	{
		material->Type = MATERIAL_CUSTOM;
		m_alphaRenderCommand.push_back(command);
	}
	else
	{
		if (material->Type == MATERIAL_DEFAULT)
		{
			m_deferredRenderCommand.push_back(command);
		}
		else if (material->Type == MATERIAL_CUSTOM)
		{
			if (m_customRenderComamnd.find(target) != m_customRenderComamnd.end())
				m_customRenderComamnd[target].push_back(command);
			else
			{
				m_customRenderComamnd[target] = std::vector<RenderCommand>();
				m_customRenderComamnd[target].push_back(command);
			}
		}
		else if (material->Type == MATERIAL_POSTPROCESS)
		{
			m_postProcessRenderCommand.push_back(command);
		}
	}

}

void CommandBuffer::Clear()
{
	m_deferredRenderCommand.clear();
	m_customRenderComamnd.clear();
	m_postProcessRenderCommand.clear();
	m_alphaRenderCommand.clear();
}

bool RenderSortDeferred(const RenderCommand& a, const RenderCommand& b)
{
    return a.material->GetShader()->GetShaderID() < b.material->GetShader()->GetShaderID();
}

bool RenderSortCustom(const RenderCommand& a, const RenderCommand& b)
{
    return std::make_tuple(a.material->Blend, a.material->GetShader()->GetShaderID()) <
        std::make_tuple(b.material->Blend, b.material->GetShader()->GetShaderID());
}

void CommandBuffer::Sort()
{
	std::sort(m_deferredRenderCommand.begin(), m_deferredRenderCommand.end(), RenderSortDeferred);
	for (auto rtIt = m_customRenderComamnd.begin(); rtIt != m_customRenderComamnd.end(); rtIt++)
	{
		std::sort(rtIt->second.begin(), rtIt->second.end(), RenderSortCustom);
	}
}

std::vector<RenderCommand> CommandBuffer::GetDeferredRenderCommand(Camera& cam, bool isCull)
{
	if (isCull)
	{
		std::vector<RenderCommand> culledCommandBuffer;
		for (auto item : m_deferredRenderCommand)
		{
			if (cam.Frustum.Intersect(item.BoxMin, item.BoxMax))
			{
				culledCommandBuffer.push_back(item);
			}
		}
		return culledCommandBuffer;
	}
	else
		return m_deferredRenderCommand;
}

std::vector<RenderCommand> CommandBuffer::GetAlphaRenderCommand()
{
	return m_alphaRenderCommand;
}

std::vector<RenderCommand> CommandBuffer::GetPostProcessRenderCommand()
{
	return m_postProcessRenderCommand;
}

std::vector<RenderCommand> CommandBuffer::GetCustomRenderCommand(RenderTarget* target, Camera& cam, bool cull)
{
	// only cull when on main/null render target
	if (target == nullptr && cull)
	{
		std::vector<RenderCommand> commands;
		for (auto it = m_customRenderComamnd[target].begin(); it != m_customRenderComamnd[target].end(); ++it)
		{
			RenderCommand command = *it;
			if (cam.Frustum.Intersect(command.BoxMin, command.BoxMax)) {
				commands.push_back(command);
			}
		}
		return commands;
	}
	else
	{
		return m_customRenderComamnd[target];
	}
}

std::vector<RenderCommand> CommandBuffer::GetShadowCastRenderCommands()
{
	std::vector<RenderCommand> commands;
	for (auto it = m_deferredRenderCommand.begin(); it != m_deferredRenderCommand.end(); ++it)
	{
		if (it->material->ShadowCast)
		{
			commands.push_back(*it);
		}
	}
	for (auto it = m_customRenderComamnd[nullptr].begin(); it != m_customRenderComamnd[nullptr].end(); ++it)
	{
		if (it->material->ShadowCast)
		{
			commands.push_back(*it);
		}
	}
	return commands;
}