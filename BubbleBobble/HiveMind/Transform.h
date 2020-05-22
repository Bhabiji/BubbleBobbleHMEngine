#pragma once
#include "Math.h"

namespace HiveMind
{
	class Transform final
	{
	public:
		const FPoint3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
	private:
		FPoint3 m_Position;
	};
}
