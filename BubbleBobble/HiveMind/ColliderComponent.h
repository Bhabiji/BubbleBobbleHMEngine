#pragma once
#include "BaseComponent.h"
#include "Math.h"
#include "Primitives.h"
#include <vector>
#include "Physics.h"
namespace HiveMind
{
	class GameObject;
	class ColliderComponent : public BaseComponent
	{
	public:
		ColliderComponent();
		ColliderComponent(const FPoint2& pos, const RectI& collisionArea);
		virtual ~ColliderComponent();
		virtual void RayHitObstacle(const GameObject* objectsToCheck, const FPoint2& objPos) = 0;
		virtual bool IsColliding(const FPoint2& Point) = 0;
	protected:
		virtual void Initialize() override;
		virtual void Update(const float& deltaTime) override = 0;
		virtual void Render() const override = 0;

		//Pos of parented gameobject and it's collisionArea
		FPoint2 m_Pos;
		RectI m_CollisionArea;
		Float2 m_Measures;
	private:
	};
}

