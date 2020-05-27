#include "CounterComponent.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Font.h"
#include "Renderer.h"


#include "Components.h"
HiveMind::CounterComponent::CounterComponent(Font* pFont, const int& initCount, const FPoint2& posOffset)
	:TextComponent(std::to_string(initCount),pFont)
	, m_InitCount{ initCount }
{
}
HiveMind::CounterComponent::CounterComponent(Font* pFont, const int& initCount, const bool enableStaticPos, const FPoint2& staticPos)
	:TextComponent(std::to_string(initCount),pFont,enableStaticPos,staticPos)
	, m_InitCount{ initCount }
{
}
HiveMind::CounterComponent::~CounterComponent()
{
	delete m_pFont;
	m_pFont = nullptr;
}
void HiveMind::CounterComponent::AddToCounter(const int& toAddCount)
{
	m_InitCount += toAddCount;
}

void HiveMind::CounterComponent::SetCounter(const int& toSetCount)
{
	m_InitCount = toSetCount;
}

void HiveMind::CounterComponent::Initialize()
{
	TextComponent::Initialize();
	SetText(std::to_string(m_InitCount));
	m_IsInitialized = true;
}

void HiveMind::CounterComponent::Update(const float& elapsedSec)
{
	SetText(std::to_string(m_InitCount));
	TextComponent::Update(elapsedSec);
}

