#pragma once
#include "ActorComponent.h"
namespace HiveMind
{
	class PlayerControlComponent final : public ActorComponent
	{
	public:
		PlayerControlComponent();
		virtual ~PlayerControlComponent();

	protected:

		//virtual void Initialize() override;
		virtual void Update(const float& elapsedSec) override;
		//virtual void Render() const override;
	private:
		void UpdateMovement(const float& elapsedSec);

		void UpdateCombat(const float& elapsedSec);
		void UpdateAnimation(const float& elapsedSec);
		void UpdateNPCStates(const float& elapsedSec);

	};
}

