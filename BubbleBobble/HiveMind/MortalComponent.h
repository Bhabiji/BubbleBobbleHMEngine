#pragma once
#include "BaseComponent.h"
namespace HiveMind
{
	class MortalComponent final : public BaseComponent
	{
	public:
		MortalComponent();
		MortalComponent(const int& lives);
		virtual ~MortalComponent();
		virtual void Update(const float& elapsedSec);
		void Hit();
	private:
		int m_Lives;
	};
}

