#include "HiveMindPCH.h"
#include "Components.h"
#include "Observer.h"
#include "BulletManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ControllerComponent.h"
#include "LevelManager.h"
HiveMind::ActorComponent::ActorComponent(const bool isPlayer, const bool isMaita, const bool isZenChan, const float& maxMoveSpeed)
	:m_ActorState{ ActorState::IDLE }
	, m_MovementSpeed{ 100 }
	, m_Velocity{}
	, m_JumpSpeed{ 200 }
	, m_MaxFallSpeed{ 100 }
	, m_JumpVel{}
	, m_Gravity{ 100 }
	, m_MaxRunSpeed{ maxMoveSpeed }
	, m_FaceLeft{ false }
	, m_IsOnGround{ false }
	, m_IsJumping{false}
	, m_ClipX{ 0 }
	, m_ClipY{ 0 }
	, m_AnimFrame{ 0 }
	, m_AnimTime{ 0 }
	, m_IsMaita{ isMaita }
	, m_IsZenChan{ isZenChan }
	, m_IsPlayer{ isPlayer }
	, m_IsNPC{!isPlayer}
	, m_pTargetToKill{nullptr}
	, m_ToTargetCooldown{ 1.5f }
	, m_flyTimer{0}
	, m_SpawnPickup{ false }
	, m_Counter{0.2f}
	, m_RespawnTimer{}

{
	if (m_IsMaita && m_IsZenChan)
		throw("Cant be 2 separate entities at once");
	if (m_IsMaita || m_IsZenChan)
	{
		m_IsEnemy = true;
	}
}

HiveMind::ActorComponent::~ActorComponent()
{
	for (size_t i{}; i < m_CurrentNrObservers; i++)
	{
		delete m_pObservers[i];
		m_pObservers[i] = nullptr;
	}
}

HiveMind::ActorComponent::ActorState HiveMind::ActorComponent::GetActorState() const
{
	return m_ActorState;
}

HiveMind::FVector2 HiveMind::ActorComponent::GetVelocity() const
{
	return m_Velocity;
}

void HiveMind::ActorComponent::Initialize()
{
	m_IsInitialized = true;
}

void HiveMind::ActorComponent::Update(const float& elapsedSec)
{
	if (m_ActorState != ActorComponent::ActorState::DEATH)
	{
		
		if (m_IsNPC)
			UpdateNPCStates(elapsedSec);

	}
	else if (m_ActorState == ActorComponent::ActorState::DEATH && m_IsEnemy)
		HandleNPCDeath(elapsedSec);
	else if (m_ActorState == ActorComponent::ActorState::DEATH && !m_IsNPC)
		HandlePlayerDeath(elapsedSec);

		UpdateMovement(elapsedSec);
		UpdateCombat(elapsedSec);
		UpdateAnimation(elapsedSec);
}

void HiveMind::ActorComponent::Render() const
{
}

bool HiveMind::ActorComponent::IsNPC()
{
	return m_IsNPC;
}

bool HiveMind::ActorComponent::IsEnemy()
{
	return m_IsEnemy;
}

void HiveMind::ActorComponent::SetTarget(GameObject* pGameObject)
{
	m_pTargetToKill = pGameObject;
}

void HiveMind::ActorComponent::AddObserver(Observer* pObserver)
{
	m_pObservers[m_CurrentNrObservers] = pObserver;
	m_CurrentNrObservers++;
}

void HiveMind::ActorComponent::Notify(Observer::Event event)
{
	for (UINT i{}; i < m_CurrentNrObservers; ++i)
	{
		m_pObservers[i]->OnNotify(GetGameObject(), event);
	}
}

