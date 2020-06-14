#include "HiveMindPCH.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "Components.h"
HiveMind::TransformComponent::TransformComponent()
{
}

void HiveMind::TransformComponent::SetPosition(float x, float y, float z)
{
	m_Position = FPoint3(x,y,z);
}

void HiveMind::TransformComponent::SetPosition(const FPoint3& pos)
{
	m_Position = pos;
}

HiveMind::FPoint3 HiveMind::TransformComponent::GetPosition() const
{
	return m_Position;
}

void HiveMind::TransformComponent::Update(const float& elapsedSec)
{
	(elapsedSec);

	if (GetGameObject()->HasComponent<SpriteComponent>())
	{
		SpriteComponent* pSpriteComponent = GetGameObject()->GetComponent<SpriteComponent>();
		RectI objRect = pSpriteComponent->GetDest();
		if (objRect.x + objRect.w < 0)
			m_Position.x = 640 - 3;
		else if (objRect.x > 640)
			m_Position.x = 3;
		if (objRect.y + objRect.h < 0)
			m_Position.y = 480 - 2;
		else if (objRect.y > 480)
			m_Position.y = 2;
	}
}

void HiveMind::TransformComponent::Render() const
{

}

void HiveMind::TransformComponent::Initialize()
{
	m_IsInitialized = true;
}

