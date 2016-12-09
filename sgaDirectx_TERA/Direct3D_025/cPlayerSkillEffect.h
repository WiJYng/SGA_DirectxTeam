#pragma once
#include "cPartcleEmitter.h"
#include "cQuadParticleEmitter.h"

//effeectName
enum EFFECT_NAME {
	EFF_ATTACK_01 = 0,						//��� Ÿ������Ʈ


};


class cPlayerSkillEffect
{
public :
	typedef vector<cPartcleEmitter*>			VEC_PART;
	typedef vector<cQuadParticleEmitter*>		VEC_QUADPART;
	
	typedef map<string, cPartcleEmitter*>		MAP_PART;
	typedef map<string, cQuadParticleEmitter*>	MAP_QUADPART;

private :
	VEC_PART							m_vecAttackEffect;



public :
	cPlayerSkillEffect();
	~cPlayerSkillEffect();
	
	void Setup();
	void Update(float _TimeDelta);
	void Render();

	void PlayEffect(EFFECT_NAME _Name);

private:
	void InitPlayerSkill();						//��ų Init

	//��������Ʈ
	void PlayAttackEffect_01();



	//�ǰ�����Ʈ
	void PlayerAttackedEffect();
};

