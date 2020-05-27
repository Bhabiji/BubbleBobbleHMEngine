#pragma once
#include "BaseComponent.h"
#include "Math.h"
namespace HiveMind
{
	class PhysicsComponent : public BaseComponent
	{
	public:
		PhysicsComponent();
		virtual ~PhysicsComponent();

	protected:
		virtual void Initialize() override;
		virtual void Update(const float& deltaTime) override;
		virtual void Render() const override;
	private:
		float m_Gravity;
		Float2 m_Velocity;

	};
}

