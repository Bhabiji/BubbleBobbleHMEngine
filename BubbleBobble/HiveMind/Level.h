#pragma once
#include "Math.h"
#include "GameObject.h"

#include <vector>
#include <map>
#include <iostream>
#include <winnt.h> //SHORT
namespace HiveMind
{
	class Level final
	{
	public:
		Level(const std::vector<GameObject*>& levelBlocks);
		Level();

		std::vector<std::pair<std::pair<SHORT, Float2>, GameObject*>> GetLevelData() const;
		virtual ~Level();
		//Cpy/Move


		//FromBaseClass
		virtual void Initialize();
		virtual void Update(const float& deltaTime);
		virtual void Render() const;
		virtual bool IsOnGround() const;

	private:
		//EACH BLOCK IS A SEPARATE GAMEOBJECT
		std::vector<GameObject*> m_LevelBlocks;
		Float2 m_Scale;
	};
}
