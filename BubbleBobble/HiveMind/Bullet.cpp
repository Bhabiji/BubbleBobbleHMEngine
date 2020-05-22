#include "Bullet.h"
#include "Components.h"
#include "SceneManager.h"
#include "Scene.h"
HiveMind::Bullet::Bullet(const bool isLookingLeft, const FPoint2& pos, const FPoint2& velocity, const float lifeTime)
	:m_ClipX{0}
	,m_ClipY{0}
	, m_AnimTime{}
	, m_FadeOut{}
	, m_LookingLeft{ isLookingLeft }
	, m_Velocity{ velocity }
	, m_LifeTime{ lifeTime }
{
	FPoint3 startPos{ pos,0 };
	GetTransform()->SetPosition( startPos);
}
void HiveMind::Bullet::Initialize()
{
	SpriteComponent* pSprite{ new SpriteComponent("../Data/BulletSprite.png","Bullets") };

	FPoint2 srcPos{ pSprite->GetCroppedWidth() * m_ClipX,pSprite->GetCroppedWidth() * m_ClipY };
	FPoint3 pos{ GetTransform()->GetPosition() };
	GetTransform()->SetPosition(pos);
	pSprite->SetLocalSpriteArea(srcPos, pos);
	pSprite->SetCroppingDimensions(SpriteConfig{ 8,1 });
	AddComponent(pSprite);


}

void HiveMind::Bullet::Update(const float& elapsedSec)
{
	if (m_LifeTime <= 0)
		return;
	
	FPoint3 currPos{ GetTransform()->GetPosition() };
	if (m_LookingLeft)
	{
		currPos.x -= m_Velocity.x * elapsedSec;
		currPos.y -= m_Velocity.y * elapsedSec;
	}
	else 
	{
		currPos.x += m_Velocity.x * elapsedSec;
		currPos.y += m_Velocity.y * elapsedSec;
	}

	m_AnimTime += elapsedSec;
	if (m_AnimTime >= 0.2f)
	{
		int colAmount{ 8 };
		int rowAmount{ 1 };
		m_ClipX++;
		if (m_ClipX >= colAmount)
			m_ClipX = 0;
		m_AnimTime = 0;
	}

	GetTransform()->SetPosition(currPos);
	m_LifeTime -= elapsedSec;

	
}

void HiveMind::Bullet::Render() const
{
	if (m_LifeTime <= 0)
		return;

	FPoint2 pos{ GetTransform()->GetPosition() };
	SpriteComponent* temp{ GetComponent<SpriteComponent>() };
    FPoint2 srcPos{ temp->GetCroppedWidth() * m_ClipX, temp->GetCroppedHeight() * m_ClipY };
	temp->SetLocalSpriteArea(srcPos, pos);
	temp->RescaleSprite(Float2(1, 1));

	GameObject::Render();
}

float HiveMind::Bullet::GetLifeTime() const
{
	return m_LifeTime;
}
