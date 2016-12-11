#include "stdafx.h"
#include "cScene_main.h"
#include "cLight_Point.h"
#include "cLight_Direction.h"
#include "cXMesh_Static.h"
#include "cBaseObject.h"
#include "cTransform.h"
#include "cCamera.h"
#include "cTrailRender.h"
#include "cCharacter.h"
#include "cEnemy.h"
#include "cMeshMap.h"
#include "cTerrain.h"
#include "cMap.h"
#include "cPlayerUI.h"
#include "cProgressBar_Boss.h"
#include "cPlayerSkillEffect.h"


cScene_main::cScene_main()
{
}
cScene_main::~cScene_main()
{
}


HRESULT cScene_main::Scene_Init()
{
	
	//Map 
	//pMap = new cMeshMap(); //20161206 �����ּ�
	//pMap->Setup("./Tera/Map/EntireMap/moveMap/moveMap.X");

	pEntireMap = new cMap();
	pEntireMap->Setup();
	this->SetEnvironment("../Resources/skymap.dds");
	//�÷��̾�
	pPlayer = new cCharacter();
	pPlayer->Setup("./Tera/Character/Elin_Body_WDC.X"
		, "./Tera/Character/Elin_Face_WDC.X"
		, "./Tera/Character/Elin_Hair_WDC.X"
		, "./Tera/Character/Elin_Tail_WDC.X"
		, "./Tera/Character/Weapon_R.X"
		, "./Tera/Character/Weapon_R.X");

	//PlayerUI //20161207 �����߰�
	pPlayerUI = new cPlayerUI();
	pPlayerUI->Setup();

	for (int i = 0; i < pPlayer->GetBaseObject().size(); i++)
	{
		renderObjects.push_back(pPlayer->GetBaseObject()[i]);
	}

	//����
	for (int x = 0; x < 6; x++)
	{
		for (int z = 0; z < 6; z++)
		{
			pEnemy[(x * 6) + z] = new cEnemy();
			pEnemy[(x * 6) + z]->Setup("./Tera/Monster/Kalan.X", &D3DXVECTOR3(30.0f + (x * 1), 0.0f, 33.0f + (z * 1)));
		}
	}

	for (int i = 0; i < 36; i++)
	{
		renderObjects.push_back(pEnemy[i]->GetBaseObject()[0]);
	}

	//��������UI �׽�Ʈ //20161207 �����߰�
	//pProgressBar_Boss = new cProgressBar_Boss();
	//pProgressBar_Boss->Setup();

	//���� ������Ʈ Ǫ��
	//this->renderObjects.push_back(pMapObject);

	//����Ʈ ��ġ
	this->pSceneBaseDirectionLight->pTransform->SetWorldPosition(0, 0, 0);
	this->pSceneBaseDirectionLight->pTransform->SetRotateWorld(90.0f * ONE_RAD, 0, 0);

	//TrailRenderSet
	this->pTrailRender = new cTrailRender();
	this->pTrailRender->Init(
		1.0f,					//���� ���̺� Ÿ�� ( �̰� ũ�� ȯ��ť ����� Ŀ���� ������ �������� �����ִ� )
		1.0f,					//��
		RESOURCE_TEXTURE->GetResource("./Resources/Testures/TrailTest.png"),	//���� Texture
		D3DXCOLOR(0, 0, 0, 1),												//���� Texture �� �׸��� �÷�
		RESOURCE_TEXTURE->GetResource("./Resources/Testures/TrailTest.png")	//�ܰ� �׸��� �ܰ� �븻
		);



	pPlayerSkillEff = new cPlayerSkillEffect;
	pPlayerSkillEff->Setup();

	cTransform* tempTrans = pPlayer->m_pRootTrans;
	//tempTrans->SetRotateWorld(0.0f, 90.0f, 0.0f);

	//this->pMainCamera->AttachTo(tempTrans);
	this->pMainCamera->MovePositionWorld(D3DXVECTOR3(pPlayer->GetBaseObject()[0]->pTransform->GetWorldPosition().x, pPlayer->GetBaseObject()[0]->pTransform->GetWorldPosition().y - 10, pPlayer->GetBaseObject()[0]->pTransform->GetWorldPosition().z));

	return S_OK;
}

