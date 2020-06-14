#include "HiveMindPCH.h"
#include "Texture2D.h"
#include <SDL.h>

HiveMind::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
	m_Texture = nullptr;
}

SDL_Texture* HiveMind::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

HiveMind::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
}
