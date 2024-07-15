#pragma once
#include "AComponent.h"
#include "../../Render/Animation/Bone.h"

class Animator;
class Animation;

class CPose :
    public AComponent
{

public:
    CPose(Actor& p_actor);


    void SetBoneMap(std::unordered_map<std::string, BoneInfo>& map) { m_boneInfoMap = map; }
    void SetAnimator(Animator* p_animator) { m_Animator = p_animator; }
    void SetAnimation(Animation* p_animation) { m_Animation = p_animation; }

private:

    std::unordered_map<std::string, BoneInfo> m_boneInfoMap;

    Animator* m_Animator;
    Animation* m_Animation;

};

