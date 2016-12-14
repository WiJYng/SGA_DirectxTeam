#include "stdafx.h"
#include "cPlayerSkillEffect.h"


cPlayerSkillEffect::cPlayerSkillEffect()
{
}


cPlayerSkillEffect::~cPlayerSkillEffect()
{
	//Trail ����
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
	for each(auto v in m_vecAttackEffect)
	{
		v->Render();
	}

	//�����̹Ƿ� �������� �׸�
	for each(auto v in m_vectailEffect)
	{
		v->Render();
	}
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
	m_vectailEffect[0]->Render();
}

void cPlayerSkillEffect::PlayerAttackEffect_01_R(D3DXVECTOR3 pos)
{
	m_vectailEffect[1]->Transform.SetWorldPosition(pos);
	m_vectailEffect[1]->Render();
}

void cPlayerSkillEffect::PlayerAttackEffect_02(D3DXVECTOR3 pos)
{
	//����effect index 0, 1
	m_vecAttackEffect[0]->pTransform->SetWorldPosition(pos);
	m_vecAttackEffect[1]->pTransform->SetWorldPosition(pos);


	m_vecAttackEffect[0]->Burst(200, 0.8f, 1.0f, 0.1f, 0.2f);
	m_vecAttackEffect[1]->Burst(5, 1.0f, 1.0f, 0.1f, 0.1f);
}



void cPlayerSkillEffect::InitPlayerSkill()
{
	//Default Init
	//�ʿ��� effect�� �̰����� �ε��Ѵ�.

	//-----------------------------------------
	//	1.�ܹ߰�������Ʈ
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
	// 2. ���ݽ� �˼� ����Ʈ
	//--------------------------------------------
	//TrailRenderSet
	cTrailRender* t1 = new cTrailRender();
	t1->Init(
		0.2f,					//���� ���̺� Ÿ�� ( �̰� ũ�� ȯ��ť ����� Ŀ���� ������ �������� �����ִ� )
		0.7f,					//��
		RESOURCE_TEXTURE->GetResource("./Tera/Effect/E_Swordtrail005_emis.tga"),	//���� Texture
		D3DXCOLOR(0, 0.5, 1, 0.7),												//���� Texture �� �׸��� �÷�
		RESOURCE_TEXTURE->GetResource("./Tera/Effect/E_Swordtrail004_emis.tga")	//�ܰ� �׸��� �ܰ� �븻
		);

	cTrailRender* t2 = new cTrailRender();
	t2->Init(
		0.2f,					//���� ���̺� Ÿ�� ( �̰� ũ�� ȯ��ť ����� Ŀ���� ������ �������� �����ִ� )
		0.7f,					//��
		RESOURCE_TEXTURE->GetResource("./Tera/Effect/E_Swordtrail005_emis.tga"),	//���� Texture
		D3DXCOLOR(0, 0.5, 1, 0.7),												//���� Texture �� �׸��� �÷�
		RESOURCE_TEXTURE->GetResource("./Tera/Effect/E_Swordtrail004_emis.tga")	//�ܰ� �׸��� �ܰ� �븻
		);

	//���� ������ �ΰ�
	m_vectailEffect.push_back(t1);
	m_vectailEffect.push_back(t2);
}