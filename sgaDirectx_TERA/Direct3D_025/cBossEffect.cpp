#include "stdafx.h"
#include "cBossEffect.h"


cBossEffect::cBossEffect()
{
}

cBossEffect::~cBossEffect()
{
}

void cBossEffect::Setup()
{
	BossSkillEffectInit();
}

void cBossEffect::Update(float _delta)
{
	m_pTail->Update(_delta);
}

void cBossEffect::Render()
{
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	Device->SetRenderState(D3DRS_ALPHAREF, 0.5f);

	//Render
	//=================================================

	if (m_pTail) m_pTail->Render();

	//=================================================

	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}

void cBossEffect::PlayEffect(EFFECT_NAME _Name, D3DXVECTOR3 pos)
{
	switch(_Name)
	{
	case BOSS_ATTACK:
		PlayBossTail(pos);

		break;
	default:
		break;
	}
}

void cBossEffect::PlayBossTail(D3DXVECTOR3 pos)
{
	m_pTail->Transform.SetWorldPosition(pos);
}

void cBossEffect::BossSkillEffectInit()
{

	m_pTail = new cTrailRender();
	m_pTail->Init(
		1.0f,					//���� ���̺� Ÿ�� ( �̰� ũ�� ȯ��ť ����� Ŀ���� ������ �������� �����ִ� )
		2.7f,					//��
		RESOURCE_TEXTURE->GetResource("./Tera/Effect/E_Swordtrail005_emis.tga"),	//���� Texture
		D3DXCOLOR(1, 0.4, 1, 0.7),												//���� Texture �� �׸��� �÷�
		RESOURCE_TEXTURE->GetResource("./Tera/Effect/E_Swordtrail004_emis.tga")	//�ܰ� �׸��� �ܰ� �븻
		);
}