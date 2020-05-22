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
		void CreateBullet(const FPoint3& Pos, const FPoint2& velocity, float lifeTime, bool lookingLeft);

	private:
	};


}