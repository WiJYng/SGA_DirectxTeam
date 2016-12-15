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

	//m_stingEffect->Render();

	for each(auto v in m_vecAttackEffect)
	{
		v->Render();
	}

	//=================================================

	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	Device->SetRenderState(D3DRS_LIGHTING, prevLight);
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	
}

void cEnemyEffect::PlayEffect(EFFECT_NAME _Name, D3DXVECTOR3 pos)
{
	//if (pos == NULL)
	//	pos = D3DXVECTOR3(0, 0, 0);
	//
	//switch (_Name)
	//{
	//case ENEMY_ATTACK_01:
	//	EnemyAttackEffect_01(pos);
	//	break;
	//case ENEMY_ATTACK_02:
	//	EnemyAttackEffect_02(pos);
	//	break;
	//default:
	//	break;
	//}
}


void cEnemyEffect::PlayEffect(EFFECT_NAME _Name, D3DXVECTOR3 pos, int idx)
{
	switch (_Name)
	{
	case ENEMY_ATTACK_01:
		EnemyAttackEffect_01(pos, idx);
		break;
	case ENEMY_ATTACK_02:
		EnemyAttackEffect_02(pos, idx);
		break;
	default:
		break;
	}
}


void cEnemyEffect::EnemyAttackEffect_01(D3DXVECTOR3 pos, int idx)
{
	//회전이펙트가 추가될수있음 추가되면 좋을것같음
	if (this->m_fxEffect == NULL)
		m_fxEffect = NULL;

	m_vecAttackEffect[idx]->Transform.SetWorldPosition(pos);
	//m_vecAttackEffect[idx]->Render();
}

void cEnemyEffect::EnemyAttackEffect_02(D3DXVECTOR3 pos, int idx)
{

}

//Skill Init
void cEnemyEffect::EnemyEffectInit()
{	
	for (int i = 0; i < ENEMYMAXCNT; i++)
	{
		cTrailRender* t = new cTrailRender;
		t->Init(
			0.2f,
			1.0f,
			RESOURCE_TEXTURE->GetResource("./Tera/Effect/A_Sim_Side.tga"),	//메인 Texture
			D3DXCOLOR(1, 0.2, 0, 0.7),												//메인 Texture 로 그릴때 컬러
			RESOURCE_TEXTURE->GetResource("./Tera/Effect/A_Sim_Side.tga")	//외곡 그릴때 외곡 노말
			);
		m_vecAttackEffect.push_back(t);
	}

	//cQuadParticleEmitter* e_01 = new cQuadParticleEmitter;
	//e_01->SetActive(true);
	//
	//VEC_COLOR color;
	//color.push_back(D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
	//color.push_back(D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
	//color.push_back(D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
	//
	//VEC_SCALE scale;
	//scale.push_back(1.0f);
	//scale.push_back(1.0f);
	//
	//e_01->Init(
	//	1,
	//	2.f,
	//	1.f,
	//	1.f,
	//	D3DXVECTOR3(0, 1, 0),
	//	D3DXVECTOR3(0, 1, 0),
	//	D3DXVECTOR3(0, 1, 0),
	//	D3DXVECTOR3(0, 1, 0),
	//	D3DXVECTOR3(-90 * ONE_RAD, 0, 0),		//초기시작시 회전Min
	//	D3DXVECTOR3(-90 * ONE_RAD, 0, 0),		 			 //초기시작시 회전Max
	//	D3DXVECTOR3(0, 0, 0.5),				//초당 회전할 회전 량 Min
	//	D3DXVECTOR3(0, 0, 0.5),				//초당 회전할 회전 량 Max
	//	D3DXVECTOR3(0, 0, 0),				//초당 회전 가속 Min
	//	D3DXVECTOR3(0, 0, 0),				//초당 회전 가속 Max
	//	color, scale,
	//	1.f, 1.f,
	//	RESOURCE_TEXTURE->GetResource("./Tera/Effect/A_Sim_Side.tga"),
	//	true);
	//
	//
	//m_vecAttackEffect.push_back(e_01);
	
	//D3DXMATRIXA16 matCorrection;
	//D3DXMatrixIdentity(&matCorrection);
	//D3DXMatrixScaling(&matCorrection, 0.01, 0.01, 0.01);
	//
	//cXMesh_Static* mesh = RESOURCE_STATICXMESH->GetResource("./Tera/Effect/eff_sting.X", matCorrection);
	//m_stingEffect = new cBaseObject();
	//
	//m_stingEffect->SetMesh(mesh);
	//m_stingEffect->SetActive(false);

}
