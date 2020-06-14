#include "ColliderComponent.h"
#include "Components.h"
#include "GameObject.h"

HiveMind::ColliderComponent::ColliderComponent()
	:m_Pos{}
	, m_Size{}
{
	
}

HiveMind::ColliderComponent::ColliderComponent(const FPoint2& pos, const Float2& size)
	:m_Pos{pos}
	,m_Size{size}
{
}

HiveMind::ColliderComponent::~ColliderComponent()
{
}


void HiveMind::ColliderComponent::Initialize()
{
	m_IsInitialized = true;
}
