#include "ColliderComponent.h"
#include "Components.h"
#include "GameObject.h"

HiveMind::ColliderComponent::ColliderComponent()
	:m_Pos{}
	, m_CollisionArea{}
{
	
}

HiveMind::ColliderComponent::ColliderComponent(const FPoint2& pos, const RectI& collisionArea)
	:m_Pos{pos}
	,m_CollisionArea{collisionArea}
{
}

HiveMind::ColliderComponent::~ColliderComponent()
{
}


void HiveMind::ColliderComponent::Initialize()
{
	m_IsInitialized = true;
}
