#include "PlayerControlComponent.h"
#include "Components.h"
#include "BulletManager.h"
#include "InputManager.h"
HiveMind::PlayerControlComponent::PlayerControlComponent()
	:ActorComponent()
{
}
HiveMind::PlayerControlComponent::~PlayerControlComponent()
{
}
void HiveMind::PlayerControlComponent::Update(const float& elapsedSec)
{
	auto& input = InputManager::GetInstance();
	input.HandleInput(this);

	UpdateMovement(elapsedSec);
	UpdateCombat(elapsedSec);
	UpdateAnimation(elapsedSec);
	ActorComponent::Update(elapsedSec);
}

void HiveMind::PlayerControlComponent::UpdateMovement(const float& elapsedSec)
{
	FPoint2 pos{ GetTransform()->GetPosition() };
	float yGlidingTrigger{ 5.f };
	const ColliderBox& collider = GetGameObject()->GetComponent<CharacterColliderComponent>()->GetCollisionResults();
	GetGameObject()->GetComponent<CharacterColliderComponent>()->ResetCollision();
	if (m_ActorState == ActorComponent::ActorState::IDLE && !collider.top)
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
				m_Velocity.y = -5;
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
	if (collider.bottom && m_ActorState != ActorComponent::ActorState::JUMP && collider.bottom && m_ActorState != ActorComponent::ActorState::JUMPWHILERUNNING && !collider.top)
	{
		m_IsOnGround = true;
		m_Velocity.y = 0;
	}
	if (collider.bottom && m_Velocity.y > 0 && !collider.top)
	{
		m_Velocity.y = 0;
		m_IsOnGround = true;

	}
	if (m_Velocity.y >= yGlidingTrigger)
		m_Velocity.y = yGlidingTrigger;
	pos.y += m_Velocity.y;
	GetGameObject()->SetPosition(pos);
}

void HiveMind::PlayerControlComponent::UpdateCombat(const float& elapsedSec)
{
	const float cooldown{ 0.5f };
	m_ShootingTimer += elapsedSec;
	if( m_ShootingTimer >= cooldown)
	{
		if (m_ActorState == ActorComponent::ActorState::SHOOT || m_ActorState == ActorComponent::ActorState::SHOOTWHILERUNNING)
		{

			SpriteComponent* tempComp = GetGameObject()->GetComponent<SpriteComponent>();
			if (m_FaceLeft)
			{
				BulletManager::GetInstance().CreateBullet(FPoint3(GetTransform()->GetPosition().x, GetTransform()->GetPosition().y + tempComp->GetDest().h / 3.f, 0.f), FPoint2(120, 0), 3.f, m_FaceLeft);
			}
			else
			{
				BulletManager::GetInstance().CreateBullet(FPoint3(GetTransform()->GetPosition().x + tempComp->GetDest().w, GetTransform()->GetPosition().y + tempComp->GetDest().h / 3.f, 0.f), FPoint2(120, 0), 3.f, m_FaceLeft);
			}
			m_ShootingTimer = 0;
		}
	}
}

void HiveMind::PlayerControlComponent::UpdateAnimation(const float& elapsedSec)
{
}

void HiveMind::PlayerControlComponent::UpdateNPCStates(const float& elapsedSec)
{
}
