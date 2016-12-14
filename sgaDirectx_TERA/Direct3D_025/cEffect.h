#pragma once

#include "cPartcleEmitter.h"
#include "cQuadParticleEmitter.h"
#include "cTrailRender.h"

//effeectName
enum EFFECT_NAME {
	PLAYER_ATTACK_01_L = 0,						//�÷��̾� ���ݽ� ����Ʈ - ����
	PLAYER_ATTACK_01_R,							//�÷��̾� ���ݽ� ����Ʈ - ������
	PLAYER_ATTACL_02,							//�÷��̾� ���� ��Ʈ����Ʈ
	PLAYER_RUN,									//�÷��̾� �޸� �� ����Ʈ
	ENEMY_ATTACK_01,							//�� ���ݽ� ����Ʈ
	ENEMY_ATTACK_02,							//�� ���ݽ� ��Ʈ����Ʈ
	BOSS_ATTACK_01,								//���� ���ݽ� ����Ʈ 1�����
	BOSS_ATTACK_02,								//���� ���ݽ� ����Ʈ 2�����
	BOSS_ATTACK_03,								//���� ���ݽ� ����Ʈ 3�����
	BOSS_ATTACK_03_GROUND,						//���� ���ݽ� ����Ʈ �ٴ�
	BOSS_ATTACK_04,								//���� ���ݽ� ��Ʈ����Ʈ
};

class cEffect
{
public:
	typedef vector<cPartcleEmitter*>			VEC_PART;
	typedef vector<cQuadParticleEmitter*>		VEC_QUADPART;
	typedef vector<cTrailRender*>				VEC_TAIL;

	typedef map<string, cPartcleEmitter*>		MAP_PART;
	typedef map<string, cQuadParticleEmitter*>	MAP_QUADPART;
	typedef map<string, cTrailRender*>			MAP_TAIL;

public:
	cEffect();
	~cEffect();

	virtual void Setup() {};
	virtual void Render() {};
	virtual void PlayEffect(EFFECT_NAME _Name, D3DXVECTOR3 pos) {};
};

