#pragma once

namespace HiveMind {
	class GameObject;
	class TransformComponent;
	class BaseComponent
	{
	public:
		friend class GameObject;
		BaseComponent();
		virtual ~BaseComponent();
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(const BaseComponent&& other) = delete;
		HiveMind::TransformComponent* GetTransform() const;
		GameObject* GetGameObject() const { return m_pGameObject; }
		bool IsInitialized() const;
	protected:
		GameObject* m_pGameObject;
		virtual void Initialize() = 0;
		virtual void Update(const float& deltaTime) = 0;
		virtual void Render() const = 0;
		bool m_IsInitialized;
	private:
	};
}

