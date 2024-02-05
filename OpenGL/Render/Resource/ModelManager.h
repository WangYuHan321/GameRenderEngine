#include "AResourceManager.h"
#include "../Mesh/Model.h"

class ModelManager : public AResourceManager<Model>
{
public:
	virtual Model* CreateResource(const std::string& p_path) override;

	virtual void DestroyResource(const std::string& p_path) override;

};
