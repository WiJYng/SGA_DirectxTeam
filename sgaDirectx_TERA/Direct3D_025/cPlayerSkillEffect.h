#pragma once
#include "cEffect.h"


class cPlayerSkillEffect
{
public :
	typedef vector<cEffect*> VEC_EFFECT;
	typedef map<string, VEC_EFFECT> MAP_EFFECT;

private :
	MAP_EFFECT m_mapEffects;

public :
	cPlayerSkillEffect();
	~cPlayerSkillEffect();
	
	void StartEffect(string _Name);
	void StopEffect(string _Name);

private:
	void InitPlayerSkill();						//½ºÅ³ Init

};

