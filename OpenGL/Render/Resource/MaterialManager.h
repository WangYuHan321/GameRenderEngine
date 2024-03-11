#pragma once
#include "AResourceManager.h"
#include "../Mesh/Material.h"

class MaterialManager : public AResourceManager<Material>
{
public:
	virtual Material* CreateResource(const std::string& p_path) override;

	virtual void DestroyResource(const std::string& p_path) override;

};


