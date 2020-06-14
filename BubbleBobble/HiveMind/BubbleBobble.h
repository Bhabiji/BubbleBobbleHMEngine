#pragma once
#include "Core.h"
struct SDL_Window;

namespace HiveMind
{

	class HIVEMIND_API BubbleBobble
	{
	public:
		void Initialize();
		void LoadGame() const;
		void LoadGameScene() const;
		void Cleanup();
		void Run();
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
		float m_DeltaTime;
	};
}
