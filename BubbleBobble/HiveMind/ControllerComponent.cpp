#include "HiveMindPCH.h"
#include "ControllerComponent.h"

#include <SDL.h>


HiveMind::ControllerComponent::ControllerComponent(const bool useController)
	:m_UseController{useController}
{
}

HiveMind::ControllerComponent::~ControllerComponent()
{
}

void HiveMind::ControllerComponent::Update(const float& elapsedSec)
{
	(elapsedSec);
	ProcessInput();
	HandleInput();
}

void HiveMind::ControllerComponent::Render() const
{
}

void HiveMind::ControllerComponent::Initialize()
{
	JumpCommand jumpCommand{};
	LeftCommand leftCommand{};
	RightCommand rightCommand{};
	ShootCommand shootCommand{};

	if (m_UseController)
	{
		AddInputConfig(XINPUT_GAMEPAD_A, new JumpCommand());
		AddInputConfig(XINPUT_GAMEPAD_DPAD_LEFT, new LeftCommand());
		AddInputConfig(XINPUT_GAMEPAD_DPAD_RIGHT,new RightCommand());
		AddInputConfig(XINPUT_GAMEPAD_B, new ShootCommand());
	}
	else
	{
		AddInputConfig('W', new JumpCommand());
		AddInputConfig('A', new LeftCommand());
		AddInputConfig('D', new RightCommand());
		AddInputConfig(VK_SPACE, new ShootCommand());
	}

}

bool HiveMind::ControllerComponent::ProcessInput()
{
	ZeroMemory(&m_ControllerState, sizeof(XINPUT_STATE));

	DWORD Result = XInputGetState(0, &m_ControllerState);

	if (Result == ERROR_SUCCESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool HiveMind::ControllerComponent::IsPressed(const WORD& gamepadButton) const
{
	if (m_UseController)
	{
		if ((m_ControllerState.Gamepad.wButtons & gamepadButton) != 0)
		{
			return true;
		}
	}
	else if (GetAsyncKeyState(gamepadButton))
	{
		return true;
	}
	return false;
}

void HiveMind::ControllerComponent::HandleInput()
{
	bool buttonPressed{};
	if (GetGameObject()->HasComponent<ActorComponent>())
	{
		ActorComponent* pActorComp{ GetGameObject()->GetComponent<ActorComponent>() };
		for (InputConfig& inputConfig : m_pCommandInput)
		{
			if (pActorComp->GetActorState() != ActorComponent::ActorState::DEATH)
			{
				if (inputConfig.pCommand != nullptr && IsPressed(inputConfig.GamepadButton))
				{
					inputConfig.pCommand->Execute(pActorComp);
					buttonPressed = true;
				}
				if(!buttonPressed)
				{
					inputConfig.pCommand->SetIdle(pActorComp);
				}
			}
		}
	}
	else
		throw("GameObject with Controller needs Actor");
}

void HiveMind::ControllerComponent::AddInputConfig(const WORD& gamepadButton, Command* pCommand)
{
	
	m_pCommandInput.push_back(InputConfig{ gamepadButton, pCommand  });
}


