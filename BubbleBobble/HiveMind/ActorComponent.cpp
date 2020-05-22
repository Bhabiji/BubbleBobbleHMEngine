#include "HiveMindPCH.h"
#include "Components.h"
#include "Observer.h"
#include "PlayerCharacter.h"
#include "BulletManager.h"
#include "InputManager.h"
HiveMind::ActorComponent::ActorComponent()
	:m_ActorState{ ActorState::IDLE }
	, m_MovementSpeed{ 100.f }
	, m_Velocity{}
	, m_JumpSpeed{ 100 }
	, m_JumpVel{}
	, m_Gravity{ 9.81f }
	, m_FaceLeft{ false }
	, m_IsOnGround{ false }
	, m_ClipX{ 0 }
	, m_ClipY{ 0 }
	, m_AnimFrame{ 0 }
	, m_AnimTime{ 0 }
{
}

HiveMind::ActorComponent::~ActorComponent()
{
	for (auto* pObserver : m_pObservers) 
	{ delete pObserver; };
}

void HiveMind::ActorComponent::AddObserver(Observer* pObserver)
{
	m_pObservers[m_CurrentNrObservers] = pObserver;
	m_CurrentNrObservers++;
}

void HiveMind::ActorComponent::Notify(GameObject* pSubject, Observer::Event event)
{
	UNREFERENCED_PARAMETER(pSubject);
	for (unsigned int i{}; i < m_CurrentNrObservers; ++i)
	{
		m_pObservers[i]->OnNotify(GetGameObject(), event);
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
	
	//	auto& input = InputManager::GetInstance();
	//	input.HandleInput(this);
	//
	//
	//	UpdateNPCStates(elapsedSec);

	//UpdateMovement(elapsedSec);
	//UpdateCombat(elapsedSec);
	UpdateAnimation(elapsedSec);
}

void HiveMind::ActorComponent::Render() const
{
}

void HiveMind::ActorComponent::UpdateMovement(const float& elapsedSec)
{
	FPoint2 pos{ GetTransform()->GetPosition() };

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
	if ( !collider.right)
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
	pos.y += m_Velocity.y;
	GetGameObject()->SetPosition(pos);
}

void HiveMind::ActorComponent::UpdateCombat(const float& elapsedSec)
{
	
}

void HiveMind::ActorComponent::UpdateAnimation(const float& elapsedSec)
{
	m_AnimTime += elapsedSec;
	SpriteComponent* tempComp = GetGameObject()->GetComponent<SpriteComponent>();
	if (m_AnimTime >= 0.2f)
	{
		int colAmount{ tempComp->GetSpriteConfig().columns };
		int rowAmount{ tempComp->GetSpriteConfig().rows };
		if (m_ActorState == ActorComponent::ActorState::IDLE)
		{
			m_ClipY = 2;
			if (m_FaceLeft)
				m_ClipY = 3;
		}
		else if (m_ActorState == ActorComponent::ActorState::LEFT)
		{
			m_ClipY = 3;
			++m_ClipX;
		}
		else if (m_ActorState == ActorComponent::ActorState::RIGHT)
		{
			m_ClipY = 2;
			++m_ClipX;
		}
		else if (m_ActorState == ActorComponent::ActorState::SHOOT || m_ActorState == ActorComponent::ActorState::SHOOTWHILERUNNING)
		{
			m_ClipY = 0;
			if (m_FaceLeft)
				m_ClipY = 1;
		}
		if (m_ActorState == ActorComponent::ActorState::JUMP || m_ActorState == ActorComponent::ActorState::JUMPWHILERUNNING)
		{
			m_ClipY = 2;
			if (m_FaceLeft)
				m_ClipY = 3;
		}

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
	

}


void HiveMind::ActorComponent::MoveLeft()
{
		m_ActorState = ActorState::LEFT;
		m_FaceLeft = true;
}

void HiveMind::ActorComponent::MoveRight()
{

		m_ActorState = ActorState::RIGHT;
		m_FaceLeft = false;
}

void HiveMind::ActorComponent::Jump()
{
	if (m_IsOnGround)
		m_ActorState = ActorState::JUMP;
}

void HiveMind::ActorComponent::JumpWhileRunning(const bool faceLeft)
{
	m_FaceLeft = faceLeft;
	m_ActorState = ActorState::JUMPWHILERUNNING;
}

void HiveMind::ActorComponent::ShootWhileRunning(const bool faceLeft)
{
	m_FaceLeft = faceLeft;
	m_ActorState = ActorState::SHOOTWHILERUNNING;
}

void HiveMind::ActorComponent::Death()
{
	m_ActorState = ActorState::DEATH;
}

void HiveMind::ActorComponent::Idle()
{
	const ColliderBox& collider = GetGameObject()->GetComponent<CharacterColliderComponent>()->GetCollisionResults();
	if (collider.bottom)
		m_ActorState = ActorState::IDLE;
}

void HiveMind::ActorComponent::Shoot()
{
	m_ActorState = ActorState::SHOOT;
}
