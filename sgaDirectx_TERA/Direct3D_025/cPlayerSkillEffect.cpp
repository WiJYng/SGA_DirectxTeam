#include "stdafx.h"
#include "cPlayerSkillEffect.h"


cPlayerSkillEffect::cPlayerSkillEffect()
{

}


cPlayerSkillEffect::~cPlayerSkillEffect()
{
	//Trail 해재
	for each(auto t in m_vectailEffect)
	{
		t->Release();
		SAFE_DELETE(t);
	}
}

void cPlayerSkillEffect::Setup()
{
	InitPlayerSkill();

}

void cPlayerSkillEffect::Update(float _TimeDelta)
{
	for each(auto v in m_vectailEffect)
	{
		v->Update(_TimeDelta);
	}

	for each(auto v in m_vecAttackEffect)
	{
		v->Update(_TimeDelta);
	}
}

void cPlayerSkillEffect::Render()
{
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	Device->SetRenderState(D3DRS_ALPHAREF, 0.5f);

	//Render
	//=================================================
	
	for each(auto v in m_vecAttackEffect) { v->Render(); }
	for each(auto v in m_vectailEffect) { v->Render(); }

	//=================================================

	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}

void cPlayerSkillEffect::PlayEffect(EFFECT_NAME _Name, D3DXVECTOR3 pos)
{
	if (pos == NULL)
		pos = D3DXVECTOR3(0, 0, 0);

	switch (_Name)
	{
	case PLAYER_ATTACK_01_L:
		PlayerAttackEffect_01_L(pos);
		break;
	case PLAYER_ATTACK_01_R:
		PlayerAttackEffect_01_R(pos);
		break;
	case PLAYER_ATTACL_02:
		PlayerAttackEffect_02(pos);
		break;
	default :
		break;
	}
}

void cPlayerSkillEffect::PlayerAttackEffect_01_L(D3DXVECTOR3 pos)
{
	m_vectailEffect[0]->Transform.SetWorldPosition(pos);
}

void cPlayerSkillEffect::PlayerAttackEffect_01_R(D3DXVECTOR3 pos)
{
	m_vectailEffect[1]->Transform.SetWorldPosition(pos);
}

void cPlayerSkillEffect::PlayerAttackEffect_02(D3DXVECTOR3 pos)
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
	// 2. 공격시 검선 이펙트
	//--------------------------------------------
	//TrailRenderSet
	cTrailRender* t1 = new cTrailRender();
	t1->Init(
		0.2f,					//꼬리 라이브 타임 ( 이게 크면 환영큐 사이즈가 커지고 꼬리가 오랬동안 남아있다 )
		0.7f,					//폭
		RESOURCE_TEXTURE->GetResource("./Tera/Effect/E_Swordtrail005_emis.tga"),	//메인 Texture
		D3DXCOLOR(0, 0.5, 1, 0.7),												//메인 Texture 로 그릴때 컬러
		RESOURCE_TEXTURE->GetResource("./Tera/Effect/E_Swordtrail004_emis.tga")	//외곡 그릴때 외곡 노말
		);

	cTrailRender* t2 = new cTrailRender();
	t2->Init(
		0.2f,					//꼬리 라이브 타임 ( 이게 크면 환영큐 사이즈가 커지고 꼬리가 오랬동안 남아있다 )
		0.7f,					//폭
		RESOURCE_TEXTURE->GetResource("./Tera/Effect/E_Swordtrail005_emis.tga"),	//메인 Texture
		D3DXCOLOR(0, 0.5, 1, 0.7),												//메인 Texture 로 그릴때 컬러
		RESOURCE_TEXTURE->GetResource("./Tera/Effect/E_Swordtrail004_emis.tga")	//외곡 그릴때 외곡 노말
		);

	//왼쪽 오른쪽 두개
	m_vectailEffect.push_back(t1);
	m_vectailEffect.push_back(t2);
}