#pragma once
#include "cEffect.h"

#define ENEMYMAXCNT 100

class cEnemyEffect : public cEffect
{
private :
	//cBaseObject*	m_stingEffect;
	//float			m_fTime;
	//
	//
	//VEC_QUADPART	m_vecAttackEffect;
	VEC_TAIL		m_vecAttackEffect;
	

public :
	cEnemyEffect();
	~cEnemyEffect();

	void Setup() override;
	void Update(float _TimeDelta) override;
	void Render() override;
	void PlayEffect(EFFECT_NAME _Name, D3DXVECTOR3 pos) override;
	void PlayEffect(EFFECT_NAME _Name, cTransform* trans);
	

private : 
	void EnemyEffectInit();			//����Ʈ init

	void EnemyAttackEffect_01(D3DXVECTOR3 pos);
	void EnemyAttackEffect_01(cTransform* trans);

	void EnemyAttackEffect_02(D3DXVECTOR3 pos);
	void EnemyAttackEffect_02(cTransform* trans);
};

