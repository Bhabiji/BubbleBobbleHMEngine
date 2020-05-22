#pragma once

#include <Windows.h>
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"
#include "ActorComponent.h"

namespace HiveMind
{
	struct InputConfig
	{
		WORD GamepadButton;
		Command* pCommand;
	};
	//enum class ControllerButton
	//{
	//	ButtonA,
	//	ButtonB,
	//	ButtonX,
	//	ButtonY,
	//	Keyboard_A,
	//	Keyboard_Z,
	//	Keyboard_E,
	//	Keyboard_R,
	//	Keyboard_T,
	//	Keyboard_Y,
	//	Keyboard_U,
	//	Keyboard_I,
	//	Keyboard_O,
	//	Keyboard_P,
	//	Keyboard_Q,
	//	Keyboard_S,
	//	Keyboard_D,
	//	Keyboard_F,
	//	Keyboard_G,
	//	Keyboard_H,
	//	Keyboard_J,
	//	Keyboard_K,
	//	Keyboard_L,
	//	Keyboard_M,
	//	Keyboard_W,
	//	Keyboard_X,
	//	Keyboard_C,
	//	Keyboard_V,
	//	Keyboard_B,
	//	Keyboard_N,
	//	Keyboard_UP,
	//	Keyboard_DOWN,
	//	Keyboard_LEFT,
	//	Keyboard_RIGHT,


	//	Count
	//	//...
	//};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsPressed(const WORD& gamepadButton) const;
		void HandleInput(ActorComponent* pActor);
		void AddInputConfig(const WORD& gamepadButton, Command* pCommand);
	private:
		std::vector<InputConfig> m_pCommandInput;
		XINPUT_STATE m_ControllerState;

	};

}
