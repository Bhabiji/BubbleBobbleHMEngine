#include "Components.h"
#include "GameObject.h"
#include "Renderer.h"
HiveMind::BlockColliderComponent::BlockColliderComponent()
	:ColliderComponent()
	, m_CustomSize{false}

{
}
//writew init func for m_size 
HiveMind::BlockColliderComponent::BlockColliderComponent(const FPoint2& pos, const Float2& size)
	:ColliderComponent(pos,size)
	,m_CustomSize{true}
{
}

HiveMind::BlockColliderComponent::~BlockColliderComponent()
{
}

bool HiveMind::BlockColliderComponent::IsCollidingVertically(const FPoint2& point)
{

	if (point.x >= m_Pos.x && point.x <= (m_Pos.x + m_Size.x) && point.y >= m_Pos.y && point.y <= m_Pos.y + 4)
		return true;
	return false;
}

bool HiveMind::BlockColliderComponent::IsCollidingHorizontally(const FPoint2& point)
{
	
	if (point.x >= m_Pos.x && point.x <= (m_Pos.x + m_Size.x) && point.y >= m_Pos.y && point.y <= m_Pos.y + m_Size.y)
		return true;
	return false;
}


void HiveMind::BlockColliderComponent::RayHitObstacle(const GameObject* objectsToCheck, const FPoint2& objPos)
{
	(objectsToCheck);
	(objPos);
}

void HiveMind::BlockColliderComponent::Initialize()
{

	m_IsInitialized = true;
	if (!m_CustomSize)
	{
		if (m_pGameObject->HasComponent<SpriteComponent>())
			m_Size = Float2{ m_pGameObject->GetComponent<SpriteComponent>()->GetDest().w, m_pGameObject->GetComponent<SpriteComponent>()->GetDest().h };
	}
}

void HiveMind::BlockColliderComponent::Update(const float& elapsedSec)
{
	(elapsedSec);
	m_Pos = GetGameObject()->GetTransform()->GetPosition();
}

void HiveMind::BlockColliderComponent::Render() const
{
	const SDL_Rect rect{ int(m_Pos.x),  int(m_Pos.y),  int(m_Size.x), int(m_Size.y) };
	SDL_RenderDrawRect(Renderer::GetInstance().GetSDLRenderer(), &rect );
}
