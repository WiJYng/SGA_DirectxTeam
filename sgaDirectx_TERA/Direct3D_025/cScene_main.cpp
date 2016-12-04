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


cScene_main::cScene_main()
{
}


cScene_main::~cScene_main()
{
}


HRESULT cScene_main::Scene_Init()
{
	//���� �ִ� �Ž����� ������ ���� ��ķ� �������� 
	//��� ������ Ʋ�������.
	D3DXMATRIXA16 matCorrection;
	D3DXMatrixIdentity(&matCorrection);

	//Map
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 0, -10, 0);
	D3DXMatrixRotationY(&matT, 180.0f * ONE_RAD);

	matCorrection = matT;

	cXMesh_Static* mesh =
		RESOURCE_STATICXMESH->GetResource(
		"./Tera/Map/moveMap/moveMap.X", &matCorrection);
	
	pMap = new cBaseObject();
	pMap->SetMesh(mesh);
	pMap->SetActive(true);
	pMap->IgnoreCreateShadow = true;		//�׸��� �ȱ׸���.
	pMap->ApplyShadow = true;

	//�÷��̾�
	pPlayer = new cCharacter();
	pPlayer->Setup("./Tera/Character/Elin_Body_WDC.X"
		, "./Tera/Character/Elin_Face_WDC.X"
		, "./Tera/Character/Elin_Hair_WDC.X"
		, "./Tera/Character/Elin_Tail_WDC.X"
		, "./Tera/Character/Weapon_R.X"
		, "");



	//���� ������Ʈ Ǫ��
	//this->renderObjects.push_back(pMapObject);

	//����Ʈ ��ġ
	this->pSceneBaseDirectionLight->pTransform->SetWorldPosition(0, 20, 0);
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

	return S_OK;
}

void cScene_main::Scene_Release()
{
	//������Ʈ ����
	for (int i = 0; i < this->renderObjects.size(); i++)
		SAFE_DELETE(this->renderObjects[i]);
	this->renderObjects.clear();
	this->cullObjects.clear();

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

	//������Ʈ
	this->pTrailRender->Update(timDelta);
	this->pTrailRender->Transform.DefaultControl2(timDelta);


	//������� �غ�
	this->ReadyShadowMap(&this->renderObjects);
}

void cScene_main::Scene_Render1()
{
	cXMesh_Static::SetCamera(this->pMainCamera);
	cXMesh_Static::SetBaseLight(this->pSceneBaseDirectionLight);

	cXMesh_Skinned::SetCamera(this->pMainCamera);
	cXMesh_Skinned::SetBaseLight(this->pSceneBaseDirectionLight);

	cXMesh_Skinned::SetLighting(&this->lights);

	//Map
	//if (pMap)
	//	pMap->Render();
	
	//Player
	if (pPlayer)
		pPlayer->Render();

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