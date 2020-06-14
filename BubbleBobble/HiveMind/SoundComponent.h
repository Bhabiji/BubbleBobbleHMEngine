#pragma once
#include "BaseComponent.h"
#include "fmod.hpp"
#include <map>
#include <string>
namespace HiveMind
{
	class SoundComponent : public BaseComponent
	{
	public:
		SoundComponent();
		~SoundComponent();
		SoundComponent(const SoundComponent& obj) = delete;
		SoundComponent& operator=(const SoundComponent& obj) = delete;
		
		virtual void Update(const float& elapsedSec) override;
		virtual void Initialize() override;
		virtual void Render() const override;

		void PlaySoundByName(const std::string& sound);
		void AddSound(const std::string& soundName, const std::string& assetPath, const bool loop);

	protected:

	private:
		std::map<std::string, FMOD::Sound*> m_pSounds;
		FMOD::Channel* m_pChannel;
	};
}


