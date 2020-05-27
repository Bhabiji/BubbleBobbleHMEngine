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

	class LeftCommand final : public Command
	{
	public:
		virtual void Execute(ActorComponent* pActorComp) override
		{
			std::cout << "Left" << std::endl;
			pActorComp->MoveLeft();
			
		};
	};

	class RightCommand final : public Command
	{
	public:
		virtual void Execute(ActorComponent* pActorComp) override
		{
			std::cout << "Right" << std::endl;
				pActorComp->MoveRight();
			
		};
	};

	class JumpCommand final : public Command
	{
	public:
		virtual void Execute(ActorComponent* pActorComp) override
		{
			std::cout << "Jump" << std::endl;
			pActorComp->Jump();


		};
	};

	class IdleCommand final : public Command
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
				pActorComp->Shoot();

		}
	};

}