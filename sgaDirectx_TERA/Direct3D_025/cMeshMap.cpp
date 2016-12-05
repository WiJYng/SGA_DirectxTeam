#include "stdafx.h"
#include "cMeshMap.h"
#include "cXMesh_Static.h"


cMeshMap::cMeshMap()
{
}


cMeshMap::~cMeshMap()
{
}


void cMeshMap::Setup(string PathMap)
{
	D3DXMATRIXA16 matCorrection;
	D3DXMatrixIdentity(&matCorrection);

	//Map
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 0, -10, 0);
	D3DXMatrixRotationY(&matT, 180.0f * ONE_RAD);
	matCorrection = matT;

	Setup(PathMap, &matCorrection);
}

void cMeshMap::Setup(string PathMap, D3DXMATRIXA16* mat)
{
	cXMesh_Static* mesh = RESOURCE_STATICXMESH->GetResource(PathMap, mat);
	mesh->SetTechniqueName("Distort");
	//m_pTerrainEffect = RESOURCE_FX->GetResource( "./Resources/Shaders/TerrainBase.fx");

	


	pMap = new cBaseObject();
	pMap->SetMesh(mesh);
	pMap->SetActive(true);
	pMap->IgnoreCreateShadow = true;		//그림자 안그린다.
	pMap->ApplyShadow = false;
}

void cMeshMap::Render()
{
	if (pMap)
		pMap->Render();
}

float cMeshMap::GetHeight(float x, float z)
{
	float result = 0;
	float buffer = 99999;

	LPRay vR;
	vR->origin = D3DXVECTOR3(x, buffer, z);
	vR->direction = D3DXVECTOR3(0, -1, 0);

	cXMesh_Static* m = (cXMesh_Static*)pMap->pMesh;
	

	float d;
	BOOL isHit;
	D3DXIntersect(m->GetMesh(), &vR->origin, &vR->direction, &isHit, NULL, NULL, NULL, &d, NULL, NULL);

	if (isHit)
		result = buffer - d;

	return result;
}