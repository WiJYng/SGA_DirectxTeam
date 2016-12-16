#include "stdafx.h"
#include "cEnemyEffect.h"


cEnemyEffect::cEnemyEffect()
{
}


cEnemyEffect::~cEnemyEffect()
{
}

void cEnemyEffect::Setup()
{
	EnemyEffectInit();
}

void cEnemyEffect::Update(float _TimeDelta)
{
	for each (auto v in m_vecAttackEffect)
	{
		v->Update(_TimeDelta);
	}

	for each(auto v in m_vecAttackEffect2)
	{
		v->Update(_TimeDelta);
	}

}

void cEnemyEffect::Render()
{
	DWORD prevLight;
	Device->GetRenderState(D3DRS_LIGHTING, &prevLight);
	Device->SetRenderState(D3DRS_LIGHTING, FALSE);

	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	Device->SetRenderState(D3DRS_ALPHAREF, 0.5f);
	
	//Render
	//=================================================

	for each(auto v in m_vecAttackEffect2) { v->Render(); }
	for each(auto v in m_vecAttackEffect) { v->Render(); }

	//=================================================

	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	Device->SetRenderState(D3DRS_LIGHTING, prevLight);
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	
}

void cEnemyEffect::PlayEffect(EFFECT_NAME _Name, D3DXVECTOR3 pos)
{
	if (pos == NULL)
		pos = D3DXVECTOR3(0, 0, 0);
	
	switch (_Name)
	{
	case ENEMY_ATTACK_01:
		EnemyAttackEffect_01(pos);
		break;
	case ENEMY_ATTACK_02:
		EnemyAttackEffect_02(pos);
		break;
	default:
		break;
	}
}


void cEnemyEffect::EnemyAttackEffect_01(D3DXVECTOR3 pos)
{
	//회전이펙트가 추가될수있음 추가되면 좋을것같음
	if (this->m_fxEffect == NULL)
		m_fxEffect = NULL;

	for each(auto v in m_vecAttackEffect)
	{
		v->Transform.SetWorldPosition(pos);
	}
}


void cEnemyEffect::EnemyAttackEffect_02(D3DXVECTOR3 pos)
{
	m_vecAttackEffect2[0]->pTransform->SetWorldPosition(pos);
	m_vecAttackEffect2[1]->pTransform->SetWorldPosition(pos);

	m_vecAttackEffect2[0]->Burst(200, 0.8f, 1.0f, 0.1f, 0.2f);
	m_vecAttackEffect2[1]->Burst(5, 1.0f, 1.0f, 0.1f, 0.1f);
}


//Skill Init
void cEnemyEffect::EnemyEffectInit()
{	
	cPartcleEmitter* e_01 = new cPartcleEmitter;
	e_01->SetActive(true);

	VEC_COLOR color;
	color.push_back(D3DXCOLOR(1.0f, 0.2f, 0.0f, 1.0f));
	color.push_back(D3DXCOLOR(0.8f, 0.3f, 0.0f, 1.0f));

	VEC_SCALE scale;
	scale.push_back(0.2f);
	scale.push_back(0.4f);

	LPDIRECT3DTEXTURE9 pTex = RESOURCE_TEXTURE->GetResource("./Tera/Effect/F_ring003_emis.tga");

	e_01->Init(
		20,
		40.0f,
		1.f,
		3.f,
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(1, 1, 1),
		D3DXVECTOR3(-1, -1, -1),
		color, scale,
		1.0f, 1.5f,
		pTex,
		false
		);

	cPartcleEmitter* e_02 = new cPartcleEmitter;
	e_02->SetActive(true);

	LPDIRECT3DTEXTURE9 pTex2 = RESOURCE_TEXTURE->GetResource("./Tera/Effect/A_blood_ring05_emis.tga");

	e_02->Init(
		1,
		30.0f,
		1.f,
		3.f,
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(1, 1, 1),
		D3DXVECTOR3(-1, -1, -1),
		color, scale,
		0.8f, 0.8f,
		pTex2,
		false
		);

	m_vecAttackEffect2.push_back(e_01);
	m_vecAttackEffect2.push_back(e_02);


	for (int i = 0; i < 3; i++)
	{
		cTrailRender* t = new cTrailRender;
		t->Init(
			0.3f,
			1.5f,
			RESOURCE_TEXTURE->GetResource("./Tera/Effect/Lens_Flare_A001_EMIS.tga"),	//메인 Texture
			D3DXCOLOR(1, 0.2, 0, 0.7),												//메인 Texture 로 그릴때 컬러
			RESOURCE_TEXTURE->GetResource("./Tera/Effect/Lens_Flare_A001_EMIS.tga")	//외곡 그릴때 외곡 노말
			);
		m_vecAttackEffect.push_back(t);
	}

}
