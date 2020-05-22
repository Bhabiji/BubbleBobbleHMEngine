#pragma once
#include "BaseComponent.h"
#include <vector>
namespace HiveMind
{
	class GameObject;
	class PickupComponent :
		public BaseComponent
	{
	public:
		PickupComponent(const int& points, std::vector<GameObject*> pPlayers);
		PickupComponent(const int& points, GameObject* pPlayers);

		virtual ~PickupComponent();
		virtual void Update(const float& elapsedSec);
		virtual void Initialize();
		virtual void Render() const override;
	private:
		int m_Points;
		std::vector<GameObject*> m_pPlayers;

	};
}

