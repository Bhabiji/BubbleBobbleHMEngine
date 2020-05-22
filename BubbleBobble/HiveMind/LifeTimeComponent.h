#pragma once
#include "BaseComponent.h"
namespace HiveMind
{
	class LifeTimeComponent : public BaseComponent
	{
	public:
		LifeTimeComponent(const float lifeTime, const bool isTimer);
		virtual ~LifeTimeComponent();
		LifeTimeComponent(const LifeTimeComponent& other) = delete;
		LifeTimeComponent(LifeTimeComponent&& other) = delete;
		LifeTimeComponent& operator=(const LifeTimeComponent& other) = delete;
		LifeTimeComponent& operator=(const LifeTimeComponent&& other) = delete;
		bool IsActive() const;
		void ToggleActive(const bool toggle);

	protected:
		virtual void Initialize();
		virtual void Update(const float& deltaTime);
		virtual void Render() const;
	private:
		float m_LifeTime;
		float m_MaxLifeTime;
		bool m_Active;
		bool m_IsTimer;
	};
}

