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

void cEnemyEffect::PlayEffect(EFFECT_NAME _Name, cTransform* trans)
{
	switch (_Name)
	{
	case ENEMY_ATTACK_01:
		EnemyAttackEffect_01(trans);
		break;
	case ENEMY_ATTACK_02:
		EnemyAttackEffect_02(trans);
		break;
	default:
		break;
	}
}


void cEnemyEffect::EnemyAttackEffect_01(D3DXVECTOR3 pos)
{
	//ȸ������Ʈ�� �߰��ɼ����� �߰��Ǹ� �����Ͱ���
	if (this->m_fxEffect == NULL)
		m_fxEffect = NULL;

	for each(auto v in m_vecAttackEffect)
	{
		v->Transform.SetWorldPosition(pos);
	}
}

void cEnemyEffect::EnemyAttackEffect_01(cTransform* trans)
{
	for each(auto v in m_vecAttackEffect)
	{
		v->Transform = *trans;
	}
}


void cEnemyEffect::EnemyAttackEffect_02(D3DXVECTOR3 pos)
{

}

void cEnemyEffect::EnemyAttackEffect_02(cTransform* trans)
{

}

//Skill Init
void cEnemyEffect::EnemyEffectInit()
{	
	//busrt�� �׷��� �������Ű���..?

	for (int i = 0; i < 3; i++)
	{
		cTrailRender* t = new cTrailRender;
		t->Init(
			0.3f,
			2.0f,
			RESOURCE_TEXTURE->GetResource("./Tera/Effect/A_Sim_Side.tga"),	//���� Texture
			D3DXCOLOR(1, 0.2, 0, 0.7),												//���� Texture �� �׸��� �÷�
			RESOURCE_TEXTURE->GetResource("./Tera/Effect/A_Sim_Side.tga")	//�ܰ� �׸��� �ܰ� �븻
			);
		m_vecAttackEffect.push_back(t);
	}


}
