#include"../Util/common.h"
#include"../Util/Singleton.h"

class SceneNode;
class Mesh;
class Material;

class Scene : public CSingleton<Scene>
{
public:
	SceneNode* Root;
	uint32 CounterID = 0;

	Scene();
	~Scene();

	void Clear();

	SceneNode* MakeSceneNode(Mesh mesh, Material material);

	SceneNode* MakeSceneNode(SceneNode* node);

	void DeleteSceneNode(SceneNode* node);

};

