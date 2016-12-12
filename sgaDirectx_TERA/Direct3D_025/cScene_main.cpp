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
	//pMap = new cMeshMap(); //20161206 승현주석
	//pMap->Setup("./Tera/Map/EntireMap/moveMap/moveMap.X");

	pEntireMap = new cMap();
	pEntireMap->Setup();
	this->SetEnvironment("../Resources/skymap.dds");
	//플레이어
	pPlayer = new cCharacter();
	pPlayer->Setup("./Tera/Character/Elin_Body_WDC.X"
		, "./Tera/Character/Elin_Face_WDC.X"
		, "./Tera/Character/Elin_Hair_WDC.X"
		, "./Tera/Character/Elin_Tail_WDC.X"
		, "./Tera/Character/Weapon_R.X"
		, "./Tera/Character/Weapon_R.X");

	//PlayerUI //20161207 승현추가
	pPlayerUI = new cPlayerUI();
	pPlayerUI->Setup();

	for (int i = 0; i < pPlayer->GetBaseObject().size(); i++)
	{
		renderObjects.push_back(pPlayer->GetBaseObject()[i]);
	}

	//몬스터
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

	//보스몬스터UI 테스트 //20161207 승현추가
	//pProgressBar_Boss = new cProgressBar_Boss();
	//pProgressBar_Boss->Setup();

	//렌더 오브젝트 푸쉬
	//this->renderObjects.push_back(pMapObject);

	//라이트 위치
	this->pSceneBaseDirectionLight->pTransform->SetWorldPosition(0, 0, 0);
	this->pSceneBaseDirectionLight->pTransform->SetRotateWorld(90.0f * ONE_RAD, 0, 0);

	//TrailRenderSet
	cTrailRender* t1 = new cTrailRender();
	t1->Init(
		0.1f,					//꼬리 라이브 타임 ( 이게 크면 환영큐 사이즈가 커지고 꼬리가 오랬동안 남아있다 )
		0.5f,					//폭
		RESOURCE_TEXTURE->GetResource("./Resources/Testures/Tail.png"),	//메인 Texture
		D3DXCOLOR(0, 0.5, 1, 0.7),												//메인 Texture 로 그릴때 컬러
		RESOURCE_TEXTURE->GetResource("./Resources/Testures/Tail.png")	//외곡 그릴때 외곡 노말
		);

	cTrailRender* t2 = new cTrailRender();
	t2->Init(
		0.1f,					//꼬리 라이브 타임 ( 이게 크면 환영큐 사이즈가 커지고 꼬리가 오랬동안 남아있다 )
		0.5f,					//폭
		RESOURCE_TEXTURE->GetResource("./Resources/Testures/Tail.png"),	//메인 Texture
		D3DXCOLOR(0, 0.5, 1, 0.7),												//메인 Texture 로 그릴때 컬러
		RESOURCE_TEXTURE->GetResource("./Resources/Testures/Tail.png")	//외곡 그릴때 외곡 노말
		);

	//왼쪽 오른쪽 두개
	pVecTrailRender.push_back(t1);
	pVecTrailRender.push_back(t2);


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
	//오브젝트 해재
	for (int i = 0; i < this->renderObjects.size(); i++)
		SAFE_DELETE(this->renderObjects[i]);
	this->renderObjects.clear();
	this->cullObjects.clear();
	SAFE_DELETE(pPlayer);
	//SAFE_DELETE_ARR(pEnemy);
	delete[] pEnemy;
	//Trail 해재
	for each(auto t in pVecTrailRender)
	{
		t->Release();
		SAFE_DELETE(t);
	}
}

