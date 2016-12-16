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

}


//Skill Init
void cEnemyEffect::EnemyEffectInit()
{	
	//busrt로 그려도 괜찮을거같은..?

	for (int i = 0; i < 3; i++)
	{
		cTrailRender* t = new cTrailRender;
		t->Init(
			0.3f,
			2.0f,
			RESOURCE_TEXTURE->GetResource("./Tera/Effect/Lens_Flare_A001_EMIS.tga"),	//메인 Texture
			D3DXCOLOR(1, 0.2, 0, 0.7),												//메인 Texture 로 그릴때 컬러
			RESOURCE_TEXTURE->GetResource("./Tera/Effect/Lens_Flare_A001_EMIS.tga")	//외곡 그릴때 외곡 노말
			);
		m_vecAttackEffect.push_back(t);
	}


}
