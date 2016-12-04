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
	//원래 있던 매쉬에서 다음과 같은 행렬로 보정시켜 
	//모든 정보를 틀어버린다.
	D3DXMATRIXA16 matCorrection;
	D3DXMatrixIdentity(&matCorrection);

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 0, -10, 0);
	D3DXMatrixRotationY(&matT, 180.0f * ONE_RAD);

	matCorrection = matT;


	//원본 메쉬 로딩
	cXMesh_Static* mesh =
		RESOURCE_STATICXMESH->GetResource(
		"./Tera/Map/moveMap/moveMap.X", &matCorrection);

	//플레이어
	pPlayer = new cCharacter();
	pPlayer->Setup("./Tera/Character/Elin_Body_WDC.X"
		, "./Tera/Character/Elin_Face_WDC.X"
		, "./Tera/Character/Elin_Hair_WDC.X"
		, "./Tera/Character/Elin_Tail_WDC.X"
		, "./Tera/Character/Weapon_R.object"
		, "./Tera/Character/Weapon_L.object"
		, &matCorrection);


	cBaseObject* pNewObject2 = new cBaseObject();
	pNewObject2->SetMesh(mesh);
	pNewObject2->SetActive(true);
	pNewObject2->pTransform->SetWorldPosition(0, 0.0f, 0.0f);
	pNewObject2->IgnoreCreateShadow = true;		//그림자 안그린다.
	pNewObject2->ApplyShadow = true;

	this->renderObjects.push_back(pNewObject2);

	//라이트 위치
	this->pSceneBaseDirectionLight->pTransform->SetWorldPosition(0, 20, 0);
	this->pSceneBaseDirectionLight->pTransform->SetRotateWorld(90.0f * ONE_RAD, 0, 0);



	//TrailRenderSet
	this->pTrailRender = new cTrailRender();
	this->pTrailRender->Init(
		1.0f,					//꼬리 라이브 타임 ( 이게 크면 환영큐 사이즈가 커지고 꼬리가 오랬동안 남아있다 )
		1.0f,					//폭
		RESOURCE_TEXTURE->GetResource("./Resources/Testures/TrailTest.png"),	//메인 Texture
		D3DXCOLOR(1, 0, 0, 1),												//메인 Texture 로 그릴때 컬러
		RESOURCE_TEXTURE->GetResource("./Resources/Testures/TrailTest.png")	//외곡 그릴때 외곡 노말
		);

	return S_OK;
}

void cScene_main::Scene_Release()
{
	//오브젝트 해재
	for (int i = 0; i < this->renderObjects.size(); i++)
		SAFE_DELETE(this->renderObjects[i]);
	this->renderObjects.clear();
	this->cullObjects.clear();

	//Trail 해재
	this->pTrailRender->Release();
	SAFE_DELETE(this->pTrailRender);
}

void cScene_main::Scene_Update(float timDelta)
{
	if (KEY_MGR->IsOnceDown(VK_RETURN)){
		SCENE_MGR->ChangeSceneWithLoading("Test01", "로딩씬", 1, 1);
	}

	this->pMainCamera->UpdateFrustum();
	this->cullObjects.clear();
	for (int i = 0; i < this->renderObjects.size(); i++){

		this->renderObjects[i]->Update(timDelta);

		//프러스텀 안에 있니?
		if (this->pMainCamera->Frustum.IsInFrustum(this->renderObjects[i]))
		{
			this->cullObjects.push_back(this->renderObjects[i]);
		}
	}

	//업데이트
	this->pTrailRender->Update(timDelta);
	this->pTrailRender->Transform.DefaultControl2(timDelta);


	//쉐도우맵 준비
	this->ReadyShadowMap(&this->renderObjects);
}

void cScene_main::Scene_Render1()
{
	cXMesh_Static::SetCamera(this->pMainCamera);
	cXMesh_Static::SetBaseLight(this->pSceneBaseDirectionLight);

	cXMesh_Skinned::SetCamera(this->pMainCamera);
	cXMesh_Skinned::SetBaseLight(this->pSceneBaseDirectionLight);

	cXMesh_Skinned::SetLighting(&this->lights);

	//컬링된 오브젝트만
	this->cullObjects.clear();
	for (int i = 0; i < this->renderObjects.size(); i++){
		//프러스텀 안에 있니?
		if (this->pMainCamera->Frustum.IsInFrustum(this->renderObjects[i]))
			this->cullObjects.push_back(this->renderObjects[i]);
	}

	if (pPlayer)
		pPlayer->Render();

	//프러텀을 그려보장
	this->pDirectionLightCamera->Frustum.RenderGizmo();
	this->pSceneBaseDirectionLight->pTransform->RenderGimozo();


	//랜더 ( 왠만하면 알파블랜딩이니깐 나중에 그리자... )
	this->pTrailRender->Render();
}

void cScene_main::Scene_RenderSprite()
{
	//쉐도우 맵을 그려보자....
	RECT rcSour = { 0, 0, 4096, 4096 };
	RECT rcDest = { 0, 0, 300, 300 };


	SPRITE_MGR->DrawArea(this->pDirectionLightCamera->GetShadowTexture(),
		&rcSour,
		&rcDest);
}