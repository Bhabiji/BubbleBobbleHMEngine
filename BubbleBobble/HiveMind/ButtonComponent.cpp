#include "ButtonComponent.h"
#include "GameObject.h"
#include "Components.h"
#include "SceneManager.h"
#include "Renderer.h"
HiveMind::ButtonComponent::ButtonComponent(const Int2& size, const std::string& linkedScene)
	:m_LinkedSceneName{linkedScene}
	,m_Size{size}
	,m_Alpha{1}
	,m_Action{Action::NONE}
{
}

HiveMind::ButtonComponent::ButtonComponent(const Int2& size, const Action action)
	:m_Size{size}
	,m_Action{action}
	,m_Alpha{1}
	,m_LinkedSceneName{""}
{
}

HiveMind::ButtonComponent::ButtonComponent(const Int2& size, const Action action, const std::string& linkedScene)
	:m_Size{size}
	,m_Action{action}
	,m_LinkedSceneName{linkedScene}
	,m_Alpha{1}
{
}

HiveMind::ButtonComponent::~ButtonComponent()
{
}

void HiveMind::ButtonComponent::Initialize()
{
}

void HiveMind::ButtonComponent::Render() const
{
	const SDL_Rect rect{ GetGameObject()->GetTransform()->GetPosition().x, GetGameObject()->GetTransform()->GetPosition().y, m_Size.x, m_Size.y };
	SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 255, 255, 255, m_Alpha);
	SDL_RenderDrawRect(Renderer::GetInstance().GetSDLRenderer(), &rect);
	SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 0, 0, 0, 1);

}

void HiveMind::ButtonComponent::Update(const float& elapsedSec)
{
	Int2 mousePos{};
	SDL_PumpEvents();
	SDL_GetMouseState(&mousePos.x, &mousePos.y);
	if (HiveMind::IsOverlapping(mousePos, RectI{ int(GetGameObject()->GetTransform()->GetPosition().x), int(GetGameObject()->GetTransform()->GetPosition().y), m_Size.x, m_Size.y }))
	{
		if (m_Alpha > 0.2f)
			m_Alpha -= elapsedSec;
	
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0) //checkifmouse is pressed
		{
			Execute(m_Action);
			if (SceneManager::GetInstance().GetScene(m_LinkedSceneName))
				SceneManager::GetInstance().SetSceneActive(m_LinkedSceneName, true);


		}
	
	}
	else if(m_Alpha < 1.f)
	{
		m_Alpha += elapsedSec;
	}
	std::cout << mousePos.x << ", " << mousePos.y << std::endl;
}

void HiveMind::ButtonComponent::Execute(Action action)
{
	switch (action)
	{
	case HiveMind::ButtonComponent::Action::NONE:
		break;
	case HiveMind::ButtonComponent::Action::LOADSINGLEPLAYERSCENE:
		SceneManager::GetInstance().LoadGameScene();
		break;
	case HiveMind::ButtonComponent::Action::LOADMULTIPLAYERSCENE:
		SceneManager::GetInstance().LoadMultiPlayerGameScene();

		break;
	case HiveMind::ButtonComponent::Action::DESTROYSINGLEPLAYERSCENE:
		SceneManager::GetInstance().ResetScene("SinglePlayerGame");
		break;
	default:
		break;
	}

	
}
