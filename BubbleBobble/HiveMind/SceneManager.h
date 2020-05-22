#pragma once
#include "Singleton.h"
#include <iostream>
#include <string>
namespace HiveMind
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		virtual ~SceneManager();
		Scene* CreateScene(const std::string& name);
		Scene* GetScene(const std::string& name) const;
		Scene* GetActiveScene() const;

		void SetSceneActive(const std::string& sceneName, const bool toggle);
		void DeleteInactives();
		void Initialize();
		void PostInitialize();

		void Update(const float& deltaTime);
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<Scene*> m_Scenes;
	};
}
