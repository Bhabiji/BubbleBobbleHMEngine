#include "HiveMindPCH.h"
#include "UIComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include <iomanip>
HiveMind::UIComponent::UIComponent()
	:m_NeedsUpdate{true}
{
}

void HiveMind::UIComponent::SetPreviousTime(const std::chrono::high_resolution_clock::time_point& now)
{
	m_PrevTime = now;
}

void HiveMind::UIComponent::SetCurrentTime(const std::chrono::high_resolution_clock::time_point& now)
{
	m_CurrTime = now;
}

void HiveMind::UIComponent::Initialize()
{
	
	m_IsInitialized = true;
	m_pGameObject->GetComponent<TextComponent>()->SetText("0");
}

void HiveMind::UIComponent::Update(const float& deltaTime)
{
	
	m_FPS = int(1000000 / deltaTime);
	m_pGameObject->GetComponent<TextComponent>()->SetText(std::to_string(m_FPS));

}

void HiveMind::UIComponent::Render() const
{
}
