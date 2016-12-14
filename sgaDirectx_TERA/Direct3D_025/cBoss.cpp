#include "stdafx.h"
#include "cBoss.h"
#include "cMeshMap.h"
#include "cTransform.h"
#include "cTickFunc.h"

cBoss::cBoss()
{
}


cBoss::~cBoss()
{
}

void cBoss::Setup(string PathMonster, D3DXVECTOR3 * Pos)
{
	m_State = UWait;
	bUWait = true;
	bWait = false;
	bRun = false;
	bAtt = false;
	bDeath = false;
	bStun = false;
	PrevAngle = 0.0f;
	m_nCount = 0;
	for (int i = 0; i < 3; i++)
	{
		m_pTick[i] = new cTickFunc();
		m_pTick[i]->init(0.7f);
	}
	
	m_pTick[0]->init(2.1f);
	m_pTick[1]->init(0.7f);
	m_pTick[2]->init(0.7f);

	m_fHP = m_fMAXHP = 10.0f;

	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);

	Setup(PathMonster, &mat, Pos);
}

void cBoss::Setup(string PathMonster, D3DXMATRIXA16 * mat, D3DXVECTOR3 * Pos)
{
	//�⺻ 1���� ������ �̷�����ִ�
	this->renderObjects.reserve(1);

	cXMesh_Skinned* pMonster = RESOURCE_SKINNEDXMESH->GetResource(PathMonster, mat);

	pMonTrans = new cTransform();
	pWeaponTrans = new cTransform();
	
	cBaseObject* pMonObj = new cBaseObject();
	pMonObj->SetMesh(pMonster);
	pMonObj->SetActive(true);
	pMonObj->pTransform->SetWorldPosition(*Pos);
	pMonObj->pTransform->RotateSelf(0.0f, 90.0f * ONE_RAD, 0.0f);
	pMonObj->pSkinned->AddBoneTransform("Dummy_root", pMonTrans);
	pMonObj->pSkinned->AddBoneTransform("Bip01-R-Hand", pWeaponTrans);
	
	renderObjects.push_back(pMonObj);
	
	renderObjects[0]->pSkinned->Play("Unarmedwait", 0.0f);
	renderObjects[0]->BoundBox.Init(D3DXVECTOR3(-1.0, 0, -1.0), D3DXVECTOR3(1.0, 2.5, 1.0));
	renderObjects[0]->BoundBox01.Init(D3DXVECTOR3(-0.7, -0.4, 0.0), D3DXVECTOR3(0.7, 0.6, 1.6));
}

