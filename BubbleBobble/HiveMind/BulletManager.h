#pragma once
#include "Singleton.h"
#include <vector>
#include "Math.h"
namespace HiveMind
{

	class BulletManager final : public Singleton<BulletManager>
	{
	public:
		BulletManager();
		~BulletManager();
		void CreateBubbleBullet(const FPoint3& pos, const FPoint2& velocity, float lifeTime, bool lookingLeft);
		void CreateFireBall(const FPoint3& pos, const FPoint2& velocity, float lifeTime, bool lookingLeft);

	private:
	};


}