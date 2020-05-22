#include "PlayerCharacter.h"
#include "InputManager.h"
#include "LevelManager.h"
#include "BulletManager.h"
#include "Physics.h"
HiveMind::PlayerCharacter::PlayerCharacter(const SpriteConfig& spriteConfig)
	: m_pSpriteComponent{new SpriteComponent("../Data/CharacterSprites.png", "Characters", spriteConfig, false) }
	, m_FaceLeft{false}
	, m_SpriteConfig{spriteConfig}
	, m_ClipX{0}
	, m_ClipY{0}
	, m_AnimFrame{0}
	, m_AnimTime{0}
	,m_ShootingTimer{1.5f}
	, m_MovementSpeed{100.f}
	, m_Movement{}
	, m_JumpSpeed{100}
	, m_JumpVel{}
	, m_Gravity{9.81f}
	, m_pActorComponent{new ActorComponent()}

{
	m_pSpriteComponent->SetCroppingDimensions();
	FPoint2 srcPos{ m_pSpriteComponent->GetCroppedWidth() * m_ClipX,m_pSpriteComponent->GetCroppedWidth() * m_ClipY };
	FPoint3 pos{ GetTransform()->GetPosition() };
	GetTransform()->SetPosition(pos);
	m_pSpriteComponent->SetLocalSpriteArea(srcPos, pos);

	AddComponent(m_pActorComponent);
	AddComponent(m_pSpriteComponent);
	AddComponent(new CharacterColliderComponent());
	m_pSpriteComponent->RescaleSprite(Float2(2, 2));
	SetPosition(FPoint2(100, 170));


}

HiveMind::PlayerCharacter::~PlayerCharacter()
{
}


void HiveMind::PlayerCharacter::Update(const float& elapsedSec)
{

	
	//UpdateCollision(elapsedSec);
	//UpdateAnimation(elapsedSec);
	GameObject::Update(elapsedSec);
}

//void HiveMind::PlayerCharacter::Render() const
//{
//	/*FPoint2 pos{ GetTransform()->GetPosition() };
//
//	FPoint2 srcPos{ (m_pSpriteComponent->GetCroppedWidth() * m_ClipX),m_pSpriteComponent->GetCroppedHeight() * m_ClipY };
//	m_pSpriteComponent->SetLocalSpriteArea(srcPos, pos);
//	
//
//	GameObject::Render();*/
//
//}

void HiveMind::PlayerCharacter::UpdateAnimation(const float& elapsedSec)
{

	m_AnimTime += elapsedSec;
	if (m_AnimTime >= 0.2f)
	{
	int colAmount{ 8 };
	int rowAmount{ 6 };
		if (m_pActorComponent->GetActorState() == ActorComponent::ActorState::IDLE)
		{
			m_ClipY = 2;
			if (m_FaceLeft)
				m_ClipY = 3;
		}
		else if (m_pActorComponent->GetActorState() == ActorComponent::ActorState::LEFT)
		{
			m_ClipY = 3;
			++m_ClipX;
		}
		else if (m_pActorComponent->GetActorState() == ActorComponent::ActorState::RIGHT)
		{
			m_ClipY = 2;
			++m_ClipX;
		}
		else if (m_pActorComponent->GetActorState() == ActorComponent::ActorState::SHOOT)
		{
			m_ClipY = 0;
			if(m_FaceLeft)
				m_ClipY = 1;
		}
		if (m_pActorComponent->GetActorState() == ActorComponent::ActorState::JUMP)
		{
			m_ClipY = 2;
			if(m_FaceLeft)
				m_ClipY = 3;
		}
	if (m_ClipX >= colAmount)
		m_ClipX = 0;
		m_AnimTime = 0;
	}
}

void HiveMind::PlayerCharacter::UpdateCombat(const float& elapsedSec)
{
	const float cooldown{ 0.5f };
	m_ShootingTimer += elapsedSec;
	if (m_pActorComponent->GetActorState() == ActorComponent::ActorState::SHOOT && m_ShootingTimer >= cooldown)
	{
		if (m_FaceLeft)
		{
			BulletManager::GetInstance().CreateBullet(FPoint3(GetTransform()->GetPosition().x, GetTransform()->GetPosition().y + m_pSpriteComponent->GetDest().h/3.f, 0.f), FPoint2(60, 0), 3.f, m_FaceLeft);
		}
		else
		{
			BulletManager::GetInstance().CreateBullet(FPoint3(GetTransform()->GetPosition().x + m_pSpriteComponent->GetDest().w, GetTransform()->GetPosition().y + m_pSpriteComponent->GetDest().h / 3.f, 0.f), FPoint2(60, 0), 3.f, m_FaceLeft);
		}
		m_ShootingTimer = 0;
	}
}



void HiveMind::PlayerCharacter::UpdateMovement(const float& elapsedSec)
{
	//FPoint2 pos{ GetTransform()->GetPosition() };

	//const ColliderBox& collider = GetComponent<CharacterColliderComponent>()->GetCollisionResults();
	//GetComponent<CharacterColliderComponent>()->ResetCollision();
	//if (m_pActorComponent->GetActorState() == ActorComponent::ActorState::IDLE)
	//{
	//	m_Movement.y = 0;
	//}
	//else if (m_pActorComponent->GetActorState() == ActorComponent::ActorState::LEFT && !collider.left)
	//{
	//	pos.x -= m_MovementSpeed * elapsedSec;
	//	std::cout << "XPos:" << pos.x << std::endl;
	//	m_FaceLeft = true;
	//}
	//else if (m_pActorComponent->GetActorState() == ActorComponent::ActorState::RIGHT && !collider.right)
	//{
	//	pos.x += m_MovementSpeed * elapsedSec;
	//	std::cout << "XPos:" << pos.x << std::endl;
	//	m_FaceLeft = false;


	//}
	//if (m_pActorComponent->GetActorState() == ActorComponent::ActorState::JUMP && m_IsOnGround )
	//{
	//	if (collider.bottom /*&& m_Movement.y <= 0*/)
	//	{
	//		m_JumpVel = 0;
	//		m_Movement.y = -5;
	//		m_IsOnGround = false;

	//	}
	//	else if (!collider.bottom)
	//	{
	//		m_IsOnGround = true;
	//	}
	//	std::cout << "YPos:" << pos.y << std::endl;

	//	//pos.y += m_Gravity * elapsedSec;
	//}
	//if (!collider.bottom)
	//{
	//	m_JumpVel = 0.15f;
	//	m_Movement.y += m_JumpVel;
	//	m_IsOnGround = false;
	//

	//	pos.y += m_Gravity * elapsedSec;
	//}
	//if (collider.bottom && m_pActorComponent->GetActorState() != ActorComponent::ActorState::JUMP)
	//{
	//	m_IsOnGround = true;
	//	m_Movement.y = 0;
	//}
	//if (collider.bottom && m_Movement.y > 0)
	//{
	//	m_Movement.y = 0;
	//	m_IsOnGround = true;

	//}
	//pos.y += m_Movement.y;
	//SetPosition(pos);

}

void HiveMind::PlayerCharacter::UpdateCollision(const float& elapsedSec)
{
	CharacterColliderComponent* charCol{ GetComponent<CharacterColliderComponent>() };
	std::vector<GameObject*> levelData{ LevelManager::GetInstance().GetCurrentLevel() };
	for (size_t i{ 0 }; i < levelData.size(); i++)
	{
		charCol->RayHitObstacle(levelData[i], GetTransform()->GetPosition());
	}
}

