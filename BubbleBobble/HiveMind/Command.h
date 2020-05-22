#pragma once
#include <iostream>
#include "Components.h"
namespace HiveMind
{
	class Command
	{
	public:
		Command() = default;
		virtual ~Command() = default;

		Command(const Command& other) = delete;
		Command(Command&& other) noexcept = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) noexcept = delete;

		virtual void Execute(ActorComponent* pActorComp) = 0;
		void SetIdle(ActorComponent* pActorComp)
		{
			pActorComp->Idle();
		}
	};

	class LeftCommand final :public Command
	{
	public:
		virtual void Execute(ActorComponent* pActorComp) override
		{
			std::cout << "Left" << std::endl;
			if (pActorComp->GetActorState() != ActorComponent::ActorState::JUMPWHILERUNNING)
				pActorComp->MoveLeft();
			
		};
	};

	class RightCommand final :public Command
	{
	public:
		virtual void Execute(ActorComponent* pActorComp) override
		{
			std::cout << "Right" << std::endl;
			if (pActorComp->GetActorState() != ActorComponent::ActorState::JUMPWHILERUNNING)
				pActorComp->MoveRight();
			
		};
	};

	class JumpCommand final :public Command
	{
	public:
		virtual void Execute(ActorComponent* pActorComp) override
		{
			std::cout << "Jump" << std::endl;
			if(pActorComp->GetActorState() == ActorComponent::ActorState::IDLE)
				pActorComp->Jump();
			else if (pActorComp->GetActorState() == ActorComponent::ActorState::LEFT)
				pActorComp->JumpWhileRunning(true);
			else if (pActorComp->GetActorState() == ActorComponent::ActorState::RIGHT)
				pActorComp->JumpWhileRunning(false);

		};
	};

	class IdleCommand final :public Command
	{
	public:
		virtual void Execute(ActorComponent* pActorComp) override
		{
			std::cout << "Idle" << std::endl;
			pActorComp->Idle();
		};
	};
	class ShootCommand final : public Command
	{
	public:
		virtual void Execute(ActorComponent* pActorComp) override
		{
			std::cout << "Shooting" << std::endl;
			if (pActorComp->GetActorState() == ActorComponent::ActorState::IDLE)
				pActorComp->Shoot();
			else if (pActorComp->GetActorState() == ActorComponent::ActorState::LEFT)
				pActorComp->ShootWhileRunning(true);
			else if (pActorComp->GetActorState() == ActorComponent::ActorState::RIGHT)
				pActorComp->ShootWhileRunning(false);
		}
	};

}