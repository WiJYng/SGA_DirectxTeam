#include "stdafx.h"
#include "cCamera.h"
#include "cCharacter.h"
#include "cSkinnedAnimation.h"
#include "cTrailRender.h"
#include "cLight_Direction.h"
#include "cLight_Point.h"
#include "cMeshMap.h"


cCharacter::cCharacter()
	: rootObject(NULL)
	, m_bAttack(false)
	, m_tState(Wait)
{
}


cCharacter::~cCharacter()
{
	SAFE_DELETE(m_pBodyAni);
	SAFE_DELETE(m_pFaceAni);
	SAFE_DELETE(m_pHairAni);
	SAFE_DELETE(m_pTailAni);
	SAFE_DELETE(m_pRootTrans);
	SAFE_DELETE(m_pNeckTrans);
	SAFE_DELETE(m_pHairTrans);
	SAFE_DELETE(m_pTailTrans);
	SAFE_DELETE(m_pRWeaponTrans);
	SAFE_DELETE(m_pLWeaponTrans);
	SAFE_DELETE(rootObject);
}


void cCharacter::Setup(string PathBody, string PathFace, string PathHair, string PathTail, string PathRWeapon, string PathLWeapon)
{
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	//D3DXMatrixTranslation(&mat, 0.0f, 0.0f, 0.0f);

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

	m_pRootTrans = new cTransform();
	m_pNeckTrans = new cTransform();
	m_pHairTrans = new cTransform();
	m_pTailTrans = new cTransform();
	m_pRWeaponTrans = new cTransform();
	m_pLWeaponTrans = new cTransform();
	m_pBottomTrans = new cTransform();

	cBaseObject* pBodyObject = new cBaseObject();
	pBodyObject->pSkinned = new cSkinnedAnimation();
	pBodyObject->pSkinned->Init(pBodyMesh);
	pBodyObject->SetMesh(pBodyMesh);
	pBodyObject->SetActive(true);
	//pBodyObject->pTransform->SetWorldPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pBodyObject->pTransform->RotateSelf(0.0f, -110.0f * ONE_RAD, 0.0f); //-110
	pBodyObject->pTransform->SetWorldPosition(D3DXVECTOR3(92.0f, 0.0f, 65.0f));
	pBodyObject->BoundBox.Init(D3DXVECTOR3(0.25f, -0.4f, -0.25f), D3DXVECTOR3(-0.25f, 1.5f, 0.25f));
	//pBodyObject->IgnoreCreateShadow = false;
	//pBodyObject->ApplyShadow = true;
	//pBodyObject->BoundBox.

	pBodyObject->pSkinned->AddBoneTransform("Dummy_root", m_pRootTrans);
	pBodyObject->pSkinned->AddBoneTransform("Bip01-Neck", m_pNeckTrans);
	pBodyObject->pSkinned->AddBoneTransform("Bip01-Head", m_pHairTrans);
	pBodyObject->pSkinned->AddBoneTransform("Bip01-Spine", m_pTailTrans);
	pBodyObject->pSkinned->AddBoneTransform("R_Sword", m_pRWeaponTrans);
	pBodyObject->pSkinned->AddBoneTransform("L_Sword", m_pLWeaponTrans);
	pBodyObject->pSkinned->AddBoneTransform("FxBottom", m_pBottomTrans);

	cBaseObject* pFaceObject = new cBaseObject();
	pFaceObject->pSkinned = new cSkinnedAnimation();
	pFaceObject->pSkinned->Init(pFaceMesh);
	pFaceObject->SetMesh(pFaceMesh);
	pFaceObject->SetActive(true);
	pFaceObject->pTransform = m_pNeckTrans;

	cBaseObject* pHairObject = new cBaseObject();
	pHairObject->pSkinned = new cSkinnedAnimation();
	pHairObject->pSkinned->Init(pHairMesh);
	pHairObject->SetMesh(pHairMesh);
	pHairObject->SetActive(true);
	pHairObject->pTransform = m_pHairTrans;

	cBaseObject* pTailObject = new cBaseObject();
	pTailObject->pSkinned = new cSkinnedAnimation();
	pTailObject->pSkinned->Init(pTailMesh);
	pTailObject->SetMesh(pTailMesh);
	pTailObject->SetActive(true);
	pTailObject->pTransform = m_pTailTrans;


	if (PathRWeapon.length() > 0)
		m_pRWeaponMesh = RESOURCE_STATICXMESH->GetResource(PathRWeapon, mat);

	if (PathLWeapon.length() > 0)
		m_pLWeaponMesh = RESOURCE_STATICXMESH->GetResource(PathLWeapon, mat);

	cBaseObject* pRWeapon = new cBaseObject();
	pRWeapon->SetMesh(m_pRWeaponMesh);
	pRWeapon->SetActive(true);
	pRWeapon->pTransform = m_pRWeaponTrans;
	pRWeapon->BoundBox.Init(D3DXVECTOR3(-0.1, 0.6, -0.15), D3DXVECTOR3(0.1, 0.9, 0.1)); //0.0f, 0.75f, -0.025f

	cBaseObject* pLWeapon = new cBaseObject();
	pLWeapon->SetMesh(m_pLWeaponMesh);
	pLWeapon->SetActive(true);
	pLWeapon->pTransform = m_pLWeaponTrans;
	pLWeapon->BoundBox.Init(D3DXVECTOR3(-0.1, 0.6, -0.15), D3DXVECTOR3(0.1, 0.9, 0.1));

	renderObjects.push_back(pBodyObject);
	renderObjects.push_back(pFaceObject);
	renderObjects.push_back(pHairObject);
	renderObjects.push_back(pTailObject);
	renderObjects.push_back(pRWeapon);
	renderObjects.push_back(pLWeapon);

	for (int i = 0; i < renderObjects.size(); i++)
	{
		if (!renderObjects[i]->pSkinned) continue;
		renderObjects[i]->pSkinned->Play("Wait", 0.3f);
	}

	m_fHP = m_fMaxHP = 100;
}



