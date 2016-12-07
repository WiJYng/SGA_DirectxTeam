#pragma once
#include "cEffect.h"

class cEffectManager
{
private:

public:
	cEffectManager();
	~cEffectManager();

	void SetupDefaultEffect();

	void Setup();

	void GetEffect(string Name);
};

