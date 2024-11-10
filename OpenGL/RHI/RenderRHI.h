#pragma once

class RenderCommand;
class CommandBuffer;


class RenderRHI
{

public:
	RenderRHI();
	~RenderRHI();

	virtual void PushCommandBuffer(RenderCommand* renderCommand);
	virtual void RenderPushedBuffer();




private:
	CommandBuffer* m_pCommandBuffer;

};