void HiveMind::ActorComponent::UpdateMovement(const float& elapsedSec)
{
	float maxVelocity{ 200 };
	const ColliderBox& collider = GetGameObject()->GetComponent<CharacterColliderComponent>()->GetCollisionResults();
	GetGameObject()->GetComponent<CharacterColliderComponent>()->ResetCollision();
	if (!collider.bottom)
	{
		m_Counter += elapsedSec;
		m_Velocity.y += m_Gravity * m_Counter *  elapsedSec * 2;
		if (m_Velocity.y >= maxVelocity)
			m_Velocity.y = maxVelocity;
	}
	else if (!m_IsJumping)
	{
		m_Velocity.y = 0;
		m_Counter = 0.2f;
	}

	float yGlidingTrigger{ 200 };

	if (collider.left && m_FaceLeft)
	{
		m_Velocity.x = 0;
	}
	if (collider.right && !m_FaceLeft)
	{
		m_Velocity.x = 0;
	}
	if (collider.bottom && m_IsJumping)
		m_IsJumping = false;

	FPoint2 pos{ GetTransform()->GetPosition() };
	pos.y += m_Velocity.y * elapsedSec;
	pos.x += m_Velocity.x * elapsedSec;
	GetGameObject()->SetPosition(pos);
}

void HiveMind::ActorComponent::UpdateCombat(const float& elapsedSec)
{
	m_ShootingTimer += elapsedSec;
}

void HiveMind::ActorComponent::UpdateAnimation(const float& elapsedSec)
{
	m_AnimTime += elapsedSec;
	SpriteComponent* tempComp = GetGameObject()->GetComponent<SpriteComponent>();
	if (m_AnimTime >= 0.2f)
	{
		int colAmount{ tempComp->GetSpriteConfig().columns };
		int rowAmount{ tempComp->GetSpriteConfig().rows };

		++m_ClipX;
		if (m_ClipX >= colAmount)
			m_ClipX = 0;
		m_AnimTime = 0;
	}
	FPoint2 pos{ GetTransform()->GetPosition() };

	FPoint2 srcPos{ (tempComp->GetCroppedWidth() * m_ClipX),tempComp->GetCroppedHeight() * m_ClipY };
	tempComp->SetLocalSpriteArea(srcPos, pos);
	
}

void HiveMind::ActorComponent::UpdateNPCStates(const float& elapsedSec)
{
	if (m_pTargetToKill)
	{
	
		if (LevelManager::GetInstance().GetEnemyCount() == 1)
		{
			m_MovementSpeed = 160;
			m_MaxRunSpeed = 160;

		}
		float maitaShootCooldown{ 5.f };
		const FPoint2& pos{ GetTransform()->GetPosition() };
		const FPoint2& targetPos{ m_pTargetToKill->GetTransform()->GetPosition() };
		const ColliderBox& collider = GetGameObject()->GetComponent<CharacterColliderComponent>()->GetCollisionResults();

		if (m_FaceLeft && !collider.left)
			MoveLeft();
		else if (!m_FaceLeft && !collider.right)
			MoveRight();
		else if (collider.left)
			MoveRight();
		else if (collider.right)
			MoveLeft();
		if (!collider.rightFoot && !m_FaceLeft)
		{
			if (pos.y > targetPos.y - 5)
			{
				if (pos.x < targetPos.x + 1)
				{
					m_JumpSpeed = 100;
					Jump();

				}
				else
					MoveLeft();
			}
		}
		if (!collider.leftFoot && m_FaceLeft)
		{
			if (pos.y > targetPos.y - 5)
			{
				if (pos.x > targetPos.x)
				{
					m_JumpSpeed = 100;
					Jump();

				}
				else
					MoveRight();
			}
		}

		//update compared to target (player) position
		if (pos.y - 2 > targetPos.y&& collider.bottom && m_ToTargetCooldown <= m_ToTargetTimer)
		{
			m_JumpSpeed = 200;
			Jump();
			m_ToTargetTimer = 0;
		}
		m_ToTargetTimer += elapsedSec;
		if (!m_IsPlayer && m_IsMaita)
			if (m_ShootingTimer >= maitaShootCooldown)
				Shoot();
	}
	
	if (HiveMind::IsOverlapping(GetGameObject()->GetComponent<SpriteComponent>()->GetDest(), m_pTargetToKill->GetComponent<SpriteComponent>()->GetDest()))
	{
		m_pTargetToKill->GetComponent<ActorComponent>()->Notify(Observer::Event::ISHIT);
	}

}

