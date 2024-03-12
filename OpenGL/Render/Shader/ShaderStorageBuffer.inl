#include "ShaderStorageBuffer.h"

template <class T>
void ShaderStorageBuffer::SetSubData(T* p_data, size_t p_size)
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, p_size, p_data, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}