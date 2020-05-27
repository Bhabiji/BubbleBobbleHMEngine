#include "ProjectileComponent.h"
#include "GameObject.h"
#include "Components.h"
#include "SceneManager.h"
#include "Scene.h"
HiveMind::ProjectileComponent::ProjectileComponent(const bool isLookingLeft, const FPoint3& pos, const FVector2& velocity, ProjectileState kindOfProjectile)
	:m_LookingLeft{isLookingLeft}
	,m_Velocity{velocity}
	, m_FrameX{}
	, m_FrameY{}
	,m_Pos{pos}
	,m_ProjState{kindOfProjectile}
{
	
}

HiveMind::ProjectileComponent::~ProjectileComponent()
{
}

void HiveMind::ProjectileComponent::Initialize()
{
	m_IsInitialized = true;
	GetGameObject()->GetTransform()->SetPosition(m_Pos);
}

void HiveMind::ProjectileComponent::Update(const float& elapsedSec)
{
	UpdateMovement(elapsedSec);
	UpdateCollision(elapsedSec);
}

void HiveMind::ProjectileComponent::Render() const
{

}


void HiveMind::ProjectileComponent::UpdateMovement(const float& elapsedSec)
{
	FPoint3 newPos{ GetGameObject()->GetTransform()->GetPosition() };
	if (m_LookingLeft)
		newPos.x -= m_Velocity.x * elapsedSec;
	else
		newPos.x += m_Velocity.x * elapsedSec;

	newPos.y += m_Velocity.y * elapsedSec;

	GetGameObject()->GetTransform()->SetPosition(newPos);

}

void HiveMind::ProjectileComponent::UpdateCollision(const float& elapsedSec)
{
	GetTransform();
	auto scene = SceneManager::GetInstance().GetActiveScene();
	for (auto& object : scene->GetObjects())
	{
		if(m_ProjState == ProjectileState::BUBBLE)
		{
			if (object->HasComponent<ActorComponent>() && object->GetComponent<ActorComponent>()->IsNPC() && object->HasComponent<HealthComponent>())
			{
				if (HiveMind::IsOverlapping(GetGameObject()->GetTransform()->GetPosition(), object->GetComponent<SpriteComponent>()->GetDest()) && object->GetComponent<ActorComponent>()->GetActorState() != ActorComponent::ActorState::DEATH)
				{
					object->GetComponent<HealthComponent>()->DecreaseHealth(1);
					GetGameObject()->SetActive(false);
				}
			}
		}
		else if (m_ProjState == ProjectileState::FIREBALL)
		{
			if (object->HasComponent<ActorComponent>() && !object->GetComponent<ActorComponent>()->IsNPC() && object->HasComponent<HealthComponent>())
			{
				if (HiveMind::IsOverlapping(GetGameObject()->GetTransform()->GetPosition(), object->GetComponent<SpriteComponent>()->GetDest()) && object->GetComponent<ActorComponent>()->GetActorState() != ActorComponent::ActorState::DEATH)
				{
					object->GetComponent<HealthComponent>()->DecreaseHealth(1);
					GetGameObject()->SetActive(false);
				}
			}
		}
			
	}
}
