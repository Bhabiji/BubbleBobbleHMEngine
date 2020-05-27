#include "BulletManager.h"
#include "SceneManager.h"
#include "Scene.h"
HiveMind::BulletManager::BulletManager()
{
	
}


HiveMind::BulletManager::~BulletManager()
{
}

void HiveMind::BulletManager::CreateBubbleBullet(const FPoint3& pos, const FPoint2& velocity, float lifeTime, bool lookingLeft)
{
	auto currScene = SceneManager::GetInstance().GetActiveScene();
	GameObject* pBullet{ new GameObject() };
	pBullet->CreateBlob(lookingLeft, pos, velocity, lifeTime);
	currScene->Add(pBullet);
}

void HiveMind::BulletManager::CreateFireBall(const FPoint3& pos, const FPoint2& velocity, float lifeTime, bool lookingLeft)
{
	auto currScene = SceneManager::GetInstance().GetActiveScene();
	GameObject* pBullet{ new GameObject() };
	pBullet->CreateFireBall(lookingLeft, pos, velocity, lifeTime);
	currScene->Add(pBullet);
}

