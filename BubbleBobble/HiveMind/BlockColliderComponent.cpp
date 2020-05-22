#include "Components.h"
#include "GameObject.h"
#include "Renderer.h"
HiveMind::BlockColliderComponent::BlockColliderComponent()
	:ColliderComponent()
{
}

HiveMind::BlockColliderComponent::BlockColliderComponent(const FPoint2& pos, const RectI& collisionArea)
	:ColliderComponent(pos,collisionArea)
{
}

HiveMind::BlockColliderComponent::~BlockColliderComponent()
{
}

bool HiveMind::BlockColliderComponent::IsColliding(const FPoint2& point)
{
	if (m_pGameObject->HasComponent<SpriteComponent>())
		m_CollisionArea = m_pGameObject->GetComponent<SpriteComponent>()->GetDest();
	if (point.x >= m_CollisionArea.x && point.x <= (m_CollisionArea.x + m_CollisionArea.w) && point.y >= m_CollisionArea.y && point.y <= (m_CollisionArea.y + m_CollisionArea.h))
		return true;
	return false;
}

void HiveMind::BlockColliderComponent::RayHitObstacle(const GameObject* objectsToCheck, const FPoint2& objPos)
{
}

void HiveMind::BlockColliderComponent::Update(const float& deltaTime)
{
}

void HiveMind::BlockColliderComponent::Render() const
{
	SDL_RenderDrawRect(Renderer::GetInstance().GetSDLRenderer(), &m_pGameObject->GetComponent<SpriteComponent>()->GetDest());
}