void cCharacter::Update(D3DXVECTOR3 worldPos, float timDelta, cMeshMap* _Map)
{
	for (int i = 0; i < renderObjects.size(); i++)
	{
		if (!renderObjects[i]->pSkinned) continue;

		renderObjects[i]->pSkinned->Update(timDelta);
	}
	//renderObjects[0]->pSkinned->AddBoneTransform("Dummy_root", m_pRootTrans);
	//m_pRootTrans = renderObjects[0]->pTransform;


	if (!m_bAttack)
	{
		if (KEY_MGR->IsStayDown('A'))
		{
			renderObjects[0]->pTransform->LeftControl(timDelta);
		}
		if (KEY_MGR->IsStayDown('D'))
		{
			renderObjects[0]->pTransform->RightControl(timDelta);
		}
		if (KEY_MGR->IsStayDown('S'))
		{
			renderObjects[0]->pTransform->BackControl(timDelta);
		}
	}

	if (KEY_MGR->IsStayDown('W'))
	{
		renderObjects[0]->pTransform->GoControl(timDelta);
		if (!m_bAttack && m_tState != Dash)
		{
			m_tState = Dash;
			for (int i = 0; i < renderObjects.size(); i++)
			{
				if (!renderObjects[i]->pSkinned) continue;
				renderObjects[i]->pSkinned->Play("Dash", 0.3f);
				renderObjects[i]->pSkinned->SetPlaySpeed(0.75);
				//SOUND_MGR->play("RunS");
			}
		}
		if (renderObjects[0]->pSkinned->GetFactor() <= 0.03)
		{
			SOUND_MGR->play("RS", 0.1);
		}
		if (renderObjects[0]->pSkinned->GetFactor() > 0.50 && renderObjects[0]->pSkinned->GetFactor() <= 0.53)
		{
			SOUND_MGR->play("RS", 0.1);
		}
	}

	if (KEY_MGR->IsOnceDown('O'))
	{
		if (!m_bAttack)
		{
			m_bAttack = true;
			if (m_tState == Wait || m_tState == Dash)
			{
				m_tState = Combo1;
				for (int i = 0; i < renderObjects.size(); i++)
				{
					if (!renderObjects[i]->pSkinned) continue;
					renderObjects[i]->pSkinned->PlayOneShot("Combo1", 0.3f);
					renderObjects[i]->pSkinned->SetPlaySpeed(1.0f);
				}
				//CharPlaySound(rand() % 10);
				SOUND_MGR->play("ATT_S01", 1.0);
			}
		}
		else
		{
			if (renderObjects[0]->pSkinned->GetFactor() >= 0.55)
			{
				if (m_tState == Combo1 || m_tState == Rapid1)
				{
					m_tState = Combo2;
					for (int i = 0; i < renderObjects.size(); i++)
					{
						if (!renderObjects[i]->pSkinned) continue;
						renderObjects[i]->pSkinned->PlayOneShot("Combo2", 0.0f);
						renderObjects[i]->pSkinned->SetPlaySpeed(1.0f);
					}
					//CharPlaySound(rand() % 10);
					SOUND_MGR->play("ATT_S02", 1.0);
					renderObjects[0]->pTransform->SetWorldPosition(D3DXVECTOR3(m_pRootTrans->GetWorldPosition().x, 0.0f, m_pRootTrans->GetWorldPosition().z));
				}
				else if (m_tState == Combo2 || m_tState == Rapid2)
				{
					m_tState = Combo3;
					for (int i = 0; i < renderObjects.size(); i++)
					{
						if (!renderObjects[i]->pSkinned) continue;
						renderObjects[i]->pSkinned->PlayOneShot("Combo3", 0.0f);
						renderObjects[i]->pSkinned->SetPlaySpeed(1.0f);
					}
					//CharPlaySound(rand() % 5);
					SOUND_MGR->play("ATT_S03", 1.0);
					renderObjects[0]->pTransform->SetWorldPosition(D3DXVECTOR3(m_pRootTrans->GetWorldPosition().x, 0.0f, m_pRootTrans->GetWorldPosition().z));
				}
				else if (m_tState == Combo3 || m_tState == Rapid3)
				{
					m_tState = Combo4;
					for (int i = 0; i < renderObjects.size(); i++)
					{
						if (!renderObjects[i]->pSkinned) continue;
						renderObjects[i]->pSkinned->PlayOneShot("Combo4", 0.0f);
						renderObjects[i]->pSkinned->SetPlaySpeed(1.0f);
					}
					//CharPlaySound(rand() % 10);
					SOUND_MGR->play("ATT_S04", 1.0);
					renderObjects[0]->pTransform->SetWorldPosition(D3DXVECTOR3(m_pRootTrans->GetWorldPosition().x, 0.0f, m_pRootTrans->GetWorldPosition().z));
				}
			}
		}
	}

	if (KEY_MGR->IsOnceDown('P'))
	{
		if (!m_bAttack)
		{
			m_bAttack = true;
			if (m_tState == Wait || m_tState == Dash || m_tState == Combo1)
			{
				m_tState = Rapid1;
				for (int i = 0; i < renderObjects.size(); i++)
				{
					if (!renderObjects[i]->pSkinned) continue;
					renderObjects[i]->pSkinned->PlayOneShot("Rapid1", 0.3f);
					renderObjects[i]->pSkinned->SetPlaySpeed(1.0f);
				}
				//CharPlaySound(rand() % 10);
				SOUND_MGR->play("RAPID_01");
			}
		}
		else
		{
			if (renderObjects[0]->pSkinned->GetFactor() >= 0.55)
			{
				if (m_tState == Rapid1 || m_tState == Combo2)
				{
					m_tState = Rapid2;
					for (int i = 0; i < renderObjects.size(); i++)
					{
						if (!renderObjects[i]->pSkinned) continue;
						renderObjects[i]->pSkinned->PlayOneShot("Rapid2", 0.0f);
						renderObjects[i]->pSkinned->SetPlaySpeed(1.0f);
					}
					//CharPlaySound(rand() % 10);
					SOUND_MGR->play("RAPID_02");
					renderObjects[0]->pTransform->SetWorldPosition(D3DXVECTOR3(m_pRootTrans->GetWorldPosition().x, 0.0f, m_pRootTrans->GetWorldPosition().z));
				}
				else if (m_tState == Rapid2 || m_tState == Combo2)
				{
					m_tState = Rapid3;
					for (int i = 0; i < renderObjects.size(); i++)
					{
						if (!renderObjects[i]->pSkinned) continue;
						renderObjects[i]->pSkinned->PlayOneShot("Rapid3", 0.0f);
						renderObjects[i]->pSkinned->SetPlaySpeed(1.0f);
					}
					CharPlaySound((rand() % 6) + 5);
					renderObjects[0]->pTransform->SetWorldPosition(D3DXVECTOR3(m_pRootTrans->GetWorldPosition().x, 0.0f, m_pRootTrans->GetWorldPosition().z));
				}
			}
		}
	}

	if (m_tState == Rapid3)
	{
		if (renderObjects[0]->pSkinned->GetFactor() <= 0.01)
		{
			SOUND_MGR->play("RAPID_03", 0.4);
		}
		if (renderObjects[0]->pSkinned->GetFactor() > 0.30 && renderObjects[0]->pSkinned->GetFactor() <= 0.305)
		{
			SOUND_MGR->play("RAPID_04", 0.4);
		}
	}


	if (m_bAttack)
	{
		if ((m_tState == Combo1 || m_tState == Combo2 || m_tState == Combo3 || m_tState == Combo4
			|| m_tState == Rapid1 || m_tState == Rapid2 || m_tState == Rapid3) && renderObjects[0]->pSkinned->GetFactor() >= 0.75f)
		{
			//renderObjects[0]->pTransform->SetWorldPosition(m_pRootTrans->GetWorldPosition());

			m_tState = Wait;
			m_bAttack = false;
			for (int i = 0; i < renderObjects.size(); i++)
			{
				if (!renderObjects[i]->pSkinned) continue;
				renderObjects[i]->pSkinned->Play("Wait", 0.0f);
				renderObjects[i]->pSkinned->SetPlaySpeed(1.0f);
			}
			//renderObjects[0]->pTransform->PositionLerp(*m_pRootTrans, *renderObjects[0]->pTransform, 0.75f);
			renderObjects[0]->pTransform->SetWorldPosition(D3DXVECTOR3(m_pRootTrans->GetWorldPosition().x, 0.0f, m_pRootTrans->GetWorldPosition().z));
			//m_pRootTrans->SetWorldPosition(renderObjects[0]->pTransform->GetWorldPosition());
		}
	}
	else
	{
		if ((m_tState != Wait && !(GetKeyState('W') & 0x8000)))
		{
			m_tState = Wait;
			m_bAttack = false;
			for (int i = 0; i < renderObjects.size(); i++)
			{
				if (!renderObjects[i]->pSkinned) continue;
				renderObjects[i]->pSkinned->Play("Wait", 0.3f);
				renderObjects[i]->pSkinned->SetPlaySpeed(1.0f);
			}
		}
	}
	if (_Map)
	{
		float y = 0;
		if (!m_bAttack)
		{
			y = _Map->GetHeight(renderObjects[0]->pTransform->GetWorldPosition().x, renderObjects[0]->pTransform->GetWorldPosition().z);
		}
		else
		{
			y = _Map->GetHeight(m_pRootTrans->GetWorldPosition().x, m_pRootTrans->GetWorldPosition().z);
		}
		renderObjects[0]->pTransform->SetWorldPosition(renderObjects[0]->pTransform->GetWorldPosition().x, y, renderObjects[0]->pTransform->GetWorldPosition().z);
	}

}

