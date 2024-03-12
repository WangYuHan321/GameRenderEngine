#include "ShaderStorageBuffer.h"
ShaderStorageBuffer::ShaderStorageBuffer(GLenum accessType)
{
	glGenBuffers(1, &m_ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, 0, nullptr, accessType);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_ssbo);
}

ShaderStorageBuffer::~ShaderStorageBuffer()
{
	glDeleteBuffers(1, &m_ssbo);
}

void ShaderStorageBuffer::Bind(uint32 bindingPoint)
{
	m_curBindPoint = bindingPoint;
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, m_curBindPoint, m_ssbo);
}

void ShaderStorageBuffer::Unbind()
{
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, m_curBindPoint, 0);
}