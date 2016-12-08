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

	//����
	pEnemy = new cEnemy();
	pEnemy->Setup("./Tera/Monster/Kalan.X", &D3DXVECTOR3(0.0f, 0.0f, 5.0f));

	//��������UI �׽�Ʈ //20161207 �����߰�
	//pProgressBar_Boss = new cProgressBar_Boss();
	//pProgressBar_Boss->Setup();

	//���� ������Ʈ Ǫ��
	//this->renderObjects.push_back(pMapObject);

	//����Ʈ ��ġ
	this->pSceneBaseDirectionLight->pTransform->SetWorldPosition(0, 700, 0); //300
	this->pSceneBaseDirectionLight->pTransform->SetRotateWorld(90.0f * ONE_RAD, 0, 0);

	//TrailRenderSet
	this->pTrailRender = new cTrailRender();
	this->pTrailRender->Init(
		1.0f,					//���� ���̺� Ÿ�� ( �̰� ũ�� ȯ��ť ����� Ŀ���� ������ �������� �����ִ� )
		1.0f,					//��
		RESOURCE_TEXTURE->GetResource("./Resources/Testures/TrailTest.png"),	//���� Texture
		D3DXCOLOR(1, 0, 0, 1),												//���� Texture �� �׸��� �÷�
		RESOURCE_TEXTURE->GetResource("./Resources/Testures/TrailTest.png")	//�ܰ� �׸��� �ܰ� �븻
		);



	pPlayerSkillEff = new cPlayerSkillEffect;
	pPlayerSkillEff->Setup();

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
	SAFE_DELETE(pEnemy);

	//Trail ����
	this->pTrailRender->Release();
	SAFE_DELETE(this->pTrailRender);
}

void cScene_main::Scene_Update(float timDelta)
{
	if (KEY_MGR->IsOnceDown(VK_RETURN)){
		SCENE_MGR->ChangeSceneWithLoading("Test01", "�ε���", 1, 1);
	}

	this->pMainCamera->UpdateFrustum();
	this->cullObjects.clear();
	for (int i = 0; i < this->renderObjects.size(); i++){

		this->renderObjects[i]->Update(timDelta);

		//�������� �ȿ� �ִ�?
		if (this->pMainCamera->Frustum.IsInFrustum(this->renderObjects[i]))
		{
			this->cullObjects.push_back(this->renderObjects[i]);
		}
	}

	//20161206���� getMap���� �ٲٱ�
	pPlayer->Update(D3DXVECTOR3(0.0f, 0.0f, 0.0f), timDelta, pEntireMap->GetMap());

	pEnemy->Update(timDelta, pEntireMap->GetMap(), &pPlayer->GetWorldPosition());

	//������Ʈ
	//this->pTrailRender->Update(timDelta);
	//this->pTrailRender->Transform.DefaultControl2(timDelta);

	pPlayerSkillEff->Update(timDelta);

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

	//cXMesh_Skinned::SetLighting(&this->lights);

	//Map
	//if (pMap) //20161206 �����ּ�
	//	pMap->Render();
	if (pEntireMap)
		pEntireMap->Render();
	
	//Player
	if (pPlayer)
		pPlayer->Render();

	if (pEnemy)
		pEnemy->Render();

	if (pPlayerSkillEff)
		pPlayerSkillEff->Render();

	//PlayerUI //20161207 �����߰�
	//if (pPlayerUI)
	//	pPlayerUI->Render();

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

	//�������� �׷�����
	this->pDirectionLightCamera->Frustum.RenderGizmo();
	this->pSceneBaseDirectionLight->pTransform->RenderGimozo();


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