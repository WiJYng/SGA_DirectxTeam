#pragma once

#include "cPartcleEmitter.h"
#include "cQuadParticleEmitter.h"
#include "cTrailRender.h"
#include "cXMesh_Static.h"
#include "cBaseObject.h"

//effeectName
enum EFFECT_NAME {
	PLAYER_ATTACK_01_L = 0,						//플레이어 공격시 이펙트 - 왼쪽
	PLAYER_ATTACK_01_R,							//플레이어 공격시 이펙트 - 오른쪽
	PLAYER_ATTACL_02,							//플레이어 공격 히트이펙트
	PLAYER_RUN,									//플레이어 달릴 때 이펙트
	ENEMY_ATTACK_01,							//적 공격시 이펙트
	ENEMY_ATTACK_02,							//적 공격시 히트이펙트
	BOSS_ATTACK,								//보스 공격시 이펙트 1번모션
	BOSS_ATTACK_GROUND,							//보스 공격시 이펙트 바닥
	BOSS_ATTACK_GROUND_STOP,
	BOSS_ATTACK_01,								//보스 공격시 히트이펙트
	LOCATION_ARROW_01,
	LOCATION_ARROW_02,
	LOCATION_ARROW_03,
	LOCATION_ARROW_04,
	LOCATION_ARROW_BOSS,
};

class cEffect
{
protected:
	typedef vector<cPartcleEmitter*>			VEC_PART;
	typedef vector<cQuadParticleEmitter*>		VEC_QUADPART;
	typedef vector<cTrailRender*>				VEC_TAIL;
	typedef vector<cXMesh_Static*>				VEC_MESH;

	typedef map<string, cPartcleEmitter*>		MAP_PART;
	typedef map<string, cQuadParticleEmitter*>	MAP_QUADPART;
	typedef map<string, cTrailRender*>			MAP_TAIL;
	typedef map<string, cXMesh_Static*>			MAP_MESH;

protected :
	LPD3DXEFFECT m_fxEffect;

public:
	cEffect();
	~cEffect();

	virtual void Setup() {};
	virtual void Update(float _delta) {};
	virtual void Render() {};
	virtual void PlayEffect(EFFECT_NAME _Name, D3DXVECTOR3 pos) {};
};

