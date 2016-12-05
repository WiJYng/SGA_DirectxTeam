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
#include "cMeshMap.h"


cScene_main::cScene_main()
{
}


cScene_main::~cScene_main()
{
}


HRESULT cScene_main::Scene_Init()
{
	
	//Map
	pMap = new cMeshMap();
	pMap->Setup("./Tera/Map/moveMap/moveMap.X");

	//플레이어
	pPlayer = new cCharacter();
	pPlayer->Setup("./Tera/Character/Elin_Body_WDC.X"
		, "./Tera/Character/Elin_Face_WDC.X"
		, "./Tera/Character/Elin_Hair_WDC.X"
		, "./Tera/Character/Elin_Tail_WDC.X"
		, "./Tera/Character/Weapon_R.X"
		, "./Tera/Character/Weapon_R.X");


	//렌더 오브젝트 푸쉬
	//this->renderObjects.push_back(pMapObject);

	//라이트 위치
	this->pSceneBaseDirectionLight->pTransform->SetWorldPosition(0, 300, 0);
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

	pPlayer->Update(D3DXVECTOR3(0.0f, 0.0f, 0.0f), timDelta);

	//업데이트
	//this->pTrailRender->Update(timDelta);
	//this->pTrailRender->Transform.DefaultControl2(timDelta);


	//쉐도우맵 준비
	this->ReadyShadowMap(&this->renderObjects);
}

void cScene_main::Scene_Render1()
{
	cXMesh_Static::SetCamera(this->pMainCamera);
	cXMesh_Static::SetBaseLight(this->pSceneBaseDirectionLight);

	cXMesh_Skinned::SetCamera(this->pMainCamera);
	cXMesh_Skinned::SetBaseLight(this->pSceneBaseDirectionLight);

	//cXMesh_Skinned::SetLighting(&this->lights);

	//Map
	if (pMap)
		pMap->Render();
	
	//Player
	if (pPlayer)
		pPlayer->Render();

	//컬링된 오브젝트만
	this->cullObjects.clear();
	for (int i = 0; i < this->renderObjects.size(); i++){
		//프러스텀 안에 있니?
		if (this->pMainCamera->Frustum.IsInFrustum(this->renderObjects[i]))
			this->cullObjects.push_back(this->renderObjects[i]);
	}

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