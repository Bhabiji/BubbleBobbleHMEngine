#pragma once
#include "ColliderComponent.h"
#include "Math.h"
#include <vector>
#include "Physics.h"
namespace HiveMind
{
	class BlockColliderComponent : public ColliderComponent
	{
	public:
		BlockColliderComponent();
		BlockColliderComponent(const FPoint2& pos, const RectI& collisionArea);
		virtual ~BlockColliderComponent();
		virtual bool IsColliding(const FPoint2& point);
		virtual void RayHitObstacle(const GameObject* objectsToCheck, const FPoint2& objPos);

	protected:
		//virtual void Initialize() override;
		virtual void Update(const float& deltaTime) override;
		virtual void Render() const override;

		//Pos of parented gameobject and it's collisionArea
	private:
	};
}

