//#pragma once
//#include "Math.h"
//#include "GameObject.h"
//#include "Components.h"
//#include "Animations.h"
//#include "Primitives.h"
//namespace HiveMind
//{
//
//	class SpriteRenderComponent;
//	class LevelCollisionComponent;
//	class RigidBodyComponent;
//
//
//	class PlayerCharacter final : public GameObject
//	{
//
//	public:
//		
//
//		PlayerCharacter(const SpriteConfig& spriteConfig);
//		virtual ~PlayerCharacter();
//
//		PlayerCharacter(const PlayerCharacter& other) = delete;
//		PlayerCharacter(PlayerCharacter&& other) noexcept = delete;
//		PlayerCharacter& operator=(const PlayerCharacter& other) = delete;
//		PlayerCharacter& operator=(PlayerCharacter&& other) noexcept = delete;
//
//		virtual void Update(const float& elapsedSec) override;
//		//virtual void Render() const override;
//	
//	private:
//		void UpdateMovement(const float& elapsedSec);
//		void UpdateCollision(const float& elapsedSec);
//		void UpdateAnimation(const float& elapsedSec);
//		void UpdateCombat(const float& elapsedSec);
//
//		SpriteComponent* m_pSpriteComponent;
//		ActorComponent* m_pActorComponent;
//		bool m_FaceLeft;
//		SpriteConfig m_SpriteConfig;
//		int m_ClipX;
//		int m_ClipY;
//
//		const float m_MovementSpeed;
//		const float m_JumpSpeed;
//		const float m_Gravity;
//		float m_AnimTime;
//		//const float m_MaxMovementVel;
//		//const float m_MaxJumpVel;
//		//const float m_MaxTerminalVel;
//		float m_AnimFrame;
//		float m_JumpVel;
//		float m_ShootingTimer;
//		RectI m_SourceRect;
//		RectI m_DestRect;
//		Float2 m_Movement;
//		const Float2 m_Scale;
//
//	};
//}