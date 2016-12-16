#pragma once

#include "cPartcleEmitter.h"
#include "cQuadParticleEmitter.h"
#include "cTrailRender.h"
#include "cXMesh_Static.h"
#include "cBaseObject.h"

//effeectName
enum EFFECT_NAME {
	PLAYER_ATTACK_01_L = 0,						//�÷��̾� ���ݽ� ����Ʈ - ����
	PLAYER_ATTACK_01_R,							//�÷��̾� ���ݽ� ����Ʈ - ������
	PLAYER_ATTACL_02,							//�÷��̾� ���� ��Ʈ����Ʈ
	PLAYER_RUN,									//�÷��̾� �޸� �� ����Ʈ
	ENEMY_ATTACK_01,							//�� ���ݽ� ����Ʈ
	ENEMY_ATTACK_02,							//�� ���ݽ� ��Ʈ����Ʈ
	BOSS_ATTACK,								//���� ���ݽ� ����Ʈ 1�����
	BOSS_ATTACK_03_GROUND,						//���� ���ݽ� ����Ʈ �ٴ�
	BOSS_ATTACK_04,								//���� ���ݽ� ��Ʈ����Ʈ
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

