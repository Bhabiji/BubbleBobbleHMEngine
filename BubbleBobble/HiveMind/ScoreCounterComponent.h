#pragma once
#include "CounterComponent.h"
namespace HiveMind
{
	class ScoreCounterComponent final : public CounterComponent
	{
	public:
		ScoreCounterComponent(Font* pFont, const int& initScore, const FPoint2& posOffset);
		virtual ~ScoreCounterComponent() = default;
	private:

	};
}

