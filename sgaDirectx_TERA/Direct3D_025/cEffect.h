#pragma once

#include "cPartcleEmitter.h"
#include "cQuadParticleEmitter.h"

//effeectName
enum EFFECT_NAME {
	PLAYER_ATTACK_01 = 0,						//�÷��̾� ���� ��Ʈ����Ʈ
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

	typedef map<string, cPartcleEmitter*>		MAP_PART;
	typedef map<string, cQuadParticleEmitter*>	MAP_QUADPART;


public:
	cEffect();
	~cEffect();

	virtual void Setup() {};
	virtual void Render() {};
};

