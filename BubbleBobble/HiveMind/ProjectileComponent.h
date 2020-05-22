#pragma once
#include "BaseComponent.h"
#include "Math.h"
namespace HiveMind 
{
	class ProjectileComponent : public BaseComponent
	{
	public:
		ProjectileComponent(const bool isLookingLeft, const FPoint3& pos, const FVector2& velocity);
		virtual ~ProjectileComponent();
		ProjectileComponent(const ProjectileComponent& other) = delete;
		ProjectileComponent(ProjectileComponent&& other) = delete;
		ProjectileComponent& operator=(const ProjectileComponent& other) = delete;
		ProjectileComponent& operator=(const ProjectileComponent&& other) = delete;

	protected:
		virtual void Initialize() override;
		virtual void Update(const float& elapsedSec) override;
		virtual void Render() const override;
	private:
		void UpdateMovement(const float& elapsedSec);
		void UpdateCollision(const float& elapsedSec);
		const bool m_LookingLeft;
		FVector2 m_Velocity;
		float m_LifeTime;
		FPoint3 m_Pos;
		int m_FrameX;
		int m_FrameY;
	};
}

