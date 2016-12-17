#pragma once
#include "cSingletonBase.h"
#include "inc/fmod.hpp"
#pragma comment(lib, "lib/fmodex_vc.lib")

using namespace FMOD;

#define SOUNDBUFFER 100
#define EXTRACHANNELBUFFER 50

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

class cSoundManager : public cSingletonBase<cSoundManager>
{
private:
	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundsIter;
	typedef map<string, Channel**> arrChannels;
	typedef map<string, Channel**>::iterator arrChannelsIter;

private:
	System*			pSystem;
	Sound**			pSound;
	Channel**		pChannel;

	arrSounds		vecTotalSounds;

private:
	cSoundManager();
public:
	friend cSoundManager* cSingletonBase<cSoundManager>::GetInstance();
	~cSoundManager(void);

	HRESULT Init(void);
	void Update(void);
	void Release(void);
	
	void addSound(string keyName, string soundName, bool bgm, bool loop);
	void play(string keyName, float volume = 1.0f); // 0.0 ~ 1.0f  0 ~ 255
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	bool isPlaySound(string keyName);

	bool isPauseSound(string keyName);
};

#define SOUND_MGR cSoundManager::GetInstance()