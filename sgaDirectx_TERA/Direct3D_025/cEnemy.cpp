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
}

void cEnemy::Setup(string PathMonster, D3DXVECTOR3* Pos)
{
	m_State = Wait;
	bWait = true;
	bRun = false;
	bAtt = false;

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

	//cTransform* Transform = new cTransform();

	cBaseObject* pMonObj = new cBaseObject();
	pMonObj->SetMesh(pMonster);
	pMonObj->SetActive(true);
	pMonObj->pTransform->SetWorldPosition(*Pos);

	renderObjects.push_back(pMonObj);

	renderObjects[0]->pSkinned->Play("Wait", 0.0f);
}

void cEnemy::Update(float timDelta, cMeshMap * _Map, D3DXVECTOR3* _PlayerPos)
{
	renderObjects[0]->Update(timDelta);

	float len = CalcLen(_PlayerPos, &renderObjects[0]->pTransform->GetWorldPosition());

	if (len > 15.0f)
	{
		if (m_State != Wait && !bWait)
		{
			renderObjects[0]->pSkinned->Play("Wait", 0.0f);
			m_State = Wait;
			bWait = true;
			bRun = bAtt = false;
		}
	}
	else if (len <= 15.0f && len > 5.0f)
	{
		if (m_State != Run && !bRun)
		{
			renderObjects[0]->pSkinned->Play("Run", 0.0f);
			m_State = Run;
			bRun = true;
			bWait = bAtt = false;
		}
	}
	else if (len <= 2.0f && len > 0.0f)
	{
		if (m_State != Run && !bRun)
		{
			renderObjects[0]->pSkinned->Play("Run", 0.0f);
			m_State = Run;
			bRun = true;
			bWait = bAtt = false;
		}
	}

	float y = _Map->GetHeight(renderObjects[0]->pTransform->GetWorldPosition().x, renderObjects[0]->pTransform->GetWorldPosition().z);
	if (_Map && y)
	{
		D3DXVECTOR3 vTemp = D3DXVECTOR3(renderObjects[0]->pTransform->GetWorldPosition().x, y, renderObjects[0]->pTransform->GetWorldPosition().z);
		renderObjects[0]->pTransform->SetWorldPosition(vTemp);
	}
	
	char str[1024];
	sprintf_s(str, "%.2f", len);
	//sprintf_s(str, "%.2f, %.2f, %.2f", _PlayerPos->x, _PlayerPos->y, _PlayerPos->z);
	//sprintf_s(str, "%.2f, %.2f, %.2f", renderObjects[0]->pTransform->GetWorldPosition().x, renderObjects[0]->pTransform->GetWorldPosition().y, renderObjects[0]->pTransform->GetWorldPosition().z);
	LOG_MGR->AddLog(str);
}

void cEnemy::Render()
{
	renderObjects[0]->Render();
	//renderObjects[0]->BoundBox.RenderGizmo(renderObjects[0]->pTransform);
}

float cEnemy::CalcLen(D3DXVECTOR3 * _PlayerPos, D3DXVECTOR3 * _ThisPos)
{
	float x = abs(_PlayerPos->x - _ThisPos->x);
	float y = abs(_PlayerPos->y - _ThisPos->y);
	float z = abs(_PlayerPos->z - _ThisPos->z);

	float len = (x * x) + (y * y) + (z * z);

	return len;
}
