#include "LifeCounterComponent.h"

HiveMind::LifeCounterComponent::LifeCounterComponent(Font* pFont, const int& initScore, const FPoint2& posOffset)
	:CounterComponent(pFont, initScore, true, posOffset)
{
}
