#pragma once
#include "cPartcleEmitter.h"
#include "cQuadParticleEmitter.h"

enum EFFECT_NAME {
	EFF_ATTACK = 0,

};

enum EFFECT_TYPE
{
	EFF_PLAY = 0,
	EFF_BURST,

};


class cPlayerSkillEffect
{
public :
	typedef vector<cPartcleEmitter*>			VEC_PART;
	typedef vector<cQuadParticleEmitter*>		VEC_QUADPART;
	
	typedef map<string, cPartcleEmitter*>		MAP_PART;
	typedef map<string, cQuadParticleEmitter*>	MAP_QUADPART;

private :
	VEC_PART				m_AttackEffect;


public :
	cPlayerSkillEffect();
	~cPlayerSkillEffect();
	
	void Setup();
	void Update(float _TimeDelta);
	void Render();

	void PlayEffect(EFFECT_NAME _Name, EFFECT_TYPE _PlayType);

private:
	void InitPlayerSkill();						//½ºÅ³ Init

};

