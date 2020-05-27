#pragma once
#include <typeinfo>
#include <string>
#include <vector>
#include <iostream>
#include "Math.h"
#include "Animations.h"
namespace HiveMind
{
	class PlayerControlComponent;
	class TransformComponent;
	class BaseComponent;
	class Texture2D;
	class GameObject final
	{
	public:
		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		virtual void Initialize();
		virtual void Update(const float& deltaTime) ;
		virtual void Render() const ;
		virtual bool IsOnGround() const;

		//LEVEL
		void CreateLevelBlock(const int& blockData, FPoint3& pos);
		void CreateLevelBlockNoCollision(const int& blockData, FPoint3& pos);
		void CreateBlob(const bool isLookingLeft, const FPoint3& pos, const FPoint2& velocity, const float lifeTime);
		void CreatePlayer(const SpriteConfig& spriteConfig);
		void CreateMaita();
		void CreateMaita(FPoint3& pos);
		void CreateScorePickup(const int& whichPickup, const FPoint3& pos, std::vector<GameObject*> pPlayerVec);
		void CreateScorePickup(const int& whichPickup, const FPoint3& pos, GameObject* pPlayer);
		void CreateFireBall(const bool isLookingLeft, const FPoint3& pos, const FPoint2& velocity, const float lifeTime);
		bool IsActive() const;
		bool SetActive(const bool active);

		void SetTexture(const std::string& filename, const std::string& texName);
		void SetPosition(const FPoint2& pos);
		void AddComponent(BaseComponent* pComponent);
		TransformComponent* GetTransform() const;
		template <typename T>
		bool HasComponent() const
		{
			return GetComponent<T>() != nullptr;
		}
		template <typename T>
		T* GetComponent() const
		{
			//TypeInfo to compare passed type for templated function with the types in component vector (to find the correct type)
			for (BaseComponent* component : m_pComponents)
			{
				const type_info& ti = typeid(T);

				if (component && typeid(*component) == ti)
					return (T*)component;
			}
			return nullptr;
		}
	protected:
		bool m_IsOnGround;

	private:
		TransformComponent* m_pTransform;
		std::vector<BaseComponent*> m_pComponents;
		bool m_IsActive;
		
	};
}
