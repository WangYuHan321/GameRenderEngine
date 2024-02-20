#include "UniformBuffer.h"

template<typename T>
void UniformBuffer::SetSubData(const T& p_data, size_t p_offset)
{
	Bind();

	glBufferSubData(GL_UNIFORM_BUFFER, p_offset, sizeof(T), std::addressof(p_data));

	UnBind();
}