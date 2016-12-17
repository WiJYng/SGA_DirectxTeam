#include "stdafx.h"
#include "cSoundManager.h"


cSoundManager::cSoundManager()
	: pSystem(NULL)
	, pSound(NULL)
	, pChannel(NULL)
{
}


cSoundManager::~cSoundManager()
{
}


HRESULT cSoundManager::Init(void)
{
	System_Create(&pSystem);
	pSystem->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	pSound = new Sound*[TOTALSOUNDBUFFER];
	pChannel = new Channel*[TOTALSOUNDBUFFER];

	memset(pSound, 0, sizeof(Sound*) * TOTALSOUNDBUFFER);
	memset(pChannel, 0, sizeof(Channel*) * TOTALSOUNDBUFFER);

	return S_OK;
}

void cSoundManager::Release(void)
{

}

void cSoundManager::Update(void)
{
	pSystem->update();
}


void cSoundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
	//루프여부
	if (loop)
	{
		if (bgm)
		{
			pSystem->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &pSound[vecTotalSounds.size()]);
		}
		else
		{
			pSystem->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &pSound[vecTotalSounds.size()]);
		}
	}
	else
	{
		if (bgm)
		{
			pSystem->createStream(soundName.c_str(), FMOD_DEFAULT, 0, &pSound[vecTotalSounds.size()]);
		}
		else
		{
			pSystem->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &pSound[vecTotalSounds.size()]);
		}
	}

	vecTotalSounds.insert(make_pair(keyName, &pSound[vecTotalSounds.size()]));
}

void cSoundManager::play(string keyName, float volume)
{
	arrSoundsIter iter = vecTotalSounds.begin();

	int count = 0;

	for (iter; iter != vecTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//pSystem->playSound(FMOD_CHANNEL_FREE, pSound[count], false, &pChannel[count]);
			pSystem->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &pChannel[count]);

			pChannel[count]->setVolume(volume);
			break;
		}
	}
}

void cSoundManager::stop(string keyName)
{
	arrSoundsIter iter = vecTotalSounds.begin();

	int count = 0;

	for (iter; iter != vecTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			pChannel[count]->stop();
			break;
		}
	}
}

void cSoundManager::pause(string keyName)
{
	arrSoundsIter iter = vecTotalSounds.begin();

	int count = 0;

	for (iter; iter != vecTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			pChannel[count]->setPaused(true);
			break;
		}
	}
}

void cSoundManager::resume(string keyName)
{
	arrSoundsIter iter = vecTotalSounds.begin();

	int count = 0;

	for (iter; iter != vecTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			pChannel[count]->setPaused(false);
			break;
		}
	}
}

bool cSoundManager::isPlaySound(string keyName)
{
	bool isPlay;
	arrSoundsIter iter = vecTotalSounds.begin();

	int count = 0;

	for (iter; iter != vecTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			pChannel[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

bool cSoundManager::isPauseSound(string keyName)
{
	bool isPause;
	arrSoundsIter iter = vecTotalSounds.begin();

	int count = 0;

	for (iter; iter != vecTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			pChannel[count]->getPaused(&isPause);
			break;
		}
	}

	return isPause;
}
