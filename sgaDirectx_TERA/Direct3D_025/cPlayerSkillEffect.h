#pragma once
#include "cEffect.h"


class cPlayerSkillEffect : public cEffect
{
private :
	VEC_TAIL							m_vectailEffect;
	VEC_PART							m_vecAttackEffect;	
public :
	cPlayerSkillEffect();
	~cPlayerSkillEffect();
	
	//override
	void Setup() override;
	void Update(float _TimeDelta) override;
	void Render() override;
	void PlayEffect(EFFECT_NAME _Name, D3DXVECTOR3 pos) override;

private:
	void InitPlayerSkill();						//스킬 Init

	//플레이어 공격 이펙트
	void PlayerAttackEffect_01_L(D3DXVECTOR3 pos);
	void PlayerAttackEffect_01_R(D3DXVECTOR3 pos);
	void PlayerAttackEffect_02(D3DXVECTOR3 pos);

	void PlayerRunEffect(D3DXVECTOR3 pos);

};

