#include "HiveMindPCH.h"
#include "Components.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "BulletManager.h"
#include "LevelManager.h"
#include "Renderer.h"
#include "Scene.h"
#include "BubbleBobble.h"
#include "Command.h"
#include <chrono>
#include <thread>
#include "SoundManager.h"
using namespace std;
using namespace std::chrono;

void HiveMind::BubbleBobble::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	HiveMind::Renderer::GetInstance().Init(m_Window);
	HiveMind::SoundManager::GetInstance().Initialize();
}

/**
 * Code constructing the scene world starts here
 */
void HiveMind::BubbleBobble::LoadGame() const
{
	auto go = new GameObject();
	auto scene = SceneManager::GetInstance().CreateScene("MainMenu");
	scene->SetActive(true);
	GameObject* pButton = new GameObject();
	pButton->CreateButton(FPoint3{ 285,200,0 }, Int2{ 70,40 }, "Play", ButtonComponent::Action::LOADSINGLEPLAYERSCENE,"SinglePlayerGame", ResourceManager::GetInstance().LoadFont("pixelated.ttf", 30));
	scene->Add(pButton);

	pButton = new GameObject();
	pButton->CreateButton(FPoint3{ 285,280,0 }, Int2{ 70,40 }, "Play 2", ButtonComponent::Action::LOADMULTIPLAYERSCENE, "MultiPlayerGame", ResourceManager::GetInstance().LoadFont("pixelated.ttf", 30));
	scene->Add(pButton);
	//LOGO
	go->AddComponent(new RenderComponent());
	go->SetTexture("BubbleBobble.png", "BubbleBobble");
	go->SetPosition(FPoint2{ 216, 50 });
	scene->Add(go);
	
	//GameOver
	auto gameOverScene = SceneManager::GetInstance().CreateScene("GameOver");
	pButton = new GameObject();
	pButton->CreateButton(FPoint3{ 285,380,0 }, Int2{ 150,40 }, "Main Menu",ButtonComponent::Action::DESTROYSINGLEPLAYERSCENE, "MainMenu", ResourceManager::GetInstance().LoadFont("pixelated.ttf", 30));
	go = new GameObject();
	go->AddComponent(new TextComponent("Game Over", ResourceManager::GetInstance().LoadFont("pixelated.ttf", 30)));
	go->GetTransform()->SetPosition(285, 150, 0);
	gameOverScene->Add(pButton);
	gameOverScene->Add(go);
	gameOverScene->SetActive(false);

	SceneManager::GetInstance().CreateScene("SinglePlayerGame");
	SceneManager::GetInstance().CreateScene("MultiPlayerGame");


	SceneManager::GetInstance().Initialize();
	SceneManager::GetInstance().PostInitialize();

}

void HiveMind::BubbleBobble::LoadGameScene() const
{
}

void HiveMind::BubbleBobble::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SceneManager::GetInstance().Destroy();
	LevelManager::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void HiveMind::BubbleBobble::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& soundManager = SoundManager::GetInstance();

		//COMMANDS
		
		float levelTransitionTimer{0};
		float updatePauseTimer{ 0 };
		bool pausePhysics{ false };
		bool doContinue = true;
		while (doContinue)
		{
			//To quit game
			SDL_Event e;
			while (SDL_PollEvent(&e))
			{
				switch (e.type)
				{
				case SDL_QUIT:
					doContinue = false;
					break;
				case SDL_KEYUP:
					break;
				}
			}
			const auto currentTime = high_resolution_clock::now();

			/*doContinue = input.ProcessInput();*/
			if (!pausePhysics)
			{
				sceneManager.Update(m_DeltaTime);
			}
			if (pausePhysics)
			{
				updatePauseTimer += m_DeltaTime;
				if (updatePauseTimer >= 2.f)
				{
					pausePhysics = false;
					updatePauseTimer = 0;
				}
			}

			soundManager.Update();
			sceneManager.DeleteInactives(); //delete obsolete objects
			if (SceneManager::GetInstance().GetActiveScene()->GetName() == "SinglePlayerGame" || SceneManager::GetInstance().GetActiveScene()->GetName() == "MultiPlayerGame")
			{
				if(LevelManager::GetInstance().GetEnemyCount() == 0)
				{
					levelTransitionTimer += m_DeltaTime;
					if(levelTransitionTimer >= 5.f )//If enemies are dead still give 5 seconds to pick up remaining potential pickups
					{
						LevelManager::GetInstance().LoadNextLevel();
						sceneManager.GetActiveScene()->BindEnemiesAndTarget();
						levelTransitionTimer = 0;
						pausePhysics = true;
					}
				}
			}
			renderer.Render();
			auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);

			const auto end = std::chrono::high_resolution_clock::now();
			m_DeltaTime = float(std::chrono::duration_cast<std::chrono::microseconds>(end - currentTime).count());
			m_DeltaTime *= powf(10, -6);//conversion to seconds
		}
	}

	Cleanup();
}
