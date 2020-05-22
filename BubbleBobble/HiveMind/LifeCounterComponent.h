#pragma once
#include "CounterComponent.h"
namespace HiveMind
{
	class LifeCounterComponent final : public CounterComponent
	{
	public:
		LifeCounterComponent(Font* pFont, const int& initScore, const FPoint2& posOffset);
		virtual ~LifeCounterComponent()  = default;
	private:

	};
}

