#pragma once
#include "Singleton.h"
#include "fmod.hpp"
#include "fmod.h"
namespace HiveMind
{
	class SoundManager : public Singleton<SoundManager>
	{
	public:
		virtual ~SoundManager();
		void Initialize();
		void Destroy();
		void Update();
		FMOD::System* GetSoundSystem() { return m_pFmodSystem; };
	private:
		bool ErrorCheck(FMOD_RESULT res);
		FMOD::System* m_pFmodSystem;
	};
}

