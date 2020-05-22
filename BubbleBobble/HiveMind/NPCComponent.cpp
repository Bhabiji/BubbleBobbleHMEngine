#include "NPCComponent.h"
#include "Components.h"
#include "BulletManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Physics.h"
HiveMind::NPCComponent::NPCComponent()
	:ActorComponent()
	,m_ToTargetCooldown{1.5f}
	, m_flyTimer{}
	,m_SpawnPickup{false}
	
{
}

HiveMind::NPCComponent::~NPCComponent()
{
}

void HiveMind::NPCComponent::SetTarget(GameObject* pGameObject)
{
	m_pTargetToKill = pGameObject;
}

void HiveMind::NPCComponent::Update(const float& elapsedSec)
{
	if (m_ActorState != ActorState::DEATH)
	{
		UpdateNPCStates(elapsedSec);
		UpdateMovement(elapsedSec);
		UpdateCombat(elapsedSec);

		ActorComponent::Update(elapsedSec);
	}
	else
		HandleDeath(elapsedSec);

}

void HiveMind::NPCComponent::UpdateMovement(const float& elapsedSec)
{
	FPoint2 pos{ GetTransform()->GetPosition() };
	float maxYvelocity{ 5.f };

	const ColliderBox& collider = GetGameObject()->GetComponent<CharacterColliderComponent>()->GetCollisionResults();
	GetGameObject()->GetComponent<CharacterColliderComponent>()->ResetCollision();
	if (m_ActorState == ActorComponent::ActorState::IDLE)
	{
		m_Velocity.y = 0;
	}
	if (!collider.left)
	{
		if (m_ActorState == ActorComponent::ActorState::LEFT || m_ActorState == ActorComponent::ActorState::JUMPWHILERUNNING && m_FaceLeft)
		{
			pos.x -= m_MovementSpeed * elapsedSec;
			std::cout << "XPos:" << pos.x << std::endl;
		}

	}
	if (!collider.right)
	{
		if (m_ActorState == ActorComponent::ActorState::RIGHT || m_ActorState == ActorComponent::ActorState::JUMPWHILERUNNING && !m_FaceLeft)
		{
			pos.x += m_MovementSpeed * elapsedSec;
			std::cout << "XPos:" << pos.x << std::endl;
		}
	}
	if (m_IsOnGround)
	{
		if (m_ActorState == ActorComponent::ActorState::JUMP || m_ActorState == ActorComponent::ActorState::JUMPWHILERUNNING)
		{
			if (collider.bottom /*&& m_Movement.y <= 0*/)
			{
				m_JumpVel = 0;
				if (m_ActorState == ActorComponent::ActorState::JUMP) //jump higher to other platform
					m_Velocity.y = -5.f;
				else
					m_Velocity.y -= 2.5f;
				m_IsOnGround = false;

			}
			else if (!collider.bottom)
			{
				m_IsOnGround = true;
			}
			std::cout << "YPos:" << pos.y << std::endl;
		}

		//pos.y += m_Gravity * elapsedSec;
	}
	if (!collider.bottom)
	{
		m_JumpVel = 0.15f;
		m_Velocity.y += m_JumpVel;
		m_IsOnGround = false;


		pos.y += m_Gravity * elapsedSec;
	}
	if (collider.bottom && m_ActorState != ActorComponent::ActorState::JUMP && collider.bottom && m_ActorState != ActorComponent::ActorState::JUMPWHILERUNNING)
	{
		m_IsOnGround = true;
		m_Velocity.y = 0;

	}
	if (collider.bottom && m_Velocity.y > 0)
	{
		m_Velocity.y = 0;
		m_IsOnGround = true;

	}
	if (m_Velocity.y >= maxYvelocity)
		m_Velocity.y = maxYvelocity;
	pos.y += m_Velocity.y;
	GetGameObject()->SetPosition(pos);
}

