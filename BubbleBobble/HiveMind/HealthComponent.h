#pragma once
#include "BaseComponent.h"
namespace HiveMind
{
	class HealthComponent : public BaseComponent
	{
		public:
			HealthComponent(const int health = 1);
			virtual ~HealthComponent() = default;
			void DecreaseHealth(const int decreaseVal);
			int GetHealth() const;
			virtual void Update(const float& elapsedSec) override;
			virtual void Render() const override;
			virtual void Initialize () override;
			void SetInvincibility(const bool setInvincible);


		private:
			int m_Health;
			bool m_IsInvincible;
	};
}

