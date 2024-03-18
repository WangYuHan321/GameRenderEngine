#include"../Util/common.h"
#include"../Util/Singleton.h"
#include"../../Core/API/ISerializable.h"

class SceneNode;
class Mesh;
class Material;
class Actor;
class CCamera;
class CLight;
class AComponent;
class CModelRenderer;


class Scene : public ISerializable
{
	
	struct FastAccessComponents
	{
		std::vector<CModelRenderer*>	modelRenderers;
		std::vector<CCamera*>			cameras;
		std::vector<CLight*>			lights;
	};

public:
	SceneNode* Root;
	uint32 CounterID = 0;

	Scene();
	~Scene();

	void Clear();

	void Play();

	SceneNode* MakeSceneNode(Mesh mesh, Material material);

	SceneNode* MakeSceneNode(SceneNode* node);

	void DeleteSceneNode(SceneNode* node);

	Actor* CreateActor();

	Actor* CreateActor(const std::string& p_name, const std::string& p_tag = "");

	Actor* FindActorByID(int64_t p_id);

	CCamera* FindMainCCamera();

	const FastAccessComponents GetFastAccessComponents() const;

	std::vector<Actor*> GetActors()const ;

	void OnComponentAdded(AComponent& p_component);

	void OnComponentRemoved(AComponent& p_component);

	void OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

	void OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

private:
	int64_t m_availableID = 1;
	std::vector<Actor*> m_actors;
	bool m_isPlaying = false;
	FastAccessComponents m_fastAccessComponents;
};

