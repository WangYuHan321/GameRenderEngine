#include "CPose.h"

CPose::CPose(Actor& p_actor):
	AComponent(p_actor),
	m_Animation(nullptr),
	m_Animator(nullptr),
	m_boneInfoMap{}
{
}