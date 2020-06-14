#include "MortalComponent.h"
#include "ActorComponent.h"
HiveMind::MortalComponent::MortalComponent()
	:m_Lives{1}
{
}

HiveMind::MortalComponent::MortalComponent(const int& lives)
	: m_Lives{ lives }
{
}

HiveMind::MortalComponent::~MortalComponent()
{
}

void HiveMind::MortalComponent::Update(const float& elapsedSec)
{
	(elapsedSec);
	if (m_Lives <= 0)
		GetGameObject()->GetComponent<ActorComponent>()->Death();
}

void HiveMind::MortalComponent::Hit()
{
	m_Lives--;
}
