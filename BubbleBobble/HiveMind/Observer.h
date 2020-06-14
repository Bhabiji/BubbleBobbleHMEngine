#pragma once
#pragma once
#include "GameObject.h"
#include "ActorComponent.h"
#include "HealthComponent.h"
#include "SceneManager.h"
#include "Scene.h"

namespace HiveMind
{
	class Observer
	{

	public:
		enum class Event
		{
			ISHIT, DEATH
		};
		virtual ~Observer() = default;
		virtual void OnNotify(GameObject* pActor, Event event) = 0;
		
	};

	class HealthObserver final : public Observer
	{
	public:
		virtual ~HealthObserver() = default;
		virtual void OnNotify(GameObject* pActor, Event event) override
		{
			if (event == Event::ISHIT) 
			{
				if(pActor->HasComponent<HealthComponent>())
				{ 
					if(pActor->GetComponent<HealthComponent>()->GetHealth() > 0)
						pActor->GetComponent<HealthComponent>()->DecreaseHealth(1);
					//pActor->GetComponent<ActorComponent>()->Death();

				}
			};
			
		}
	private:
	};

	class DeathObserver final : public Observer
	{
	public:
		virtual ~DeathObserver() = default;
		virtual void OnNotify(GameObject* pActor, Event event) override
		{
			if (event == Event::DEATH)
			{
				pActor->SetActive(false);
				SceneManager::GetInstance().SetSceneActive("GameOver", true);
			};

		}
	private:
	};

}