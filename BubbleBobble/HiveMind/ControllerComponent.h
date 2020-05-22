#pragma once
#include "BaseComponent.h"
#include "Math.h"
namespace HiveMind
{
	class ControllerComponent final : public BaseComponent
	{
	public:
		ControllerComponent(const FPoint3& pos);
		virtual ~ControllerComponent();
		ControllerComponent(const ControllerComponent& other) = delete;
		ControllerComponent(ControllerComponent&& other) = delete;
		ControllerComponent& operator=(const ControllerComponent& other) = delete;
		ControllerComponent& operator=(const ControllerComponent&& other) = delete;

	protected:
		virtual void Initialize() override;
		virtual void Update(const float& elapsedSec) override;
		virtual void Render() const override;
	private:
		void UpdateMovement(const float& elapsedSec);

		const bool m_LookingLeft;
		FVector2 m_Velocity;
		float m_LifeTime;
		FPoint3 m_Pos;
		int m_FrameX;
		int m_FrameY;
	};
}


