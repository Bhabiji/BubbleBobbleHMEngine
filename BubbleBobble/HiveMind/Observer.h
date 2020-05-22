#pragma once
#pragma once
#include "GameObject.h"

namespace HiveMind
{
	class Observer
	{

	public:
		enum class Event
		{
			HIT, PICKUP
		};
		virtual ~Observer() = default;
		virtual void OnNotify(GameObject* pCharacter, Event event) = 0;
		
	};

	class HealthDisplay final : public Observer
	{
	public:
		virtual ~HealthDisplay() = default;
		virtual void OnNotify(GameObject* pSubject, Event event) override
		{
			(pSubject);
			if (event == Event::HIT) {};
			//Get textrendercomponent from character and update it
		}
	private:
	};

	class ScoreDisplay final :public Observer
	{
	public:
		virtual ~ScoreDisplay() = default;
		virtual void OnNotify(GameObject* pSubject, Event event) override
		{
			(pSubject);

			if (event == Event::PICKUP) {};
			//Get textrendercomponent from character and update it
		}
	private:
	};
}