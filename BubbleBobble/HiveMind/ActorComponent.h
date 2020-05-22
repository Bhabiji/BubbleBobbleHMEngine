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
			LEFT, RIGHT, IDLE, JUMP, SHOOT, JUMPWHILERUNNING, SHOOTWHILERUNNING, DEATH, FLYINGAWAY
		};
		ActorComponent();
		~ActorComponent();
		void AddObserver(Observer* pObserver);
		void Notify(GameObject* pSubject, Observer::Event event);
		ActorState GetActorState() const;
		FVector2 GetVelocity() const;
		void MoveLeft();
		void MoveRight();
		void Jump();
		void JumpWhileRunning(const bool faceLeft);
		void ShootWhileRunning(const bool faceLeft);
		void Death();



		void Idle();
		void Shoot();


	protected:
		ActorState m_ActorState;
		bool m_FaceLeft;
		bool m_IsOnGround;
		int m_ClipX;
		int m_ClipY;
		int m_AnimFrame;
		float m_AnimTime;
		float m_JumpVel;
		float m_MovementSpeed;
		float m_Gravity;
		float m_JumpSpeed;
		float m_ShootingTimer;
		Float2 m_Velocity;

		virtual void Initialize() override;
		virtual void Update(const float& deltaTime) override;
		virtual void Render() const override;
	private:
		void UpdateMovement(const float& elapsedSec);

		void UpdateCombat(const float& elapsedSec);
		void UpdateAnimation(const float& elapsedSec);
		void UpdateNPCStates(const float& elapsedSec);

		static const unsigned int MAX_OBSERVERS = 10;
		unsigned int m_CurrentNrObservers = 0;

		Observer* m_pObservers[MAX_OBSERVERS];
	};
}

