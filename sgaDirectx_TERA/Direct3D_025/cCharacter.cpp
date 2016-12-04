#include "stdafx.h"
#include "cCamera.h"
#include "cCharacter.h"
#include "cSkinnedAnimation.h"
#include "cTrailRender.h"
#include "cLight_Direction.h"
#include "cLight_Point.h"


cCharacter::cCharacter()
	: rootObject(NULL)
{
}


cCharacter::~cCharacter()
{
	SAFE_DELETE(rootObject);
}


void cCharacter::Setup(string PathBody, string PathFace, string PathHair, string PathTail, string PathRWeapon, string PathLWeapon)
{
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);

	Setup(PathBody, PathFace, PathHair, PathTail, PathRWeapon, PathLWeapon, &mat);	
}

void cCharacter::Setup(string PathBody, string PathFace, string PathHair, string PathTail, string PathRWeapon, string PathLWeapon, D3DXMATRIXA16* mat)
{
	//기본 6개의 파츠로 이루어져있다
	this->renderObjects.reserve(6);

	cXMesh_Skinned* pBodyMesh = RESOURCE_SKINNEDXMESH->GetResource(PathBody, mat);
	cXMesh_Skinned* pFaceMesh = RESOURCE_SKINNEDXMESH->GetResource(PathFace, mat);
	cXMesh_Skinned* pHairMesh = RESOURCE_SKINNEDXMESH->GetResource(PathHair, mat);
	cXMesh_Skinned* pTailMesh = RESOURCE_SKINNEDXMESH->GetResource(PathTail, mat);
	cXMesh_Static* pRWeaponMesh = NULL;
	cXMesh_Static* pLWeaponMesh = NULL;
	
	if (PathRWeapon.length() > 0)
		pRWeaponMesh = RESOURCE_STATICXMESH->GetResource(PathRWeapon, mat);
	
	if (PathLWeapon.length() > 0)
		pLWeaponMesh = RESOURCE_STATICXMESH->GetResource(PathLWeapon, mat);
		
	//Body가 루트가 된다
	rootObject = new cBaseObject();
	rootObject->SetMesh(pBodyMesh);
	rootObject->SetActive(true);

	cBaseObject* face = new cBaseObject();
	face->SetMesh(pFaceMesh);
	face->SetActive(true);
	
	cBaseObject* hair = new cBaseObject();
	hair->SetMesh(pHairMesh);
	hair->SetActive(true);
	
	cBaseObject* tail = new cBaseObject();
	tail->SetMesh(pTailMesh);
	tail->SetActive(true);
	
	//무기
	cBaseObject* rWeapon = NULL; 
	cBaseObject* lWeapon = NULL;
	
	if (pRWeaponMesh)
	{
		rWeapon = new cBaseObject();
		rWeapon->SetMesh(pRWeaponMesh);
		rWeapon->SetActive(true);
	}
	
	if (pLWeaponMesh)
	{
		lWeapon = new cBaseObject();
		lWeapon->SetMesh(pLWeaponMesh);
		lWeapon->SetActive(true);
	}

	//Render할 객체 Push
	this->renderObjects.push_back(rootObject);
	this->renderObjects.push_back(face);
	this->renderObjects.push_back(hair);
	this->renderObjects.push_back(tail);
	this->renderObjects.push_back(rWeapon);
	this->renderObjects.push_back(lWeapon);	


	//calculateMeshPosition(mat);
}

void cCharacter::calculateMeshPosition(D3DXMATRIXA16* mat)
{
	//for (int i = 0; i<);


}


void cCharacter::Update(D3DXVECTOR3 worldPos)
{
	
}

void cCharacter::Render()
{
	for (int i = 0; i < this->renderObjects.size(); i++)
	{
		if (this->renderObjects[i])
			this->renderObjects[i]->Render();
	}
}

void cCharacter::SetWorldPosition(D3DXVECTOR3 pos)
{
	for (int i = 0; i < this->renderObjects.size(); i++)
		this->renderObjects[i]->pTransform->SetWorldPosition(pos);
}

D3DXVECTOR3 cCharacter::GetWorldPosition()
{
	//body
	D3DXVECTOR3 result = rootObject->pTransform->GetWorldPosition();
	return result;
}