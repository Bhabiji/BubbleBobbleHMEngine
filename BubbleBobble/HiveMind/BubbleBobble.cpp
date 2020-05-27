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
}

/**
 * Code constructing the scene world starts here
 */
void HiveMind::BubbleBobble::LoadGame() const
{
	auto scene = SceneManager::GetInstance().CreateScene("Demo");
	scene->SetActive(true);

	auto go = new GameObject();
	go->AddComponent(new RenderComponent());
	go->SetTexture("background.jpg", "Background");
	scene->Add(go);

	go = new GameObject();
	go->AddComponent(new RenderComponent());
	go->SetTexture("logo.png", "Logo");
	go->SetPosition(FPoint2{ 216, 180 });
	scene->Add(go);

	//auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//go = new GameObject();
	//go->AddComponent(new TextComponent("Programming4 assignment", font));
	//go->GetTransform()->SetPosition(80,20,0);
	//scene->Add(go);

	//go = new GameObject();
	//go->AddComponent(new RenderComponent());

	//go->AddComponent(new TextComponent("FPS:", font));
	//go->GetTransform()->SetPosition(80, 20, 0);

	//scene->Add(go);

	//go = new GameObject();
	//go->AddComponent(new RenderComponent());

	//go->AddComponent(new TextComponent("0", font));
	//go->GetTransform()->SetPosition(150, 20, 0);
	//go->AddComponent(new UIComponent());
	//scene->Add(go);

	auto& levels = LevelManager::GetInstance();
	levels.AddLevel(L"../Data/level1.txt", scene);

	GameObject* player = new GameObject();
	player->CreatePlayer(SpriteConfig{ 8, 5 });
	scene->Add(player);

	SceneManager::GetInstance().Initialize();
	SceneManager::GetInstance().PostInitialize();

}

void HiveMind::BubbleBobble::Cleanup()
{
	/*Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();*/
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
		//COMMANDS
		
		float levelTransitionTimer{0};
		float updatePauseTimer{ 0 };
		bool pausePhysics{ false };
		bool doContinue = true;
		while (doContinue)
		{
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
			sceneManager.DeleteInactives();
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
