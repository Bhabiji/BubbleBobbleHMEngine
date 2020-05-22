//#pragma once
//#include "GameObject.h"
//namespace HiveMind 
//{
//	class Bullet :
//		public GameObject
//	{
//	public:
//		Bullet(const bool isLookingLeft, const FPoint2& pos, const FPoint2& velocity, const float lifeTime);
//		virtual ~Bullet() = default;
//
//		Bullet(const Bullet& other) = delete;
//		Bullet(Bullet&& other) noexcept = delete;
//		Bullet& operator=(const Bullet& other) = delete;
//		Bullet& operator=(Bullet&& other) noexcept = delete;
//
//		virtual void Initialize() override;
//		virtual void Update(const float& elapsedSec) override;
//		virtual void Render() const override;
//
//		float GetLifeTime() const;
//	private:
//		bool m_FadeOut;
//		bool m_LookingLeft;
//		unsigned int m_ClipX, m_ClipY;
//		float m_LifeTime;
//		FVector2 m_Velocity;
//		float m_AnimTime;
//
//		FVector2 m_Movement;
//	};
//}
//
