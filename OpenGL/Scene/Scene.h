#include"../Util/common.h"
#include"../Util/Singleton.h"
#include"../../Core/API/ISerializable.h"

class SceneNode;
class Mesh;
class Material;
class Actor;

class Scene : public ISerializable
{
public:
	SceneNode* Root;
	uint32 CounterID = 0;

	Scene();
	~Scene();

	void Clear();

	Actor* CreateActor();

	Actor* CreateActor(const std::string& p_name, const std::string& p_tag = "");

	SceneNode* MakeSceneNode(Mesh mesh, Material material);

	SceneNode* MakeSceneNode(SceneNode* node);

	void DeleteSceneNode(SceneNode* node);

	Actor* FindActorByID(int64_t p_id);

	void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

	void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

private:
	int64_t m_availableID = 1;
	std::vector<Actor*> m_actors;
};

