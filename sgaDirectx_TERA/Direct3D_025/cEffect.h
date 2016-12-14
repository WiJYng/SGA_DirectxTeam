#pragma once

#include "cPartcleEmitter.h"
#include "cQuadParticleEmitter.h"

//effeectName
enum EFFECT_NAME {
	PLAYER_ATTACK_01 = 0,						//플레이어 공격 히트이펙트
	PLAYER_RUN,									//플레이어 달릴 때 이펙트
	ENEMY_ATTACK_01,							//적 공격시 이펙트
	ENEMY_ATTACK_02,							//적 공격시 히트이펙트
	BOSS_ATTACK_01,								//보스 공격시 이펙트 1번모션
	BOSS_ATTACK_02,								//보스 공격시 이펙트 2번모션
	BOSS_ATTACK_03,								//보스 공격시 이펙트 3번모션
	BOSS_ATTACK_03_GROUND,						//보스 공격시 이펙트 바닥
	BOSS_ATTACK_04,								//보스 공격시 히트이펙트
};

class cEffect
{
public:
	typedef vector<cPartcleEmitter*>			VEC_PART;
	typedef vector<cQuadParticleEmitter*>		VEC_QUADPART;

	typedef map<string, cPartcleEmitter*>		MAP_PART;
	typedef map<string, cQuadParticleEmitter*>	MAP_QUADPART;


public:
	cEffect();
	~cEffect();

	virtual void Setup() {};
	virtual void Render() {};
};

