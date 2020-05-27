#pragma once
#include "ColliderComponent.h"
#include "BlockColliderComponent.h"
#include "Math.h"
#include <vector>
#include "Physics.h"

namespace HiveMind
{
	class BlockColliderComponent;
	class CharacterColliderComponent final : public ColliderComponent
	{
	public:
		CharacterColliderComponent();
		CharacterColliderComponent(const FPoint2& pos, const RectI& collisionArea);
		virtual ~CharacterColliderComponent();
		virtual void RayHitObstacle(const GameObject* objectsToCheck, const FPoint2& objPos);
		virtual bool IsCollidingVertically(const FPoint2& Point);
		virtual bool IsCollidingHorizontally(const FPoint2& Point);
		ColliderBox GetCollisionResults() const;
		void ResetCollision();
	protected:
		//virtual void Initialize() override;
		virtual void Update(const float& deltaTime) override;
		virtual void Render() const override;

		//Pos of parented gameobject and its collisionArea
	private:
		ColliderBox m_ColliderBox;


		//TEST
		HiveMind::Line g_Left{};
		HiveMind::Line g_Right{};
		HiveMind::Line g_Up{};
		HiveMind::Line g_Down{};
		HiveMind::Line g_LeftFoot{};
		HiveMind::Line g_RightFoot{};

	};
}

