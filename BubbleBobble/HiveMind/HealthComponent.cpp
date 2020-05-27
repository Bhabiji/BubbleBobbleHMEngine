#include "HealthComponent.h"
#include "GameObject.h"
#include "Components.h"
HiveMind::HealthComponent::HealthComponent(const int health)
	:m_Health{health}
{
}

void HiveMind::HealthComponent::DecreaseHealth(const int decreaseVal)
{
	if (!m_IsInvincible)
	{
		m_Health -= decreaseVal;
		GetGameObject()->GetComponent<ActorComponent>()->Death();
	}
}

int HiveMind::HealthComponent::GetHealth() const
{
	return m_Health;
}

void HiveMind::HealthComponent::Update(const float& elapsedSec)
{
	if (GetGameObject()->HasComponent<HealthCounterComponent>())
	{
		GetGameObject()->GetComponent<HealthCounterComponent>()->SetCounter(m_Health);
	}
	
}

void HiveMind::HealthComponent::Render() const
{
}

void HiveMind::HealthComponent::Initialize()
{
}

void HiveMind::HealthComponent::SetInvincibility(const bool setInvincible)
{
	m_IsInvincible = setInvincible;
}
