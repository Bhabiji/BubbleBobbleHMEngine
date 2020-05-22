#pragma once
#include "ActorComponent.h"
#include "Math.h"
namespace HiveMind {

class Observer;
	class NPCComponent : public ActorComponent
	{
	public:
		NPCComponent();
		virtual ~NPCComponent();
		void SetTarget(GameObject* pGameObject);

	protected:
		//virtual void Initialize() override;
		virtual void Update(const float& elapsedSec) override;
		//virtual void Render() const override;
	private:
		void UpdateMovement(const float& elapsedSec);
		void HandleDeath(const float& elapsedSec);
		void UpdateCombat(const float& elapsedSec);
		void UpdateNPCStates(const float& elapsedSec);
		GameObject* m_pTargetToKill;
		float m_ToTargetTimer;
		float m_ToTargetCooldown;
		float m_flyTimer;
		bool m_FlyAroundPostDeath;
		bool m_SpawnPickup;
	};


}