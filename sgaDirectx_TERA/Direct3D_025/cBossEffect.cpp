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
	m_isGaPlay = false;

	BossSkillEffectInit();
}

void cBossEffect::Update(float _delta)
{
	m_pGroundAttack->Update(_delta);
	m_pTail->Update(_delta);
	m_vecAttackEffect[0]->Update(_delta);
	m_vecAttackEffect[1]->Update(_delta);
}

void cBossEffect::Render()
{
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	Device->SetRenderState(D3DRS_ALPHAREF, 0.5f);

	//Render
	//=================================================

	m_vecAttackEffect[0]->Render();
	m_vecAttackEffect[1]->Render();
	
	m_pGroundAttack->Render();

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
	case BOSS_ATTACK_GROUND:
		PlayBossGroundAttack(pos, true);
		break;
	case BOSS_ATTACK_GROUND_STOP:
		PlayBossGroundAttack(pos, false);
		break;
	case BOSS_ATTACK_01:
		PlayBossAttackEffect(pos);
		break;
	default:
		break;
	}
}

void cBossEffect::PlayBossTail(D3DXVECTOR3 pos)
{
	m_pTail->Transform.SetWorldPosition(pos);
}

void cBossEffect::PlayBossGroundAttack(D3DXVECTOR3 pos, bool isOn)
{
	if (isOn && !m_isGaPlay)
	{
		m_pGroundAttack->pTransform->SetWorldPosition(pos);
		m_pGroundAttack->StartEmission();
		m_isGaPlay = true;
	}
	else if (!isOn && m_isGaPlay)
	{
		m_pGroundAttack->StopEmission();
		m_isGaPlay = false;
	}
}

void cBossEffect::PlayBossAttackEffect(D3DXVECTOR3 pos)
{
	m_vecAttackEffect[0]->pTransform->SetWorldPosition(pos);
	m_vecAttackEffect[1]->pTransform->SetWorldPosition(pos);

	m_vecAttackEffect[0]->Burst(200, 0.8f, 1.0f, 0.1f, 0.2f);
	m_vecAttackEffect[1]->Burst(5, 1.0f, 1.0f, 0.1f, 0.1f);
}

void cBossEffect::BossSkillEffectInit()
{
	//======================================
	// 1. ���� ���ݽ� 
	//======================================
	m_pTail = new cTrailRender();
	m_pTail->Init(
		1.0f,					//���� ���̺� Ÿ�� ( �̰� ũ�� ȯ��ť ����� Ŀ���� ������ �������� �����ִ� )
		2.7f,					//��
		RESOURCE_TEXTURE->GetResource("./Tera/Effect/E_Swordtrail005_emis.tga"),	//���� Texture
		D3DXCOLOR(1, 0.1, 0.7, 0.7),												//���� Texture �� �׸��� �÷�
		RESOURCE_TEXTURE->GetResource("./Tera/Effect/E_Swordtrail004_emis.tga")	//�ܰ� �׸��� �ܰ� �븻
		);

	//======================================
	// 2. ������ ���� ��� ����� ��
	//======================================

	m_pGroundAttack = new cQuadParticleEmitter();
	m_pGroundAttack->SetActive(true);

	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	VEC_SCALE scales;
	scales.push_back(3.0f);
	scales.push_back(3.5f);

	m_pGroundAttack->Init(
		20,
		20,
		0.2f,
		0.3f,
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(-90 * ONE_RAD, 0, 90 * ONE_RAD),		//�ʱ���۽� ȸ��Min
		D3DXVECTOR3(-90 * ONE_RAD, 0, 0),					//�ʱ���۽� ȸ��Max
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ���� ȸ�� �� Min
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ���� ȭ�� �� Max
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ�� ���� Min
		D3DXVECTOR3(0, 0, 0),				//�ʴ� ȸ�� ���� Max
		colors, scales,
		2.f, 3.0f,
		RESOURCE_TEXTURE->GetResource("./Tera/Effect/C_Crak.png"),
		true);

	//======================================
	// 3. ������ �÷��̾ �������� ��
	//======================================
	cPartcleEmitter* e_01 = new cPartcleEmitter;
	e_01->SetActive(true);

	VEC_COLOR color;
	color.push_back(D3DXCOLOR(1.0f, 0.2f, 0.7f, 1.0f));
	color.push_back(D3DXCOLOR(1.0f, 0.3f, 0.9f, 1.0f));

	VEC_SCALE scale;
	scale.push_back(0.8f);
	scale.push_back(1.5f);

	LPDIRECT3DTEXTURE9 pTex = RESOURCE_TEXTURE->GetResource("./Tera/Effect/F_ring003_emis.tga");

	e_01->Init(
		20,
		40.0f,
		1.f,
		1.2,
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(1, 1, 1),
		D3DXVECTOR3(-1, -1, -1),
		color, scale,
		0.8f, 0.8f,
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
		1.3f,
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(1, 1, 1),
		D3DXVECTOR3(-1, -1, -1),
		color, scale,
		1.2f, 1.2f,
		pTex2,
		false
		);

	m_vecAttackEffect.push_back(e_01);
	m_vecAttackEffect.push_back(e_02);
}