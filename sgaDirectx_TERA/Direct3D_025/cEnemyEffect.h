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
	VEC_PART		m_vecAttackEffect2;
	

public :
	cEnemyEffect();
	~cEnemyEffect();

	void Setup() override;
	void Update(float _TimeDelta) override;
	void Render() override;
	void PlayEffect(EFFECT_NAME _Name, D3DXVECTOR3 pos) override;
	
private : 
	void EnemyEffectInit();			//¿Ã∆Â∆Æ init

	void EnemyAttackEffect_01(D3DXVECTOR3 pos);
	void EnemyAttackEffect_02(D3DXVECTOR3 pos);
};