void cScene_main::Scene_Release()
{
	//������Ʈ ����
	for (int i = 0; i < this->renderObjects.size(); i++)
		SAFE_DELETE(this->renderObjects[i]);
	this->renderObjects.clear();
	this->cullObjects.clear();
	SAFE_DELETE(pPlayer);
	//SAFE_DELETE_ARR(pEnemy);
	delete[] pEnemy;
	//Trail ����
	this->pTrailRender->Release();
	SAFE_DELETE(this->pTrailRender);
}

void cScene_main::Scene_Update(float timDelta)
{

	if (KEY_MGR->IsOnceDown(VK_RETURN)){
		SCENE_MGR->ChangeSceneWithLoading("Test01", "�ε���", 1, 1);
	}
	
	//this->pSceneBaseDirectionLight->pTransform->DefaultControl2( timDelta );
	//this->pMainCamera->DefaultControl3(timDelta, pPlayer->GetBaseObject()[0]->pTransform->GetWorldPosition()); //
	//this->pMainCamera->DefaultControl4(timDelta, pPlayer->GetBaseObject()[0]->pTransform); //
	//this->pMainCamera->DefaultControl(timDelta); //��

	this->pMainCamera->UpdateFrustum();
	this->cullObjects.clear();
	for (int i = 0; i < this->renderObjects.size(); i++){

		//this->renderObjects[i]->Update(timDelta);

		//�������� �ȿ� �ִ�?
		if (this->pMainCamera->Frustum.IsInFrustum(this->renderObjects[i]))
		{
			this->cullObjects.push_back(this->renderObjects[i]);
		}
	}
	for (int i = 0; i < this->cullObjects.size(); i++)
	{
		cullObjects[i]->Update(timDelta);
	}

	//20161206���� getMap���� �ٲٱ�
	pPlayer->Update(D3DXVECTOR3(0.0f, 0.0f, 0.0f), timDelta, pEntireMap->GetMap());

	for (int i = 0; i < 36; i++)
	{
		pEnemy[i]->Update(timDelta, pEntireMap->GetMap(), &pPlayer->GetWorldPosition());
	}
	

	//������Ʈ
	this->pTrailRender->Update(timDelta);
	this->pTrailRender->Transform.SetWorldPosition(pPlayer->GetWorldPosition());
	//this->pTrailRender->Transform.DefaultControl2(timDelta);

	pPlayerSkillEff->Update(timDelta);

	if (pPlayer->GetIsAttack())
	{
		for (int i = 0; i < 36; i++)
		{
			if (pEnemy[i]->GetState() != MonState::Death && pEnemy[i]->GetState() != MonState::DeathWait)
			{
				if (PHYSICS_MGR->IsOverlap(pPlayer->GetBaseObject()[4], pEnemy[i]->GetBaseObject()[0]))
				{
					pEnemy[i]->SetState(MonState::Stun);
					pEnemy[i]->SetHP(pEnemy[i]->GetHP() - 1);
					//0.0f, 0.75f, -0.025f
					D3DXVECTOR3 vCenter;
					float		ftemp;

					pPlayer->GetBaseObject()[4]->BoundBox.GetWorldCenterRadius(pPlayer->GetBaseObject()[4]->pTransform, &vCenter, &ftemp);

					pPlayerSkillEff->PlayEffect(EFF_ATTACK_01, vCenter);
				}
			}
		}
	}

	pEntireMap->m_pMap->pCharPosition = pPlayer->GetWorldPosition();

	//for (int i = 0; i < 36; i++)
	//{
	//	if (pEnemy[i]->GetState() != MonState::Death || pEnemy[i]->GetState() != MonState::DeathWait)
	//	{
	//		for (int j = 0; j < 36; j++)
	//		{
	//			if (i == j) continue;
	//				PHYSICS_MGR->IsBlocking(pEnemy[i]->GetBaseObject()[0], pEnemy[j]->GetBaseObject()[0], 0.5f);
	//		}
	//	}
	//}
	
	this->pMainCamera->DefaultControl4(timDelta, pPlayer->GetBaseObject()[0]->pTransform); //��
	//this->pMainCamera->SetWorldPosition(pPlayer->GetBaseObject()[0]->pTransform->GetWorldPosition());
	//this->pMainCamera->SetWorldPosition(D3DXVECTOR3(pPlayer->GetBaseObject()[0]->pTransform->GetWorldPosition().x, pPlayer->GetBaseObject()[0]->pTransform->GetWorldPosition().y + 10, pPlayer->GetBaseObject()[0]->pTransform->GetWorldPosition().z - 10));
	this->pMainCamera->SetWorldPosition(D3DXVECTOR3(pPlayer->m_pRootTrans->GetWorldPosition().x + 5, pPlayer->m_pRootTrans->GetWorldPosition().y + 5, pPlayer->m_pRootTrans->GetWorldPosition().z + 1));
	//������� �غ�
	this->ReadyShadowMap(&this->renderObjects, NULL);
}