void cCharacter::Render(cLight_Direction* pDirLight)
{
	//라이트 정보 셋팅
	//cXMesh_Skinned::SetBaseLight(pDirLight);
	//cXMesh_Skinned::SetTechniqueName("Toon");
	//cXMesh_Static::SetLighting(&this->lights);

	for (int i = 0; i < renderObjects.size(); i++)
	{
		renderObjects[i]->Render();
	}
	//renderObjects[0]->BoundBox.RenderGizmo(m_pRootTrans);
	//renderObjects[4]->BoundBox.RenderGizmo(m_pRWeaponTrans);
	//renderObjects[5]->BoundBox.RenderGizmo(m_pLWeaponTrans);
}

void cCharacter::SetWorldPosition(D3DXVECTOR3 pos)
{
	for (int i = 0; i < this->renderObjects.size(); i++)
		this->renderObjects[i]->pTransform->SetWorldPosition(pos);
}

D3DXVECTOR3 cCharacter::GetWorldPosition()
{
	//body
	D3DXVECTOR3 result = renderObjects[0]->pTransform->GetWorldPosition();
	return result;
}

void cCharacter::CharPlaySound(int n)
{
	float SoundV = 0.2;
	switch (n)
	{
	case 0:
		SOUND_MGR->play("ATT_01", SoundV);
		break;

	case 1:
		SOUND_MGR->play("ATT_02", SoundV);
		break;

	case 2:
		SOUND_MGR->play("ATT_03", SoundV);
		break;

	case 3:
		SOUND_MGR->play("ATT_04", SoundV);
		break;

	case 4:
		SOUND_MGR->play("ATT_05", SoundV);
		break;

	case 5:
		SOUND_MGR->play("ATT_06", SoundV);
		break;

	case 6:
		SOUND_MGR->play("ATT_07", SoundV);
		break;

	case 7:
		SOUND_MGR->play("ATT_08", SoundV);
		break;

	case 8:
		SOUND_MGR->play("ATT_09", SoundV);
		break;

	case 9:
		SOUND_MGR->play("ATT_10", SoundV);
		break;

	case 10:
		SOUND_MGR->play("ATT_11", SoundV);
		break;

	case 11:
		SOUND_MGR->play("ATT_12", SoundV);
		break;

	case 12:
		SOUND_MGR->play("ATT_13", SoundV);
		break;

	case 13:
		SOUND_MGR->play("ATT_14", SoundV);
		break;

	case 14:
		SOUND_MGR->play("ATT_15", SoundV);
		break;

	case 15:
		SOUND_MGR->play("ATT_16", SoundV);
		break;
	}
}
