#pragma once

#include "../../Util/common.h"

class ShaderStorageBuffer
{
public:

	ShaderStorageBuffer(GLenum accessType);

	~ShaderStorageBuffer();

	void Bind(uint32 bindingPoint);
	void Unbind();

	template<class T>
	void SetSubData(T* p_data, size_t p_size);

private:
	uint32 m_ssbo;
	uint32 m_curBindPoint;
};

#include "ShaderStorageBuffer.inl"

