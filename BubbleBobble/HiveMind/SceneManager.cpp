#include "HiveMindPCH.h"
#include "SceneManager.h"
#include "Components.h"
#include "LevelManager.h"

#include "Scene.h"

void HiveMind::SceneManager::Initialize()
{
	for (auto& scene : m_Scenes)
		scene->Initialize();
}

void HiveMind::SceneManager::PostInitialize()
{
	for (auto& scene : m_Scenes)
		scene->BindEnemiesAndTarget();
}

void HiveMind::SceneManager::Destroy()
{
	for (size_t i{}; i < m_Scenes.size(); i++)
	{
		delete m_Scenes[i];
		m_Scenes[i] = nullptr;
	}
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
		if (scene->IsActive())
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

void HiveMind::SceneManager::LoadGameScene()
{
	auto gameScene = GetScene("SinglePlayerGame");


	auto& levels = LevelManager::GetInstance();
	levels.AddLevel(L"../Data/level1.txt", gameScene);
	GameObject* music = new GameObject();
	SoundComponent* pSoundComp{ new SoundComponent() };
	pSoundComp->AddSound("Theme", "../Data/Theme.wav", true);
	music->AddComponent(pSoundComp);
	gameScene->Add(music);
	pSoundComp->PlaySoundByName("Theme");

	//Collision Left
	GameObject* pArenaCollisionLeft{ new GameObject() };
	FPoint2 pos{ 0,-100 };
	Float2 size{ 30,600 };
	pArenaCollisionLeft->CreateCollision(pos, size);

	//Collision Right
	GameObject* pArenaCollisionRight{ new GameObject() };
	pos = FPoint2{ 480,-100 };
	size = Float2{ 30,600 };
	pArenaCollisionRight->CreateCollision(pos, size);

	gameScene->Add(pArenaCollisionLeft);
	gameScene->Add(pArenaCollisionRight);

	GameObject* pPlayer = new GameObject();
	pPlayer->CreatePlayer(SpriteConfig{ 8, 5 });
	gameScene->Add(pPlayer);
	GetActiveScene()->SetActive(false);
	gameScene->SetActive(true);
	gameScene->Initialize();
	PostInitialize();

}

void HiveMind::SceneManager::LoadMultiPlayerGameScene()
{
	auto gameScene = GetScene("MultiPlayerGame");


	auto& levels = LevelManager::GetInstance();
	levels.AddLevel(L"../Data/level1.txt", gameScene);
	GameObject* music = new GameObject();
	SoundComponent* pSoundComp{ new SoundComponent() };
	pSoundComp->AddSound("Theme", "../Data/Theme.wav", true);
	music->AddComponent(pSoundComp);
	gameScene->Add(music);
	pSoundComp->PlaySoundByName("Theme");

	//Collision Left
	GameObject* pArenaCollisionLeft{ new GameObject() };
	FPoint2 pos{ 0,-100 };
	Float2 size{ 30,600 };
	pArenaCollisionLeft->CreateCollision(pos, size);

	//Collision Right
	GameObject* pArenaCollisionRight{ new GameObject() };
	pos = FPoint2{ 480,-100 };
	size = Float2{ 30,600 };
	pArenaCollisionRight->CreateCollision(pos, size);

	gameScene->Add(pArenaCollisionLeft);
	gameScene->Add(pArenaCollisionRight);

	GameObject* pPlayer = new GameObject();
	pPlayer->CreatePlayer(SpriteConfig{ 8, 5 });
	gameScene->Add(pPlayer);

	GameObject* pZenChanPlayer = new GameObject();
	FPoint3 enemyPos{ 4,2,0 };
	pZenChanPlayer->CreateMaitaPlayer(enemyPos);
	gameScene->Add(pZenChanPlayer);

	GetActiveScene()->SetActive(false);
	gameScene->SetActive(true);
	gameScene->Initialize();
	PostInitialize();
}

void HiveMind::SceneManager::ResetScene(const std::string& sceneName)
{
	for (Scene* scene : m_Scenes)
	{
		if (scene->GetName() == sceneName)
		{
			scene->Reset();
		}

	}
}

//Toggle == to set scene active or not
void HiveMind::SceneManager::SetSceneActive(const std::string& sceneName, const bool toggle)
{
	bool newActiveScene{false};
	for (Scene* scene : m_Scenes)
	{
		if (scene->GetName() == sceneName)
		{
			scene->SetActive(toggle);
			if(toggle)
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
