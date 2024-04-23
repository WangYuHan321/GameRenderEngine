#include "LuaActorBinder.h"
#include "../ECS/Actor.h"

#include "../ECS/Components/Behaviour.h"
#include "../ECS/Components/CAmbientSphereLight.h"
#include "../ECS/Components/CCamera.h"
#include "../ECS/Components/CDirectionalLight.h"
#include "../ECS/Components/CLight.h"
#include "../ECS/Components/CMaterialRenderer.h"
#include "../ECS/Components/CModelRenderer.h"
#include "../ECS/Components/CTextMeshPro.h"
#include "../ECS/Components/CTransform.h"

void LuaActorBinder::BindActor(sol::state& p_luaState)
{

	p_luaState.new_usertype<Actor>("Actor",
		"GetName", &Actor::GetName,
		"IsActive", &Actor::IsActive,
		"GetTag", &Actor::GetTag,
		"GetID", &Actor::GetID,
		"GetParent", &Actor::GetParent,
		"DetachFromParent", &Actor::DetachFromParent,

		"GetTransform", &Actor::GetComponent<CTransform>,
		"GetCamera", &Actor::GetComponent<CCamera>,
		"GetLight", &Actor::GetComponent<CLight>,
		"GetDirectionalLight", &Actor::GetComponent<CDirectionalLight>,
		"GetAmbientSphereLight", &Actor::GetComponent<CAmbientSphereLight>,
		"GetModelRenderer", &Actor::GetComponent<CModelRenderer>,
		"GetMaterialRenderer", &Actor::GetComponent<CMaterialRenderer>,
		"GetTextMeshPro", &Actor::GetComponent<CTextMeshPro>,

		"AddTransform", &Actor::AddComponent<CTransform>,
		"AddCamera", &Actor::AddComponent<CCamera>,
		"AddLight", &Actor::AddComponent<CLight>,
		"AddDirectionalLight", &Actor::AddComponent<CDirectionalLight>,
		"AddAmbientSphereLight", &Actor::AddComponent<CAmbientSphereLight>,
		"AddModelRenderer", &Actor::AddComponent<CModelRenderer>,
		"AddMaterialRenderer", &Actor::AddComponent<CMaterialRenderer>,
		"AddTextMeshPro", &Actor::AddComponent<CTextMeshPro>,

		"RemoveTransform", &Actor::RemoveComponent<CTransform>,
		"RemoveCamera", &Actor::RemoveComponent<CCamera>,
		"RemoveLight", &Actor::RemoveComponent<CLight>,
		"RemoveDirectionalLight", &Actor::RemoveComponent<CDirectionalLight>,
		"RemoveAmbientSphereLight", &Actor::RemoveComponent<CAmbientSphereLight>,
		"RemoveModelRenderer", &Actor::RemoveComponent<CModelRenderer>,
		"RemoveMaterialRenderer", &Actor::RemoveComponent<CMaterialRenderer>,
		"RemoveTextMeshPro", &Actor::RemoveComponent<CTextMeshPro>
		
		);
}