void HiveMind::ActorComponent::HandleNPCDeath(const float& elapsedSec)
{
	m_AnimTime += elapsedSec;
	

	SpriteComponent* tempComp = GetGameObject()->GetComponent<SpriteComponent>();
	if (m_AnimTime >= 0.2f)
	{
		int colAmount{ tempComp->GetSpriteConfig().columns };
		int rowAmount{ tempComp->GetSpriteConfig().rows };
	
	}
	FPoint2 pos{ GetTransform()->GetPosition() };

	FPoint2 srcPos{ (tempComp->GetCroppedWidth() * m_ClipX),tempComp->GetCroppedHeight() * m_ClipY };
	tempComp->SetLocalSpriteArea(srcPos, pos);
	if (m_IsNPC)
	{
		if (HiveMind::IsOverlapping(tempComp->GetDest(), m_pTargetToKill->GetComponent<SpriteComponent>()->GetDest()))
		{
			m_FlyAroundPostDeath = true;
		}
	}
	else { GetGameObject()->SetActive(false); }
	if (m_FlyAroundPostDeath)
	{
		const ColliderBox& collider = GetGameObject()->GetComponent<CharacterColliderComponent>()->GetCollisionResults();
		GetGameObject()->GetComponent<CharacterColliderComponent>()->ResetCollision();

		//float maxYVelocity{ 20.f };

		m_Velocity.x = 60 * float(cos(90 * M_PI / 180));
		m_Velocity.y = 300 * float(sin(90 * M_PI / 180));
		m_flyTimer += elapsedSec * 2;
		m_Velocity.y = (-m_Velocity.y + m_Gravity * m_flyTimer);
		if (collider.bottom && m_Velocity.y > 0)
		{
			m_FlyAroundPostDeath = false;
			m_SpawnPickup = true;
			LevelManager::GetInstance().decreaseEnemyCount(1); //Decrease enemies amount so that if theres only 1 left hes in rage
		}
	
	}
	if (m_SpawnPickup)
	{
		GameObject* pPickup{ new GameObject() };
		if(m_IsMaita)
			pPickup->CreateScorePickup(1, GetTransform()->GetPosition(), m_pTargetToKill);
		else if(m_IsZenChan)
			pPickup->CreateScorePickup(0, GetTransform()->GetPosition(), m_pTargetToKill);

		SceneManager::GetInstance().GetActiveScene()->Add(pPickup);
		GetGameObject()->SetActive(false);

	}
}

void HiveMind::ActorComponent::HandlePlayerDeath(const float& elapsedSec)
{
	if (GetGameObject()->GetComponent<HealthComponent>()->GetHealth() > 0)
	{
		m_RespawnTimer += elapsedSec;
		GetGameObject()->GetComponent<HealthComponent>()->SetInvincibility(true);
		if (m_RespawnTimer >= 3.f)
		{
			GetGameObject()->GetTransform()->SetPosition(FPoint3{ 50, 200,1 });
			m_RespawnTimer = 0;
			Idle();
			GetGameObject()->GetComponent<HealthComponent>()->SetInvincibility(false);

		}
	}
	else
		Notify(Observer::Event::DEATH);
	
		
}


void HiveMind::ActorComponent::MoveLeft()
{
	const ColliderBox& collider = GetGameObject()->GetComponent<CharacterColliderComponent>()->GetCollisionResults();
	
	m_ActorState = ActorState::LEFT;
	m_FaceLeft = true;

		m_Velocity.x -= m_MovementSpeed;
	if (m_Velocity.x <= -m_MaxRunSpeed)
		m_Velocity.x = -m_MaxRunSpeed;

	m_ClipY = 3;
}

