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
	for each(auto v in m_vecAttackEffect)
	{
		v->Update(_TimeDelta);
	}

	//Test
	//if (KEY_MGR->IsOnceDown(VK_SPACE))
	//{
	//	PlayEffect(EFF_ATTACK_01, D3DXVECTOR3(0, 0, 0));
	//}
}

void cPlayerSkillEffect::Render()
{
	for each(auto v in m_vecAttackEffect)
	{
		v->Render();
		//v->pTransform->RenderGimozo(Device);
	}
}

void cPlayerSkillEffect::PlayEffect(EFFECT_NAME _Name, D3DXVECTOR3 pos)
{
	if (pos == NULL)
		pos = D3DXVECTOR3(0, 0, 0);

	switch (_Name)
	{
	case PLAYER_ATTACK_01:
		PlayAttackEffect_01(pos);

		break;
	default :
		break;

	}
}

void cPlayerSkillEffect::PlayAttackEffect_01(D3DXVECTOR3 pos)
{
	//공격effect index 0, 1
	m_vecAttackEffect[0]->pTransform->SetWorldPosition(pos);
	m_vecAttackEffect[1]->pTransform->SetWorldPosition(pos);


	m_vecAttackEffect[0]->Burst(200, 0.8f, 1.0f, 0.1f, 0.2f);
	m_vecAttackEffect[1]->Burst(5, 1.0f, 1.0f, 0.1f, 0.1f);
}



void cPlayerSkillEffect::InitPlayerSkill()
{
	//Default Init
	//필요한 effect는 이곳에서 로드한다.

	//-----------------------------------------
	//	1.단발공격이펙트
	//-----------------------------------------
	cPartcleEmitter* e_01 = new cPartcleEmitter;
	e_01->SetActive(true);

	VEC_COLOR color;
	color.push_back(D3DXCOLOR(1.0f, 1.0f, 0.1f, 1.0f));
	color.push_back(D3DXCOLOR(0.8f, 0.3f, 0.1f, 1.0f));
	
	VEC_SCALE scale;
	scale.push_back(0.3f);
	scale.push_back(0.5f);

	LPDIRECT3DTEXTURE9 pTex = RESOURCE_TEXTURE->GetResource("./Tera/Effect/F_ring004_emis.tga");

	e_01->Init(
		20, 
		50.0f, 
		1.f,
		3.f,
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(1, 1, 1),
		D3DXVECTOR3(-1,-1,-1),
		color, scale,
		1.0f, 2.0f, 
		pTex,
		false
		);

	//
	cPartcleEmitter* e_02 = new cPartcleEmitter;
	e_02->SetActive(true);

	LPDIRECT3DTEXTURE9 pTex2 = RESOURCE_TEXTURE->GetResource("./Tera/Effect/A_BigShot002_emis.tga");

	e_02->Init(
		1,
		40.0f,
		1.f,
		3.f,
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(1, 1, 1),
		D3DXVECTOR3(-1, -1, -1),
		color, scale,
		1.0f, 1.0f,
		pTex2,
		false
		);

	m_vecAttackEffect.push_back(e_01);
	m_vecAttackEffect.push_back(e_02);
	


	//--------------------------------------------
	//
	//--------------------------------------------
}