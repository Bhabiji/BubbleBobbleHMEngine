#pragma once
#include "CounterComponent.h"
namespace HiveMind
{

	class HealthCounterComponent : public CounterComponent
	{
	public:
		HealthCounterComponent(Font* pFont, const int& initHealth, const FPoint2& posOffset);
		virtual ~HealthCounterComponent() = default;
	private:

	};
}

