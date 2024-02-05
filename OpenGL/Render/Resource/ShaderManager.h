#pragma once

#include "../Shader/EShader.h"
#include "AResourceManager.h"

class ShaderManager : public AResourceManager<CShader>
{
public:
	virtual CShader* CreateResource(const std::string& p_path) override;

	virtual void DestroyResource(const std::string& p_path) override;

};

