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

	pMap = new cBaseObject();
	pMap->SetMesh(mesh);
	pMap->SetActive(true);
	pMap->IgnoreCreateShadow = true;		//그림자 안그린다.
	pMap->ApplyShadow = true;
}

void cMeshMap::Render()
{
	if (pMap)
		pMap->Render();
}

float cMeshMap::GetHeight(float x, float z)
{

	return 0;
}