#pragma once

#include "../../Util/common.h"

class UniformBuffer
{

	UniformBuffer(size_t p_size, uint32 p_bindingPoint, uint32 p_offfset);
	~UniformBuffer();

	void Bind();
	void UnBind();

	void RefreshSubData(size_t p_size, uint32 p_offset, void* data);

	uint32 GetID();

private:
	uint32 m_ubo;

};

