#include "PickupComponent.h"
#include "Components.h"
#include "Math.h"
#include "GameObject.h"
HiveMind::PickupComponent::PickupComponent(const int& points, std::vector<GameObject*> pPlayers)
	:m_Points{points}
	,m_pPlayers{ pPlayers }
{

}

HiveMind::PickupComponent::PickupComponent(const int& points, GameObject* pPlayers)
	:m_Points{ points }
{
	m_pPlayers.push_back(pPlayers);
}

HiveMind::PickupComponent::~PickupComponent()
{
	/*for (size_t i{ 0 }; i < m_pPlayers.size(); i++)
	{
		delete m_pPlayers[i];
	}*/
}

//shouldve used observer pattern
void HiveMind::PickupComponent::Update(const float& elapsedSec)
{
	(elapsedSec);

	for (GameObject* player : m_pPlayers)
	{
		if (HiveMind::IsOverlapping(player->GetComponent<SpriteComponent>()->GetDest(), GetGameObject()->GetComponent<SpriteComponent>()->GetDest()))
		{
			if (player->HasComponent<ScoreCounterComponent>())
			{
				player->GetComponent<ScoreCounterComponent>()->AddToCounter(m_Points);
				if (GetGameObject()->HasComponent<SoundComponent>())
				{
					GetGameObject()->GetComponent<SoundComponent>()->PlaySoundByName("Pickup");
				}
				GetGameObject()->SetActive(false);
			}
		}

	}
}

void HiveMind::PickupComponent::Initialize()
{
}

void HiveMind::PickupComponent::Render() const
{
}
