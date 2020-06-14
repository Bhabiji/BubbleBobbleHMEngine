#include "HiveMindPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "TransformComponent.h"
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"

HiveMind::TextComponent::TextComponent(const std::string& text,  Font* font)
	: m_NeedsUpdate(true), m_Text(text), m_Font{ font }
{ }

HiveMind::TextComponent::TextComponent(const std::string& text, Font* font, const bool enableStaticPos, const FPoint2& staticPos)
	:RenderComponent(enableStaticPos,staticPos)
	,m_Font{font}
	, m_NeedsUpdate(true)
	, m_Text(text)
{
}

HiveMind::TextComponent::~TextComponent()
{
	delete m_Font;
	m_Font = nullptr;
}

void HiveMind::TextComponent::Initialize()
{
	m_IsInitialized = true;
	const SDL_Color color = { 255,255,255 }; // only white text is supported now
	const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	SetTextTexture(new Texture2D(texture));
}

void HiveMind::TextComponent::Update(const float& elapsedSec)
{
	RenderComponent::Update(elapsedSec);
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		SetTextTexture(new Texture2D(texture));

		m_NeedsUpdate = false;
	}
}


// This implementation uses the "dirty flag" pattern
void HiveMind::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

