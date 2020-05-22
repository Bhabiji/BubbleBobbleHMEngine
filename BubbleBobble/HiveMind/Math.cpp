#include "Math.h"

bool HiveMind::IsOverlapping(const FPoint2& objPos, const HiveMind::RectI& otherArea)
{
	if (objPos.x >= otherArea.x && objPos.x <= (otherArea.x + otherArea.w) && objPos.y >= otherArea.y && objPos.y <= (otherArea.y + otherArea.h))
	{
		return true;
	}
	return false;
}

bool HiveMind::IsOverlapping(const HiveMind::RectI& area, const HiveMind::RectI& otherArea)
{
	// If one rectangle is on left side of the other
	if ((area.x + area.w) < otherArea.x || (otherArea.x + otherArea.w) < area.x)
	{
		return false;
	}

	// If one rectangle is under the other
	if (area.y > (otherArea.y + otherArea.h) || otherArea.x > (area.x + area.h))
	{
		return false;
	}

	return true;
}
