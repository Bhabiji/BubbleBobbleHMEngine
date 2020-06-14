#include "SoundComponent.h"
#include <sstream>
#include "fmod_errors.h"
#include "SoundManager.h"
using namespace FMOD;

HiveMind::SoundComponent::SoundComponent()
{
	Initialize();
}


HiveMind::SoundComponent::~SoundComponent()
{

}


void HiveMind::SoundComponent::Update(const float& elapsedSec)
{
	(elapsedSec);

}

void HiveMind::SoundComponent::PlaySoundByName(const std::string& sound)
{
	SoundManager::GetInstance().GetSoundSystem()->playSound(m_pSounds[sound], 0, false, &m_pChannel);
}

void HiveMind::SoundComponent::AddSound(const std::string& soundName, const std::string& assetPath, const bool loop)
{
	//Add sound to the map
	if(!loop)
		SoundManager::GetInstance().GetSoundSystem()->createSound(assetPath.c_str(), FMOD_LOOP_OFF, 0, &m_pSounds[soundName]);
	else 
		SoundManager::GetInstance().GetSoundSystem()->createSound(assetPath.c_str(), FMOD_LOOP_NORMAL, 0, &m_pSounds[soundName]);

}

void HiveMind::SoundComponent::Initialize()
{
	m_pChannel = 0;
}

void HiveMind::SoundComponent::Render() const
{
}
