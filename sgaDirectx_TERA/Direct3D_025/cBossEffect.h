#pragma once
#include "cEffect.h"

class cBossEffect : public cEffect
{
private:
	cTrailRender*			m_pTail;
	cQuadParticleEmitter*	m_pGroundAttack;
	VEC_PART				m_vecAttackEffect;

	bool					m_isGaPlay;

public:
	cBossEffect();
	~cBossEffect();

	void Setup() override;
	void Update(float _delta) override;
	void Render() override;
	void PlayEffect(EFFECT_NAME _Name, D3DXVECTOR3 pos) override;

private:
	void BossSkillEffectInit();

	void PlayBossTail(D3DXVECTOR3 pos);
	void PlayBossGroundAttack(D3DXVECTOR3 pos, bool isOn);
	void PlayBossAttackEffect(D3DXVECTOR3 pos);
};

