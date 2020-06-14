#include "SoundManager.h"
#include <sstream>
#include "fmod_errors.h"
HiveMind::SoundManager::~SoundManager()
{
	if (m_pFmodSystem)
	{
		m_pFmodSystem->release();
	}
}
void HiveMind::SoundManager::Initialize()
{
	FMOD_RESULT result;
	unsigned int version;
	int numdrivers;

	/*
	Create a System object and initialize.
	*/
	result = FMOD::System_Create(&m_pFmodSystem);
	ErrorCheck(result);
	result = m_pFmodSystem->getVersion(&version);
	ErrorCheck(result);

	if (version < FMOD_VERSION)
	{
		throw("SoundComponent Initialization Failed!\n\nYou are using an old version of FMOD %08x.");
	}

	result = m_pFmodSystem->getNumDrivers(&numdrivers);
	ErrorCheck(result);
	if (numdrivers == 0)
	{
		result = m_pFmodSystem->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		ErrorCheck(result);
	}
	else
	{
		result = m_pFmodSystem->init(32, FMOD_INIT_NORMAL, 0);
		ErrorCheck(result);
	}

}

void HiveMind::SoundManager::Destroy()
{
	if (m_pFmodSystem)
	{
		m_pFmodSystem->release();
	}
}

void HiveMind::SoundManager::Update()
{
	FMOD_RESULT result = m_pFmodSystem->update();
	ErrorCheck(result);
}

bool HiveMind::SoundManager::ErrorCheck(FMOD_RESULT res)
{
	if (res != FMOD_OK)
	{
		std::wstringstream strstr;
		strstr << L"FMOD error! \n[" << res << L"] " << FMOD_ErrorString(res) << std::endl;
		throw(strstr);
		return false;
	}

	return true;
}