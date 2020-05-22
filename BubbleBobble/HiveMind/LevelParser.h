#pragma once
#include "Level.h"
#include "Math.h"
#include <string>
#include <vector>
#include "GameObject.h"
namespace HiveMind
{

	class LevelParser
	{
	public:
		LevelParser();
		virtual ~LevelParser()=default;
		std::vector<GameObject*>  ParseLevel(const std::wstring& pathName);

	private:
		
		std::vector<GameObject*> m_LevelData; //ID and Pos (row and col)
	};

}

