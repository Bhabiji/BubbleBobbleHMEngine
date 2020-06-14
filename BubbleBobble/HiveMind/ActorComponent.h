#pragma once
#include "BaseComponent.h"
#include "Observer.h"


namespace HiveMind
{
	class Observer;

	class ActorComponent : public BaseComponent
	{
	public:
		enum class ActorState
		{
			LEFT, RIGHT, IDLE, JUMP, SHOOT, JUMPWHILERUNNING, SHOOTWHILERUNNING, DEATH, FLYINGAWAY, HURT
		};
		ActorComponent(const bool isPlayer, const bool isMaita, const bool isZenChan, const float& maxMoveSpeed);
		~ActorComponent();
		ActorState GetActorState() const;
		FVector2 GetVelocity() const;

		void MoveLeft();
		void MoveRight();
		void Jump();
		void Death();
		void Idle();
		void Shoot();
		void Hurt();
		virtual bool IsNPC();
		virtual bool IsEnemy();

		void SetTarget(GameObject* pGameObject);

		//Observer poattern
		void AddObserver(Observer* pObserver);
		void Notify(Observer::Event event);


	protected:

		virtual void Initialize() override;
		virtual void Update(const float& deltaTime) override;
		virtual void Render() const override;
	private:

		static const unsigned int MAX_OBSERVERS = 10;
		unsigned int m_CurrentNrObservers = 0;

		Observer* m_pObservers[MAX_OBSERVERS]{};


		void UpdateMovement(const float& elapsedSec);

		void UpdateCombat(const float& elapsedSec);
		void UpdateAnimation(const float& elapsedSec);
		void UpdateNPCStates(const float& elapsedSec);
		void HandleNPCDeath(const float& elapsedSec);
		void HandlePlayerDeath(const float& elapsedSec);

		float m_RespawnTimer;

		ActorState m_ActorState;
		bool m_FaceLeft;
		bool m_IsOnGround;
		bool m_IsEnemy;
		int m_ClipX;
		int m_ClipY;
		int m_AnimFrame;
		float m_AnimTime;
		float m_JumpVel;
		float m_MaxFallSpeed;
		float m_MovementSpeed;
		float m_Gravity;
		float m_JumpSpeed;
		float m_ShootingTimer;
		float m_MaxRunSpeed;
		float m_Counter;
		Float2 m_Velocity;
		GameObject* m_pTargetToKill;

		float m_ToTargetTimer;
		float m_ToTargetCooldown;
		float m_flyTimer;
		bool m_IsJumping;
		bool m_FlyAroundPostDeath;
		bool m_SpawnPickup;

		bool m_IsMaita;
		bool m_IsPlayer;
		bool m_IsZenChan;
		bool m_IsNPC;
	};
}

