#pragma once
#include "SceneManager.h"
#include "GameObject.h"

namespace HiveMind
{

	class Scene
	{
		friend Scene* SceneManager::CreateScene(const std::string& name);
	public:
		void Add(GameObject* object);

		void Initialize();
		void BindEnemiesAndTarget();

		void Update(const float& deltaTime);
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		std::string GetName() const;
		bool IsActive() const;
		void SetActive(const bool toggle);
		void Remove(GameObject* gameObject);
		void DeleteInactives();
		void Reset();
		std::vector<GameObject*> GetObjects() const;
		explicit Scene(const std::string& name);
	private: 

		std::string m_Name;
		std::vector <GameObject*> m_Objects{};
		bool m_IsActive;
		static unsigned int m_IdCounter; 
	};

}