void HiveMind::NPCComponent::HandleDeath(const float& elapsedSec)
{
	m_AnimTime += elapsedSec;
	SpriteComponent* tempComp = GetGameObject()->GetComponent<SpriteComponent>();
	if (m_AnimTime >= 0.2f)
	{
		int colAmount{ tempComp->GetSpriteConfig().columns };
		int rowAmount{ tempComp->GetSpriteConfig().rows };
		m_ClipY = 4;
		m_ClipX++;
		if (m_ClipX >= colAmount)
			m_ClipX = 0;
		m_AnimTime = 0;
	}
	FPoint2 pos{ GetTransform()->GetPosition() };

	FPoint2 srcPos{ (tempComp->GetCroppedWidth() * m_ClipX),tempComp->GetCroppedHeight() * m_ClipY };
	tempComp->SetLocalSpriteArea(srcPos, pos);
	
	if (HiveMind::IsOverlapping(tempComp->GetDest(), m_pTargetToKill->GetComponent<SpriteComponent>()->GetDest()))
	{
		m_FlyAroundPostDeath = true;
	}
	if (m_FlyAroundPostDeath)
	{
		const ColliderBox& collider = GetGameObject()->GetComponent<CharacterColliderComponent>()->GetCollisionResults();
		GetGameObject()->GetComponent<CharacterColliderComponent>()->ResetCollision();

		//float maxYVelocity{ 20.f };

	    m_Velocity.x = 20 * float(cos(90 * M_PI / 180));
		m_Velocity.y = 70 * float(sin(90 * M_PI / 180));
		m_flyTimer += elapsedSec*2;
		m_Velocity.y = (m_Velocity.y + -9.81f * m_flyTimer);
		if (collider.bottom && m_Velocity.y < -5)
		{
			m_FlyAroundPostDeath = false;
			m_SpawnPickup = true;
		}
		pos.x += m_Velocity.x * elapsedSec;
		pos.y -= m_Velocity.y * elapsedSec;

	}

	GetTransform()->SetPosition(FPoint3(pos.x,pos.y,1));
	if (m_SpawnPickup)
	{
		GameObject* pPickup{ new GameObject() };
		pPickup->CreateScorePickup(0, GetTransform()->GetPosition(), m_pTargetToKill);
		SceneManager::GetInstance().GetActiveScene()->Add(pPickup);
		GetGameObject()->GetComponent<LifeTimeComponent>()->ToggleActive(false);

	}
}

void HiveMind::NPCComponent::UpdateCombat(const float& elapsedSec)
{
	const float cooldown{ 0.5f };
	m_ShootingTimer += elapsedSec;
	if (m_ActorState == ActorComponent::ActorState::SHOOT && m_ShootingTimer >= cooldown)
	{
		SpriteComponent* tempComp = GetGameObject()->GetComponent<SpriteComponent>();
		if (m_FaceLeft)
		{
			BulletManager::GetInstance().CreateBullet(FPoint3(GetTransform()->GetPosition().x, GetTransform()->GetPosition().y + tempComp->GetDest().h / 3.f, 0.f), FPoint2(60, 0), 3.f, m_FaceLeft);
		}
		else
		{
			BulletManager::GetInstance().CreateBullet(FPoint3(GetTransform()->GetPosition().x + tempComp->GetDest().w, GetTransform()->GetPosition().y + tempComp->GetDest().h / 3.f, 0.f), FPoint2(60, 0), 3.f, m_FaceLeft);
		}
		m_ShootingTimer = 0;
	}
}

void HiveMind::NPCComponent::UpdateNPCStates(const float& elapsedSec)
{
	if (m_pTargetToKill)
	{

		const FPoint2& pos{ GetTransform()->GetPosition() };
		const FPoint2& targetPos{ m_pTargetToKill->GetTransform()->GetPosition() };
		const ColliderBox& collider = GetGameObject()->GetComponent<CharacterColliderComponent>()->GetCollisionResults();
		if (collider.left)
			m_FaceLeft = false;
		else if (collider.right)
			m_FaceLeft = true;

		m_ActorState = ActorState::LEFT;
		if (!m_FaceLeft && !collider.right)
			MoveRight();
		if (!collider.rightFoot && !m_FaceLeft)
		{
			if(pos.y > targetPos.y - 5)
			{
				if (pos.x < targetPos.x +1)
					m_ActorState = ActorState::JUMPWHILERUNNING;
				else
					MoveLeft();
			}
		}
		if (!collider.leftFoot && m_FaceLeft)
		{
			if(pos.y > targetPos.y - 5)
			{
				if (pos.x > targetPos.x)
					m_ActorState = ActorState::JUMPWHILERUNNING;
				else
					MoveRight();
			}
		}

		//update compared to target (player) position
		if (pos.y - 2 > targetPos.y && collider.bottom&& m_ToTargetCooldown <= m_ToTargetTimer)
		{
			Jump();
			m_ToTargetTimer = 0;
		}
		m_ToTargetTimer += elapsedSec;
	}
	

}