void cBoss::Update(float timDelta, cMeshMap * _Map, D3DXVECTOR3 * _PlayerPos)
{
	renderObjects[0]->Update(timDelta);
	
	//���� ����
	D3DXVECTOR3 currentPos = renderObjects[0]->pTransform->GetWorldPosition();
	
	//float len = CalcLen(_PlayerPos, &renderObjects[0]->pTransform->GetWorldPosition());
	D3DXVECTOR3 dirToTarget = *_PlayerPos - renderObjects[0]->pTransform->GetWorldPosition();
	float dist = D3DXVec3Length(&dirToTarget);
	dirToTarget.y = 0;
	
	//float angle = CalcAngle(_PlayerPos, &renderObjects[0]->pTransform->GetWorldPosition());
	
	if (m_State != Stun && m_State != Death && m_State != DeathWait && dist <= 15.0f)
	{
		//������ ���Ѵ�.
		D3DXVec3Normalize(&dirToTarget, &dirToTarget);
		dirToTarget.y = 0;
		D3DXVECTOR3 forward = renderObjects[0]->pTransform->GetForward();
		forward.y = 0;
		D3DXVec3Normalize(&forward, &forward);
	
		float angle = acosf(D3DXVec3Dot(&dirToTarget, &forward));
		if (angle >= 90 * ONE_RAD)
		{
			renderObjects[0]->pTransform->RotateSelf(0, 5 * ONE_RAD, 0);
	
			//LOG_MGR->AddLog("%.2f, %d", angle * 180 / 3.14, m_nIndex);
		}
	
	
	
		D3DXVECTOR3 lerp = renderObjects[0]->pTransform->GetForward();
		D3DXVec3Lerp(&lerp, &lerp, &dirToTarget, 0.2);
		renderObjects[0]->pTransform->LookDirection(lerp, renderObjects[0]->pTransform->GetUp());
	}
	
	//�̵���
	float deltaMove = 5.0f * TIME_MGR->GetFrameDeltaSec();
	float t = Clamp01(deltaMove / dist);
	
	if (m_State != Death && !bDeath && !bStun)
	{
		if (dist > 15.0f)
		{
			if (m_State != UWait && !bUWait)
			{
				renderObjects[0]->pSkinned->Play("Unarmedwait", 0.0f);
				m_State = UWait;
				bUWait = true;
				bRun = bAtt = bWait = false;
			}
		}
		else if (dist <= 15.0f && dist > 10.0f)
		{
			if (m_State != Wait && !bWait)
			{
				renderObjects[0]->pSkinned->Play("Wait", 0.0f);
				m_State = Wait;
				bWait = true;
				bRun = bAtt = bUWait = false;
			}
		}
		else if (dist <= 10.0f && dist > 2.75f)
		{
			if (m_State != Run && !bRun)
			{
				renderObjects[0]->pSkinned->Play("Run", 0.0f);
				m_State = Run;
				bRun = true;
				bWait = bAtt = bWait = false;
			}
			renderObjects[0]->pTransform->MovePositionWorld(renderObjects[0]->pTransform->GetForward()*timDelta);
	
		}
		else if (dist <= 2.75f && dist > 0.0f)
		{
			if (m_State != Attack && !bAtt)
			{
				m_nCount = 0;
				//renderObjects[0]->pSkinned->Play("Attack1", 0.0f);
				m_State = Attack;
				bAtt = true;
				bWait = bRun = bWait = false;
				//m_nCount++;
			}
			else if (m_State == Attack)
			{
				AttackFuntion(timDelta);
			}
		}
	}
	else if (m_State == Death && !bDeath && bStun)
	{
		if (renderObjects[0]->pSkinned->GetFactor() >= 0.95f)
		{
			if (m_State != DeathWait)
			{
				D3DXVECTOR3 vTemp = D3DXVECTOR3(pMonTrans->GetWorldPosition().x, 0.0f, pMonTrans->GetWorldPosition().z);
				renderObjects[0]->pTransform->SetWorldPosition(vTemp);
				
				renderObjects[0]->pSkinned->Play("Deathwait", 0.0f);
				m_State = DeathWait;
				bDeath = true;
				bWait = bRun = bAtt = bWait = false;
			}
		}
	}
	
	if (m_fHP <= 0.0f && !bStun)
	{
		if (m_State != Death)
		{
			renderObjects[0]->pSkinned->PlayOneShotAfterHold("Death", 0.0f);
			m_State = Death;
			bStun = true;
			bWait = bRun = bAtt = false;
		}
	}
	
	
	if (_Map)
	{
		if (m_State != Death)
		{
			float y = _Map->GetHeight(renderObjects[0]->pTransform->GetWorldPosition().x, renderObjects[0]->pTransform->GetWorldPosition().z);
			D3DXVECTOR3 vTemp = D3DXVECTOR3(renderObjects[0]->pTransform->GetWorldPosition().x, y, renderObjects[0]->pTransform->GetWorldPosition().z);
			renderObjects[0]->pTransform->SetWorldPosition(vTemp);
		}
		else
		{
			float y = _Map->GetHeight(pMonTrans->GetWorldPosition().x, pMonTrans->GetWorldPosition().z);
			D3DXVECTOR3 vTemp = D3DXVECTOR3(renderObjects[0]->pTransform->GetWorldPosition().x, y, renderObjects[0]->pTransform->GetWorldPosition().z);
			renderObjects[0]->pTransform->SetWorldPosition(vTemp);
		}
		int a = 0;
	}

	//LOG_MGR->AddLog("%d", m_nCount);
}

void cBoss::Render()
{
	renderObjects[0]->Render();
	//renderObjects[0]->BoundBox.RenderGizmo(pMonTrans);
	//renderObjects[0]->BoundBox01.RenderGizmo(pWeaponTrans);
}

void cBoss::AttackFuntion(float timDelta)
{
	if (m_nCount % 5 == 0 || m_nCount % 5 == 1 || m_nCount % 5 == 2)
	{
		m_pTick[0]->tickUpdate(timDelta);
		//if (renderObjects[0]->pSkinned->GetFactor() >= 0.999f)
		if (renderObjects[0]->pSkinned->GetAniEnd())
		{
			renderObjects[0]->pSkinned->Play("Attack1", 0.0f);
			m_State = Attack;
			bAtt = true;
			bWait = bRun = false;
		}
		if (m_pTick[0]->tickStart())
		{
			m_nCount++;
			//LOG_MGR->AddLog("��������1");
		}
	}
	else if (m_nCount % 5 == 3)
	{
		if (renderObjects[0]->pSkinned->GetAniEnd())
		{
			renderObjects[0]->pSkinned->Play("Attack2", 0.0f);
			m_State = Attack;
			bAtt = true;
			bWait = bRun = false;
			m_nCount++;
		}
		int a = 0;
	}
	else if (m_nCount % 5 == 4)
	{
		if (renderObjects[0]->pSkinned->GetAniEnd())
		{
			renderObjects[0]->pSkinned->Play("Attack3", 0.0f);
			m_State = Attack;
			bAtt = true;
			bWait = bRun = false;
			m_nCount++;
		}
	}
}