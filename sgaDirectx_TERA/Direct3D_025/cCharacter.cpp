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
	SAFE_DELETE(m_pBodyAni);
	SAFE_DELETE(m_pFaceAni);
	SAFE_DELETE(m_pHairAni);
	SAFE_DELETE(m_pTailAni);
	SAFE_DELETE(m_pSkinnedTrans);
	SAFE_DELETE(m_pSkinnedTrans1);
	SAFE_DELETE(m_pSkinnedTrans2);
	SAFE_DELETE(m_pSkinnedTrans3);
	SAFE_DELETE(m_pSkinnedTrans4);
	SAFE_DELETE(m_pSkinnedTrans5);
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
	m_pRWeaponMesh = NULL;
	m_pLWeaponMesh = NULL;

	m_pSkinnedTrans = new cTransform();
	m_pSkinnedTrans1 = new cTransform();
	m_pSkinnedTrans2 = new cTransform();
	m_pSkinnedTrans3 = new cTransform();
	m_pSkinnedTrans4 = new cTransform();
	m_pSkinnedTrans5 = new cTransform();

	m_pBodyAni = new cSkinnedAnimation();
	m_pBodyAni->Init(pBodyMesh);
	m_pBodyAni->AddBoneTransform("Bip01-Neck", m_pSkinnedTrans1);
	m_pBodyAni->AddBoneTransform("Bip01-Head", m_pSkinnedTrans2);
	m_pBodyAni->AddBoneTransform("Bip01-Spine", m_pSkinnedTrans3);
	m_pBodyAni->AddBoneTransform("R_Sword", m_pSkinnedTrans4);
	m_pBodyAni->AddBoneTransform("L_Sword", m_pSkinnedTrans5);

	m_pFaceAni = new cSkinnedAnimation();
	m_pFaceAni->Init(pFaceMesh);

	m_pHairAni = new cSkinnedAnimation();
	m_pHairAni->Init(pHairMesh);

	m_pTailAni = new cSkinnedAnimation();
	m_pTailAni->Init(pTailMesh);


	if (PathRWeapon.length() > 0)
		m_pRWeaponMesh = RESOURCE_STATICXMESH->GetResource(PathRWeapon, mat);
	
	if (PathLWeapon.length() > 0)
		m_pLWeaponMesh = RESOURCE_STATICXMESH->GetResource(PathLWeapon, mat);
}



void cCharacter::Update(D3DXVECTOR3 worldPos, float timDelta)
{
	m_pBodyAni->Update(timDelta);
	m_pFaceAni->Update(timDelta);
	m_pHairAni->Update(timDelta);
	m_pTailAni->Update(timDelta);

	if (KEY_MGR->IsOnceDown('I'))
	{
		m_pBodyAni->Play("Wait", 0.3f);
		m_pFaceAni->Play("Wait", 0.3f);
		m_pHairAni->Play("Wait", 0.3f);
		m_pTailAni->Play("Wait", 0.3f);
	}
	if (KEY_MGR->IsOnceDown('O'))
	{
		m_pBodyAni->Play("Dash", 0.3f);
		m_pFaceAni->Play("Dash", 0.3f);
		m_pHairAni->Play("Dash", 0.3f);
		m_pTailAni->Play("Dash", 0.3f);
	}
	if (KEY_MGR->IsOnceDown('P'))
	{
		m_pBodyAni->PlayOneShot("Combo1", 0.3f);
		m_pFaceAni->PlayOneShot("Combo1", 0.3f);
		m_pHairAni->PlayOneShot("Combo1", 0.3f);
		m_pTailAni->PlayOneShot("Combo1", 0.3f);
	}
}

void cCharacter::Render()
{
	m_pBodyAni->Render(m_pSkinnedTrans);
	m_pFaceAni->Render(m_pSkinnedTrans1);
	m_pHairAni->Render(m_pSkinnedTrans2);
	m_pTailAni->Render(m_pSkinnedTrans3);

	m_pRWeaponMesh->Render(m_pSkinnedTrans4);
	m_pLWeaponMesh->Render(m_pSkinnedTrans5);
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