#include "stdafx.h"
#include "cEnemy.h"
#include "cMeshMap.h"
#include "cTransform.h"
#include "cSkinnedAnimation.h"


cEnemy::cEnemy()
{
}


cEnemy::~cEnemy()
{
	SAFE_DELETE(pMonTrans);
	SAFE_DELETE(pWeaponTrans);
}

void cEnemy::Setup(string PathMonster, D3DXVECTOR3* Pos)
{
	m_State = Wait;
	bWait = true;
	bRun = false;
	bAtt = false;
	bDeath = false;
	PrevAngle = 0.0f;

	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);

	//if (Pos)
	//{
	//	D3DXMatrixTranslation(&mat, Pos->x, Pos->y, Pos->z);
	//}

	Setup(PathMonster, &mat, Pos);
}

void cEnemy::Setup(string PathMonster, D3DXMATRIXA16 * mat, D3DXVECTOR3* Pos)
{
	//기본 1개의 파츠로 이루어져있다
	this->renderObjects.reserve(1);

	cXMesh_Skinned* pMonster = RESOURCE_SKINNEDXMESH->GetResource(PathMonster, mat);

	pMonTrans = new cTransform();
	pWeaponTrans = new cTransform();

	cBaseObject* pMonObj = new cBaseObject();
	pMonObj->SetMesh(pMonster);
	pMonObj->SetActive(true);
	pMonObj->pTransform->SetWorldPosition(*Pos);
	pMonObj->pSkinned->AddBoneTransform("Dummy_root", pMonTrans);
	pMonObj->pSkinned->AddBoneTransform("Bip01-Prop1", pWeaponTrans);

	renderObjects.push_back(pMonObj);

	renderObjects[0]->pSkinned->Play("Wait", 0.0f);
	renderObjects[0]->BoundBox.Init(D3DXVECTOR3(-0.4, 0, -0.5), D3DXVECTOR3(0.4, 1, 0.25));
	renderObjects[0]->BoundBox01.Init(D3DXVECTOR3(-0.1, 0, -0.1), D3DXVECTOR3(0.1, 1.0, 0.1));
}

void cEnemy::Release()
{
	SAFE_DELETE(pMonTrans);
	SAFE_DELETE(pWeaponTrans);
	
}

void cEnemy::Update(float timDelta, cMeshMap * _Map, D3DXVECTOR3* _PlayerPos)
{
	renderObjects[0]->Update(timDelta);

	

	float len = CalcLen(_PlayerPos, &renderObjects[0]->pTransform->GetWorldPosition());
	float angle = CalcAngle(_PlayerPos, &renderObjects[0]->pTransform->GetWorldPosition());

	if (m_State != Death && !bDeath)
	{
		if (len > 30.0f)
		{
			if (m_State != Wait && !bWait)
			{
				renderObjects[0]->pSkinned->Play("Wait", 0.0f);
				m_State = Wait;
				bWait = true;
				bRun = bAtt = false;
			}
		}
		else if (len <= 30.0f && len > 5.0f)
		{
			if (m_State != Run && !bRun)
			{
				renderObjects[0]->pSkinned->Play("Run", 0.0f);
				m_State = Run;
				bRun = true;
				bWait = bAtt = false;
			}



			if (PrevAngle != angle)
			{
				D3DXMATRIXA16 RotY, mat;
				D3DXMatrixIdentity(&RotY);
				D3DXMatrixRotationY(&RotY, angle);
				mat = RotY * renderObjects[0]->pTransform->GetFinalMatrix();

				renderObjects[0]->pTransform->SetWorldMatrix(mat);
			}
		}
		else if (len <= 5.0f && len > 0.0f)
		{
			if (m_State != Attack && !bAtt)
			{
				renderObjects[0]->pSkinned->Play("Attack", 0.0f);
				m_State = Attack;
				bAtt = true;
				bWait = bRun = false;
			}
		}
	}
	else if (m_State == Death && !bDeath)
	{
		if (renderObjects[0]->pSkinned->GetFactor() >= 0.95f)
		{
			if (m_State != DeathWait)
			{
				D3DXVECTOR3 vTemp = D3DXVECTOR3(pMonTrans->GetWorldPosition().x, 0.0f, pMonTrans->GetWorldPosition().z);
				renderObjects[0]->pTransform->SetWorldPosition(vTemp);

				renderObjects[0]->pSkinned->Play("DeathWait", 0.0f);
				m_State = DeathWait;
				bDeath = true;
				bWait = bRun = bAtt = false;
			}
		}
	}
	

	if (KEY_MGR->IsOnceDown('1'))
	{
		if (m_State != Death)
		{
			renderObjects[0]->pSkinned->PlayOneShotAfterHold("Death", 0.0f);
			m_State = Death;
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
		
	}
	
	PrevAngle = angle;

	char str[1024];
	sprintf_s(str, "%.2f", len);
	//sprintf_s(str, "%.2f", angle);
	LOG_MGR->AddLog(str);
}

void cEnemy::Render()
{
	renderObjects[0]->Render();
	renderObjects[0]->BoundBox.RenderGizmo(pMonTrans);
	renderObjects[0]->BoundBox01.RenderGizmo(pWeaponTrans);
}

float cEnemy::CalcLen(D3DXVECTOR3 * _PlayerPos, D3DXVECTOR3 * _ThisPos)
{
	float x = abs(_PlayerPos->x - _ThisPos->x);
	float y = abs(_PlayerPos->y - _ThisPos->y);
	float z = abs(_PlayerPos->z - _ThisPos->z);

	float len = (x * x) + (y * y) + (z * z);

	return len;
}

float cEnemy::CalcAngle(D3DXVECTOR3 * _PlayerPos, D3DXVECTOR3 * _ThisPos)
{
	float x = _PlayerPos->x - _ThisPos->x;
	float z = _PlayerPos->z - _ThisPos->z;

	float distance = sqrtf(x * x + z * z);
	float angle = acosf(x / distance);

	//if (z > 0) angle = PI2 - angle;

	return angle;
}
