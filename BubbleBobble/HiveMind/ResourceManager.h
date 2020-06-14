#pragma once
#include "Singleton.h"
#include <map>
#include <string>

namespace HiveMind
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		Texture2D* LoadTexture(const std::string& file, const std::string& texName) const;
		Font* LoadFont(const std::string& file, unsigned int size) const;
		void Destroy();
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_DataPath;
		std::map<std::string, Texture2D*>* m_pTextureMap;
	};
}
