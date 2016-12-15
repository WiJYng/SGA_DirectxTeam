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

}

void cEnemyEffect::Render()
{
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	Device->SetRenderState(D3DRS_ALPHAREF, 0.5f);
	
	//Render
	//=================================================



	//=================================================

	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, false);
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



}

void cEnemyEffect::EnemyAttackEffect_02(D3DXVECTOR3 pos)
{

}

//Skill Init
void cEnemyEffect::EnemyEffectInit()
{
	//m_stingEffect

}
