#pragma once
#include "cEffect.h"

class cBossEffect : public cEffect
{
private:
	cTrailRender*	m_pTail;


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
};

