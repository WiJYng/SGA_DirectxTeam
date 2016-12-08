#include "stdafx.h"
#include "cPlayerSkillEffect.h"


cPlayerSkillEffect::cPlayerSkillEffect()
{
}


cPlayerSkillEffect::~cPlayerSkillEffect()
{
	
}

void cPlayerSkillEffect::Setup()
{
	InitPlayerSkill();
}

void cPlayerSkillEffect::Update(float _TimeDelta)
{
	for each(auto v in m_AttackEffect)
	{
		v->Update(_TimeDelta);
	}

	//Test
	if (KEY_MGR->IsOnceDown(VK_SPACE))
	{
		PlayEffect(EFF_ATTACK, EFF_BURST);
	}
}

void cPlayerSkillEffect::Render()
{
	for each(auto v in m_AttackEffect)
	{
		v->Render();
		v->pTransform->RenderGimozo(Device);
	}
}

void cPlayerSkillEffect::PlayEffect(EFFECT_NAME _Name, EFFECT_TYPE _PlayType)
{
	switch (_Name)
	{
	case EFF_ATTACK :
		if (_PlayType == EFF_PLAY)
		{
			for each(auto v in m_AttackEffect)
				v->StartEmission();
		} 
		else if (_PlayType == EFF_BURST)
		{
			for each(auto v in m_AttackEffect)
				v->Burst(200, 0.8f, 1.0f, 0.1f, 0.2f);
		}

		break;
	default :
		break;

	}
}

void cPlayerSkillEffect::InitPlayerSkill()
{
	//Default Init
	//필요한 effect는 이곳에서 로드한다.

	cPartcleEmitter* e_01 = new cPartcleEmitter;
	e_01->SetActive(true);

	VEC_COLOR c_01;
	c_01.push_back(D3DXCOLOR(1.0f, 1.0f, 0.1f, 1.0f));
	c_01.push_back(D3DXCOLOR(0.8f, 0.3f, 0.1f, 1.0f));
	
	VEC_SCALE s_01;
	//s_01.push_back(0.1f);
	//s_01.push_back(0.7f);
	s_01.push_back(0.3f);
	s_01.push_back(0.5f);

	LPDIRECT3DTEXTURE9 pTex = RESOURCE_TEXTURE->GetResource("./Tera/Effect/F_ring004_emis.tga");

	e_01->Init(
		20, 
		50.0f, 
		1.f,
		3.f,
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(1, 1, 1),
		//D3DXVECTOR3(0.5f, 0.5f, 0.5f),
		//D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(-1,-1,-1),
		c_01, s_01,
		1.0f, 2.0f, 
		pTex,
		false
		);

	m_AttackEffect.push_back(e_01);
}