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
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);

	if (Pos)
	{
		mat._41 = Pos->x;
		mat._42 = Pos->y;
		mat._43 = Pos->z;
	}

	Setup(PathMonster, &mat);
}

void cEnemy::Setup(string PathMonster, D3DXMATRIXA16 * mat)
{
	//기본 1개의 파츠로 이루어져있다
	this->renderObjects.reserve(1);

	cXMesh_Skinned* pMonster = RESOURCE_SKINNEDXMESH->GetResource(PathMonster, mat);

	//cTransform* Transform = new cTransform();

	cBaseObject* pMonObj = new cBaseObject();
	pMonObj->SetMesh(pMonster);
	pMonObj->SetActive(true);
	pMonObj->pTransform->SetWorldMatrix(*mat);

	renderObjects.push_back(pMonObj);

	renderObjects[0]->pSkinned->Play("Wait", 0.0f);
}

void cEnemy::Update(float timDelta, cMeshMap * _Map)
{
	renderObjects[0]->Update(timDelta);

	float y = _Map->GetHeight(renderObjects[0]->pTransform->GetWorldPosition().x, renderObjects[0]->pTransform->GetWorldPosition().z);
	if (_Map && y)
	{
		D3DXVECTOR3 vTemp = D3DXVECTOR3(renderObjects[0]->pTransform->GetWorldPosition().x, y, renderObjects[0]->pTransform->GetWorldPosition().z);
		renderObjects[0]->pTransform->SetWorldPosition(vTemp);
	}
}

void cEnemy::Render()
{
	renderObjects[0]->Render();
	renderObjects[0]->BoundBox.RenderGizmo(renderObjects[0]->pTransform);
}