void HiveMind::ActorComponent::MoveRight()
{
	const ColliderBox& collider = GetGameObject()->GetComponent<CharacterColliderComponent>()->GetCollisionResults();
	if (collider.right)
	{
		Idle();
		return;
	}
	m_ActorState = ActorState::RIGHT;
	m_FaceLeft = false;
		m_Velocity.x += m_MovementSpeed;
	if (m_Velocity.x >= m_MaxRunSpeed)
		m_Velocity.x = m_MaxRunSpeed;

	m_ClipY = 2;


}

void HiveMind::ActorComponent::Jump()
{
	const ColliderBox& collider = GetGameObject()->GetComponent<CharacterColliderComponent>()->GetCollisionResults();

	if (collider.bottom && !m_IsJumping)
	{
		m_ActorState = ActorState::JUMP;
		m_Velocity.y = -m_JumpSpeed;
		m_IsJumping = true;
	}
	m_ClipY = 2;
	if (m_FaceLeft)
		m_ClipY = 3;
}

void HiveMind::ActorComponent::Death()
{
	m_ActorState = ActorState::DEATH;
	m_ClipY = 4;
	m_Velocity.x = 0;
	m_Velocity.y = 0;
}

void HiveMind::ActorComponent::Idle()
{
	const ColliderBox& collider = GetGameObject()->GetComponent<CharacterColliderComponent>()->GetCollisionResults();
	if (collider.bottom)
		m_ActorState = ActorState::IDLE;
	m_Velocity.x = 0;

	m_ClipY = 2;
	if (m_FaceLeft)
		m_ClipY = 3;
}

void HiveMind::ActorComponent::Shoot()
{
	m_ActorState = ActorState::SHOOT;
	const float cooldown{ 0.5f };
	
	if (m_ShootingTimer >= cooldown)
	{
		SpriteComponent* tempComp = GetGameObject()->GetComponent<SpriteComponent>();
		if (m_FaceLeft)
		{
			if(m_IsPlayer && !m_IsMaita)
				BulletManager::GetInstance().CreateBubbleBullet(FPoint3(GetTransform()->GetPosition().x, GetTransform()->GetPosition().y + tempComp->GetDest().h / 3.f, 0.f), FPoint2(120, 0), 3.f, m_FaceLeft);
			else if (m_IsMaita)
				BulletManager::GetInstance().CreateFireBall(FPoint3(GetTransform()->GetPosition().x, GetTransform()->GetPosition().y + tempComp->GetDest().h / 3.f, 0.f), FPoint2(120, 0), 3.f, m_FaceLeft);

		}
		else
		{
			if (m_IsPlayer && !m_IsMaita)
				BulletManager::GetInstance().CreateBubbleBullet(FPoint3(GetTransform()->GetPosition().x + tempComp->GetDest().w, GetTransform()->GetPosition().y + tempComp->GetDest().h / 3.f, 0.f), FPoint2(120, 0), 3.f, m_FaceLeft);
			else if (m_IsMaita)
				BulletManager::GetInstance().CreateFireBall(FPoint3(GetTransform()->GetPosition().x, GetTransform()->GetPosition().y + tempComp->GetDest().h / 3.f, 0.f), FPoint2(120, 0), 3.f, m_FaceLeft);
		}
		m_ShootingTimer = 0;
		if (GetGameObject()->HasComponent<SoundComponent>())
		{
			GetGameObject()->GetComponent<SoundComponent>()->PlaySoundByName("Shoot");
		}
	}

	m_ClipY = 0;
	if (m_FaceLeft)
		m_ClipY = 1;

	if (m_IsEnemy)
	{
		m_ClipY = 1;
		if (m_FaceLeft)
			m_ClipY = 2;
	}
}

void HiveMind::ActorComponent::Hurt()
{
	m_ActorState = ActorState::HURT;
}
