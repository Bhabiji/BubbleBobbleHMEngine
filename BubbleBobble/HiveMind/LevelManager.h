#pragma once
#include "Singleton.h"
#include "LevelParser.h"
#include "Scene.h"
#include <map>
namespace HiveMind
{
	class LevelManager final : public Singleton<LevelManager>
	{
	public:
		virtual ~LevelManager();
		void AddLevel(const std::wstring& pathName, Scene* scene);
		std::vector<GameObject*> GetCurrentLevel() const;
		void ParseLevel(const std::wstring& pathName);
		
	private:
		LevelParser* m_Parser;
		std::map<int, std::vector<GameObject*>> m_pLevelBlocks; //Map of 2 levels, always load 1 extra level, key is nr of level, gameobject vector are all blocks of that lvl
		int m_LatestLevel{};
	};
}

