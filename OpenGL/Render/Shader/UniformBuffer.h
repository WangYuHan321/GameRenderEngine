#pragma once

#include "../../Util/common.h"

class UniformBuffer
{
public:
	UniformBuffer(size_t p_size, uint32 p_bindingPoint, uint32 p_offfset, GLenum type = GL_DYNAMIC_DRAW);
	~UniformBuffer();

	void Bind();
	void UnBind();

	template<typename T>
	void SetSubData(const T& p_data, size_t p_offset);

	void RefreshSubData(size_t p_size, uint32 p_offset, void* data);

	uint32 GetID();

private:
	uint32 m_ubo;

};

#include "UniformBuffer.inl"

