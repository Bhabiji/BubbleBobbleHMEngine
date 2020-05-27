#include "LifeTimeComponent.h"
#include "GameObject.h"
HiveMind::LifeTimeComponent::LifeTimeComponent(const float lifeTime, const bool isTimer)
	:m_MaxLifeTime{lifeTime}
	, m_LifeTime{}
	, m_IsTimer{isTimer}
{
}

HiveMind::LifeTimeComponent::~LifeTimeComponent()
{
}

bool HiveMind::LifeTimeComponent::IsActive() const
{
	return m_Active;
}

void HiveMind::LifeTimeComponent::ToggleActive(const bool toggle)
{
	m_Active = toggle;
}

void HiveMind::LifeTimeComponent::Initialize()
{
	m_IsInitialized = true;
	m_LifeTime = m_MaxLifeTime;
	m_Active = true;
}

void HiveMind::LifeTimeComponent::Update(const float& deltaTime)
{
	if (m_IsTimer)
	{
		m_LifeTime -= deltaTime;
		if (m_LifeTime <= 0)
		{
			GetGameObject()->SetActive(false);
		}
	}
}

void HiveMind::LifeTimeComponent::Render() const
{
}
