#pragma once
#include "cEffect.h"




class cPlayerSkillEffect : public cEffect
{

private :
	VEC_PART							m_vecAttackEffect;



public :
	cPlayerSkillEffect();
	~cPlayerSkillEffect();
	
	void Setup() override;
	void Update(float _TimeDelta);
	void Render() override;

	void PlayEffect(EFFECT_NAME _Name, D3DXVECTOR3 pos);

private:
	void InitPlayerSkill();						//��ų Init

	//��������Ʈ
	void PlayAttackEffect_01(D3DXVECTOR3 pos);

};

