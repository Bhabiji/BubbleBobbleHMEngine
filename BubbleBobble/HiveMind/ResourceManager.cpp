#include "HiveMindPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <unordered_map>
#include <algorithm>
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

void HiveMind::ResourceManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;
	// load support for png and jpg, this takes a while!
	m_pTextureMap = new std::map<std::string, Texture2D*>();
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) 
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) 
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0) 
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

HiveMind::Texture2D* HiveMind::ResourceManager::LoadTexture(const std::string& file, const std::string& texName) const
{
	
		const auto fullPath = m_DataPath + file;
		//If the key doesn't exist yet, add the key and texture, otherwise return the texture
		if (m_pTextureMap->find(texName) == m_pTextureMap->cend())
		{
			auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
			if (texture == nullptr) 
			{
				throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
			}
			m_pTextureMap->insert(std::pair<std::string, Texture2D*>{texName, new Texture2D(texture)});
		}
	
	return m_pTextureMap->at(texName);
}

HiveMind::Font* HiveMind::ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	return new Font(m_DataPath + file, size);
}

void HiveMind::ResourceManager::Destroy()
{
	if (m_pTextureMap)
	{
		m_pTextureMap->clear();
		delete m_pTextureMap;
	}
}
