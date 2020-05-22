#pragma once
#include "BaseComponent.h"
#include "Math.h"
namespace HiveMind 
{
	class TransformComponent : public BaseComponent
	{
	public:
		TransformComponent();
		virtual ~TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;

		void SetPosition(float x, float y, float z);
		void SetPosition(const FPoint3& pos);
		FPoint3 GetPosition() const;
	protected:
		void Update(const float& deltaTime);
		void Render() const;
		void Initialize();
	private:
		FPoint3 m_Position;
	};
}