void cScene_main::Scene_Update(float timDelta)
{

	//if (KEY_MGR->IsOnceDown(VK_RETURN)){
	//	SCENE_MGR->ChangeSceneWithLoading("Test01", "로딩씬", 1, 1);
	//}
	
	//this->pSceneBaseDirectionLight->pTransform->DefaultControl2( timDelta );
	//this->pMainCamera->DefaultControl3(timDelta, pPlayer->GetBaseObject()[0]->pTransform->GetWorldPosition()); //
	//this->pMainCamera->DefaultControl4(timDelta, pPlayer->GetBaseObject()[0]->pTransform); //
	//this->pMainCamera->DefaultControl(timDelta); //★

	this->pMainCamera->UpdateFrustum();
	this->cullObjects.clear();
	for (int i = 0; i < this->renderObjects.size(); i++){

		//this->renderObjects[i]->Update(timDelta);

		//프러스텀 안에 있니?
		if (this->pMainCamera->Frustum.IsInFrustum(this->renderObjects[i]))
		{
			this->cullObjects.push_back(this->renderObjects[i]);
		}
	}
	for (int i = 0; i < this->cullObjects.size(); i++)
	{
		cullObjects[i]->Update(timDelta);
	}

	//20161206승현 getMap으로 바꾸기
	pPlayer->Update(D3DXVECTOR3(0.0f, 0.0f, 0.0f), timDelta, pEntireMap->GetMap());

	for (int i = 0; i < 36; i++)
	{
		pEnemy[i]->Update(timDelta, pEntireMap->GetMap(), &pPlayer->GetWorldPosition());
	}
	
	//업데이트
	//스킬이펙트
	pPlayerSkillEff->Update(timDelta);

	//검선이펙트
	pVecTrailRender[0]->Update(timDelta);
	pVecTrailRender[1]->Update(timDelta);
	

	if (pPlayer->GetIsAttack())
	{
		for (int i = 0; i < 36; i++)
		{
			if (pEnemy[i]->GetState() != MonState::Death && pEnemy[i]->GetState() != MonState::DeathWait)
			{
				if (PHYSICS_MGR->IsOverlap(pPlayer->GetBaseObject()[4], pEnemy[i]->GetBaseObject()[0]))
				{
					pEnemy[i]->SetState(MonState::Stun);
					//pEnemy[i]->SetHP(pEnemy[i]->GetHP() - 1);
					//0.0f, 0.75f, -0.025f
					D3DXVECTOR3 vCenter;
					float		ftemp;

					pPlayer->GetBaseObject()[4]->BoundBox.GetWorldCenterRadius(pPlayer->GetBaseObject()[4]->pTransform, &vCenter, &ftemp);
					pPlayerSkillEff->PlayEffect(EFF_ATTACK_01, vCenter);
				}

				if (PHYSICS_MGR->IsOverlap(pPlayer->GetBaseObject()[5], pEnemy[i]->GetBaseObject()[0]))
				{
					pEnemy[i]->SetState(MonState::Stun);
					//pEnemy[i]->SetHP(pEnemy[i]->GetHP() - 1);
					//0.0f, 0.75f, -0.025f
					D3DXVECTOR3 vCenter;
					float		ftemp;

					pPlayer->GetBaseObject()[5]->BoundBox.GetWorldCenterRadius(pPlayer->GetBaseObject()[5]->pTransform, &vCenter, &ftemp);
					pPlayerSkillEff->PlayEffect(EFF_ATTACK_01, vCenter);
				}
			}
		}



		D3DXVECTOR3 weaponPos;
		float		fTemp;

		pPlayer->GetBaseObject()[4]->BoundBox.GetWorldCenterRadius(pPlayer->GetBaseObject()[4]->pTransform, &weaponPos, &fTemp);
		pVecTrailRender[0]->Transform.SetWorldPosition(weaponPos);

		pPlayer->GetBaseObject()[5]->BoundBox.GetWorldCenterRadius(pPlayer->GetBaseObject()[5]->pTransform, &weaponPos, &fTemp);
		pVecTrailRender[1]->Transform.SetWorldPosition(weaponPos);
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
	
	this->pMainCamera->SetWorldPosition(D3DXVECTOR3(pPlayer->m_pRootTrans->GetWorldPosition().x + 5, pPlayer->m_pRootTrans->GetWorldPosition().y + 5, pPlayer->m_pRootTrans->GetWorldPosition().z + 1));
	this->pMainCamera->DefaultControl4(timDelta, pPlayer->m_pRootTrans); //★

	//쉐도우맵 준비
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
	//if (pMap) //20161206 승현주석
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

	//PlayerUI //20161207 승현추가
	if (pPlayerUI)
		pPlayerUI->Render();

	//보스몬스터유아이 //20161207 승현추가
	//if (pProgressBar_Boss)
	//	pProgressBar_Boss->Render();

	//컬링된 오브젝트만
	this->cullObjects.clear();
	for (int i = 0; i < this->renderObjects.size(); i++){
		//프러스텀 안에 있니?
		if (this->pMainCamera->Frustum.IsInFrustum(this->renderObjects[i]))
			this->cullObjects.push_back(this->renderObjects[i]);
	}

	for (int i = 0; i < this->cullObjects.size(); i++)
	{
		cullObjects[i]->Render();
	}

	//프러텀을 그려보장
	this->pDirectionLightCamera->Frustum.RenderGizmo();
	this->pSceneBaseDirectionLight->pTransform->RenderGimozo();

	//-----------------------------
	//Effect Rendering
	//-----------------------------

	if (pPlayerSkillEff)
		pPlayerSkillEff->Render();


	//랜더 ( 왠만하면 알파블랜딩이니깐 나중에 그리자... )
	for each (auto t in pVecTrailRender)
	{
		t->Render();
	}
	//this->pTrailRender->Render();
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