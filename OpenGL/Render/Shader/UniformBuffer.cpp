#include "UniformBuffer.h"


UniformBuffer::UniformBuffer(size_t p_size, uint32 p_bindingPoint, uint32 p_offset)
{
	glGenBuffers(1, &m_ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
	glBufferData(GL_UNIFORM_BUFFER, p_size, NULL, GL_STREAM_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferRange(GL_UNIFORM_BUFFER, p_bindingPoint, m_ubo, p_offset, p_size);
}


void UniformBuffer::Bind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
}

void UniformBuffer::UnBind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

UniformBuffer::~UniformBuffer() 
{
	glDeleteBuffers(1, &m_ubo);
}

void UniformBuffer::RefreshSubData(size_t p_size, uint32 p_offset, void* data)
{
	Bind();
	glBufferSubData(GL_UNIFORM_BUFFER, p_offset, p_size, data);
	UnBind();
}

uint32 UniformBuffer::GetID()
{
	return m_ubo;
}