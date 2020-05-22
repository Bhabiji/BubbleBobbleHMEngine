#include "HiveMindPCH.h"
#include "InputManager.h"
#include <SDL.h>


bool HiveMind::InputManager::ProcessInput()
{
	// Zeroise the state
	ZeroMemory(&m_ControllerState, sizeof(XINPUT_STATE));

	// Get the state
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

bool HiveMind::InputManager::IsPressed(const WORD& gamepadButton) const
{
	if ((m_ControllerState.Gamepad.wButtons & gamepadButton) != 0)
	{
		return true;
	}
	return false;
}

void HiveMind::InputManager::HandleInput(ActorComponent* pActor)
{
	bool buttonPressed{};
	for (InputConfig& inputConfig : m_pCommandInput)
	{

		if (inputConfig.pCommand != nullptr && IsPressed(inputConfig.GamepadButton))
		{
			inputConfig.pCommand->Execute(pActor);
			buttonPressed = true;
		}
		if(!buttonPressed)
		{
			inputConfig.pCommand->SetIdle(pActor);
		}
	}
}

void HiveMind::InputManager::AddInputConfig(const WORD& gamepadButton, Command* pCommand)
{
	m_pCommandInput.push_back(InputConfig{ gamepadButton, pCommand });
}

