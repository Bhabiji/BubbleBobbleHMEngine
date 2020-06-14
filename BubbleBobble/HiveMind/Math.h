#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

#include "Primitives.h"

namespace HiveMind {

	typedef glm::vec3 FVec3;
	typedef glm::vec3 FPoint3;
	typedef glm::vec3 Float3;


	typedef glm::vec2 FVector2;
	typedef glm::vec2 FPoint2;
	typedef glm::vec2 Float2;

	struct Int2 {
		int x, y;
	};

	bool IsOverlapping(const FPoint2& objPos, const HiveMind::RectI& otherArea);
	bool IsOverlapping(const HiveMind::RectI& area, const HiveMind::RectI& otherArea);
	bool IsOverlapping(const Int2& objPos, const HiveMind::RectI& otherArea);

	
}