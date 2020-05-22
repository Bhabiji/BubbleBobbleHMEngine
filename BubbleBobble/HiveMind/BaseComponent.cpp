#include "HiveMindPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"
HiveMind::BaseComponent::BaseComponent()
	:m_pGameObject(nullptr)
{
}

HiveMind::BaseComponent::~BaseComponent()
{
}

HiveMind::TransformComponent* HiveMind::BaseComponent::GetTransform() const
{
	if (m_pGameObject)
		return m_pGameObject->GetTransform();
	else {
		return nullptr;
	}
}

bool HiveMind::BaseComponent::IsInitialized() const
{
	return m_IsInitialized;
}

