#include "CounterComponent.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Font.h"
#include "Renderer.h"


#include "Components.h"
HiveMind::CounterComponent::CounterComponent(Font* pFont, const int& initScore, const FPoint2& posOffset)
	:TextComponent(std::to_string(initScore),pFont)
	,m_Score{initScore}
{
}
HiveMind::CounterComponent::CounterComponent(Font* pFont, const int& initScore, const bool enableStaticPos, const FPoint2& staticPos)
	:TextComponent(std::to_string(initScore),pFont,enableStaticPos,staticPos)
	,m_Score{initScore}
{
}
HiveMind::CounterComponent::~CounterComponent()
{
	delete m_pFont;
	m_pFont = nullptr;
}
void HiveMind::CounterComponent::AddScore(const int& toAddScore0)
{
	m_Score += toAddScore0;
}

void HiveMind::CounterComponent::Initialize()
{
	TextComponent::Initialize();
	SetText(std::to_string(m_Score));
	m_IsInitialized = true;
}

void HiveMind::CounterComponent::Update(const float& elapsedSec)
{
	SetText(std::to_string(m_Score));
	TextComponent::Update(elapsedSec);
}

