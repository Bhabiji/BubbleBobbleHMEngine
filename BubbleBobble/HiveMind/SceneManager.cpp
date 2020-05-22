#include "HiveMindPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void HiveMind::SceneManager::Initialize()
{
	for (auto& scene : m_Scenes)
		scene->Initialize();
}

void HiveMind::SceneManager::PostInitialize()
{
	for (auto& scene : m_Scenes)
		scene->PostInitialize();
}

void HiveMind::SceneManager::Update(const float& deltaTime)
{
	for(auto& scene : m_Scenes)
	{
		if (scene->IsActive())
			scene->Update(deltaTime);
	}
}

void HiveMind::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		if(scene->IsActive())
			scene->Render();
	}
}

HiveMind::SceneManager::~SceneManager()
{
	for (Scene* scene : m_Scenes)
	{
		delete scene;
		scene = nullptr;
	}
}

HiveMind::Scene* HiveMind::SceneManager::CreateScene(const std::string& name)
{
	Scene* scene = new Scene(name);

	m_Scenes.push_back(scene);
	return scene;
}

HiveMind::Scene* HiveMind::SceneManager::GetScene(const std::string& sceneName) const
{
	// TODO: insert return statement here
	for (Scene* scene : m_Scenes)
	{
		if (scene->GetName() == sceneName)
			return scene;
	}
	throw(sceneName + " Not found give a valid scene");
}

HiveMind::Scene* HiveMind::SceneManager::GetActiveScene() const
{
	// TODO: insert return statement here
	for (Scene* scene : m_Scenes)
	{
		if (scene->IsActive())
			return scene;
	}
	throw("No Active Scene found");

}


void HiveMind::SceneManager::SetSceneActive(const std::string& sceneName, const bool toggle)
{
	bool newActiveScene{false};
	for (Scene* scene : m_Scenes)
	{
		if (scene->GetName() == sceneName)
		{
			scene->SetActive(toggle);
			newActiveScene = true;
		}
	}
	//now that a new scene is active we can disable the previously active scene to save computations
	if(newActiveScene)
		for (Scene* scene : m_Scenes)
		{
			if (scene->IsActive() && sceneName != scene->GetName())
				scene->SetActive(false);
		}
}

void HiveMind::SceneManager::DeleteInactives()
{
	for (Scene* scene : m_Scenes)
	{
		if (scene->IsActive())
			scene->DeleteInactives();;
	}
}