void cScene_main::Scene_Render1()
{
	cXMesh_Static::SetCamera(this->pMainCamera);
	//cXMesh_Static::SetTechniqueName("ReciveShadow");
	cXMesh_Static::SetBaseLight(this->pSceneBaseDirectionLight);

	cXMesh_Skinned::SetCamera(this->pMainCamera);
	//cXMesh_Skinned::SetTechniqueName("ReciveShadow");
	cXMesh_Skinned::SetBaseLight(this->pSceneBaseDirectionLight);

	cXMesh_Skinned::SetLighting(&this->lights);

	//Map
	//if (pMap) //20161206 �����ּ�
	//	pMap->Render();

	if (pEntireMap)
		pEntireMap->Render();
	
	//Player
	if (pPlayer)
		pPlayer->Render(this->pSceneBaseDirectionLight);

	for (int i = 0; i < 36; i++)
	{
		if (pEnemy[i])
			pEnemy[i]->Render();
	}
	

	

	//PlayerUI //20161207 �����߰�
	if (pPlayerUI)
		pPlayerUI->Render();

	//�������������� //20161207 �����߰�
	//if (pProgressBar_Boss)
	//	pProgressBar_Boss->Render();

	//�ø��� ������Ʈ��
	this->cullObjects.clear();
	for (int i = 0; i < this->renderObjects.size(); i++){
		//�������� �ȿ� �ִ�?
		if (this->pMainCamera->Frustum.IsInFrustum(this->renderObjects[i]))
			this->cullObjects.push_back(this->renderObjects[i]);
	}

	for (int i = 0; i < this->cullObjects.size(); i++)
	{
		cullObjects[i]->Render();
	}

	//�������� �׷�����
	this->pDirectionLightCamera->Frustum.RenderGizmo();
	this->pSceneBaseDirectionLight->pTransform->RenderGimozo();

	if (pPlayerSkillEff)
		pPlayerSkillEff->Render();


	//���� ( �ظ��ϸ� ���ĺ����̴ϱ� ���߿� �׸���... )
	this->pTrailRender->Render();
}

void cScene_main::Scene_RenderSprite()
{
	//������ ���� �׷�����....
	RECT rcSour = { 0, 0, 4096, 4096 };
	RECT rcDest = { 0, 0, 300, 300 };


	SPRITE_MGR->DrawArea(this->pDirectionLightCamera->GetShadowTexture(),
		&rcSour,
		&rcDest);
}