#include "stdafx.h"
#include "cCamera.h"
#include "cCharacter.h"
#include "cSkinnedAnimation.h"
#include "cTrailRender.h"
#include "cLight_Direction.h"
#include "cLight_Point.h"


cCharacter::cCharacter()
{
}


cCharacter::~cCharacter()
{
	
}

void cCharacter::Setup(string PathBody, string PathFace, string PathHair, string PathTail)
{
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);

	cXMesh_Skinned* pBodyMesh = RESOURCE_SKINNEDXMESH->GetResource(PathBody, &mat);
	
	rootObject = new cBaseObject();
	rootObject->SetMesh(pBodyMesh);
	rootObject->SetActive(true);

	this->renderObjects.push_back(rootObject);


	
	//m_pBody = new cBody(Directory, PathBody);
	//m_pFace = new cFace(Directory, PathFace);
	//m_pHair = new cHair(Directory, PathHair);
	//m_pTail = new cTail(Directory, PathTail);

	//m_pRWeapon = new cWeapon;
	//m_pRWeapon->Load("./Tera/Character/Weapon_R.object", &mat);
	//m_pLWeapon = new cWeapon;
	//m_pLWeapon->Load("./Tera/Character/Weapon_L.object", &mat);
}

void cCharacter::Update(D3DXVECTOR3 worldPos)
{
	
	

	//m_pBody->SetAnimationIndex(AniIndex);
	//m_pFace->SetAnimationIndex(AniIndex);
	//m_pHair->SetAnimationIndex(AniIndex);
	//m_pTail->SetAnimationIndex(AniIndex);
}

void cCharacter::Render()
{
	
	for (int i = 0; i < this->renderObjects.size(); i++)
		this->renderObjects[i]->Render();

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