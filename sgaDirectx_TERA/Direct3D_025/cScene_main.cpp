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
#include "cBoss.h"
#include "cMeshMap.h"
#include "cTerrain.h"
#include "cMap.h"
#include "cPlayerUI.h"
#include "cProgressBar_Boss.h"
#include "cPlayerSkillEffect.h"
#include "cTickFunc.h"


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
	this->SetEnvironment("Tera/Map/Sky.dds");

	pEntireMap = new cMap();
	pEntireMap->Setup();

	//젠 위치
	GenSetup();

	//플레이어
	pPlayer = new cCharacter();
	pPlayer->Setup("./Tera/Character/Elin_Body_WDCR.X"
		, "./Tera/Character/Elin_Face_WDCR.X"
		, "./Tera/Character/Elin_Hair_WDCR.X"
		, "./Tera/Character/Elin_Tail_WDCR.X"
		, "./Tera/Character/Weapon_R.X"
		, "./Tera/Character/Weapon_R.X");

	//PlayerUI //20161207 승현추가
	pPlayerUI = new cPlayerUI();
	pPlayerUI->Setup();

	//몬스터
	MonsterSetup();

	//보스
	pBoss = new cBoss();
	pBoss->Setup("./Tera/Monster/Drowned.X", &D3DXVECTOR3(-128.f, -15.0f, 80.0f));

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

	this->pMainCamera->AttachTo(tempTrans);
	this->pMainCamera->SetWorldPosition(pPlayer->m_pRootTrans->GetWorldPosition().x, pPlayer->m_pRootTrans->GetWorldPosition().y + 5.0f, pPlayer->m_pRootTrans->GetWorldPosition().z - 10.0f);

	for (int i = 0; i < ENEMYMAX_1; i++)
	{
		m_pTick[i] = new cTickFunc();
		m_pTick[i]->init(0.65f);

		m_pTickPlayer[i] = new cTickFunc();
		m_pTickPlayer[i]->init(0.25f);
	}
	m_pTickPlayer[ENEMYMAX_1] = new cTickFunc();
	m_pTickPlayer[ENEMYMAX_1]->init(0.25f);
	m_pTickBoss = new cTickFunc();
	m_pTickBoss->init(0.85f);


	bDraw = false;


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
	delete[] pEnemy1;
	delete[] pEnemy2;
	delete[] pEnemy3;
	delete[] pEnemy4;
	delete[] m_pTick;
	delete[] m_pTickPlayer;
	delete m_pTickBoss;
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
	//DeathCount = ENEMYMAX_1;
	DeathCount = ENEMYMAX_1;
	for (int i = 0; i < ENEMYMAX; i++)
	{
		if (pEnemy1[i]->GetHP() <= 0)
		{
			DeathCount--;
		}
		if (pEnemy2[i]->GetHP() <= 0)
		{
			DeathCount--;
		}
		if (pEnemy3[i]->GetHP() <= 0)
		{
			DeathCount--;
		}
		if (pEnemy4[i]->GetHP() <= 0)
		{
			DeathCount--;
		}
	}

	if (DeathCount == 0)
	{
		if (bDraw == false)
		{
			//renderObjects.push_back(pBoss->GetBaseObject()[0]);
			bDraw = true;
			LOG_MGR->AddLog("보스가 나타났다");
		}
	}

	this->pMainCamera->UpdateFrustum();
	this->cullObjects.clear();
	//프러스텀 안에 있니?
	for (int i = 0; i < vecGenPoint.size(); i++)
	{
		if (CalcLength(pPlayer->GetBaseObject()[0]->pTransform->GetWorldPosition(), vecGenPoint[i].p) <= 500.0f)
		{
			if (vecGenPoint[i].Gen == false)
			{
				if (i == 0)
				{
					for (int j = 0; j < ENEMYMAX; j++)
					{
						renderObjects.push_back(pEnemy1[j]->GetBaseObject()[0]);
					}

				}
				else if (i == 1)
				{
					for (int j = 0; j < ENEMYMAX; j++)
					{
						renderObjects.push_back(pEnemy2[j]->GetBaseObject()[0]);
					}
				}
				else if (i == 2)
				{
					for (int j = 0; j < ENEMYMAX; j++)
					{
						renderObjects.push_back(pEnemy3[j]->GetBaseObject()[0]);
					}
				}
				else if (i == 3)
				{
					for (int j = 0; j < ENEMYMAX; j++)
					{
						renderObjects.push_back(pEnemy4[j]->GetBaseObject()[0]);
					}
				}
				vecGenPoint[i].Gen = true;
			}
		}

		if (vecGenPoint[i].Gen == true)
		{
			if (i == 0)
			{
				for (int j = 0; j < ENEMYMAX; j++)
				{
					if (this->pMainCamera->Frustum.IsInFrustum(pEnemy1[j]->GetBaseObject()[0]))
					{
						pEnemy1[j]->Update(timDelta, pEntireMap->GetMap(), &pPlayer->GetWorldPosition());
					}
				}
			}
			if (i == 1)
			{
				for (int j = 0; j < ENEMYMAX; j++)
				{
					if (this->pMainCamera->Frustum.IsInFrustum(pEnemy2[j]->GetBaseObject()[0]))
					{
						pEnemy2[j]->Update(timDelta, pEntireMap->GetMap(), &pPlayer->GetWorldPosition());
					}
				}
			}
			if (i == 2)
			{
				for (int j = 0; j < ENEMYMAX; j++)
				{
					if (this->pMainCamera->Frustum.IsInFrustum(pEnemy3[j]->GetBaseObject()[0]))
					{
						pEnemy3[j]->Update(timDelta, pEntireMap->GetMap(), &pPlayer->GetWorldPosition());
					}
				}
			}
			if (i == 3)
			{
				for (int j = 0; j < ENEMYMAX; j++)
				{
					if (this->pMainCamera->Frustum.IsInFrustum(pEnemy4[j]->GetBaseObject()[0]))
					{
						pEnemy4[j]->Update(timDelta, pEntireMap->GetMap(), &pPlayer->GetWorldPosition());
					}
				}
			}
		}
	}

	if (bDraw == true)
	{
		//if (this->pMainCamera->Frustum.IsInFrustum(pBoss->GetBaseObject()[0]))
			pBoss->Update(timDelta, pEntireMap->GetMap(), &pPlayer->GetWorldPosition());
	}
	

	//20161206승현 getMap으로 바꾸기
	pPlayer->Update(D3DXVECTOR3(0.0f, 0.0f, 0.0f), timDelta, pEntireMap->GetMap());



	//업데이트
	//스킬이펙트
	pPlayerSkillEff->Update(timDelta);

	//검선이펙트
	pVecTrailRender[0]->Update(timDelta);
	pVecTrailRender[1]->Update(timDelta);


	if (pPlayer->GetIsAttack())
	{
		PlayerAttack(timDelta);

		D3DXVECTOR3 weaponPos;
		float		fTemp;

		pPlayer->GetBaseObject()[4]->BoundBox.GetWorldCenterRadius(pPlayer->GetBaseObject()[4]->pTransform, &weaponPos, &fTemp);
		pVecTrailRender[0]->Transform.SetWorldPosition(weaponPos);

		pPlayer->GetBaseObject()[5]->BoundBox.GetWorldCenterRadius(pPlayer->GetBaseObject()[5]->pTransform, &weaponPos, &fTemp);
		pVecTrailRender[1]->Transform.SetWorldPosition(weaponPos);
	}

	pEntireMap->m_pMap->pCharPosition = pPlayer->GetWorldPosition();

	//몬스터 공격
	MonsterAttack(timDelta);

	//this->pMainCamera->SetWorldPosition(D3DXVECTOR3(pPlayer->m_pRootTrans->GetWorldPosition().x + 5, pPlayer->m_pRootTrans->GetWorldPosition().y + 5, pPlayer->m_pRootTrans->GetWorldPosition().z + 1));
	this->pMainCamera->DefaultControl4(timDelta, pPlayer->m_pRootTrans); //★
	//this->pMainCamera->DefaultControl(timDelta); //★

	//쉐도우맵 준비
	//this->ReadyShadowMap(&this->renderObjects, NULL);
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

	//PlayerUI //20161207 승현추가
	if (pPlayerUI)
		pPlayerUI->Render();

	//보스몬스터유아이 //20161207 승현추가
	//if (pProgressBar_Boss)
	//	pProgressBar_Boss->Render();

	//컬링된 오브젝트만
	this->cullObjects.clear();
	for (int i = 0; i < this->renderObjects.size(); i++) {
		//프러스텀 안에 있니?
		if (this->pMainCamera->Frustum.IsInFrustum(this->renderObjects[i]))
			this->cullObjects.push_back(this->renderObjects[i]);
	}

	for (int i = 0; i < this->cullObjects.size(); i++)
	{
		cullObjects[i]->Render();
	}

	if(bDraw) pBoss->Render();

	//프러텀을 그려보장
	//this->pDirectionLightCamera->Frustum.RenderGizmo();
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
	//LOG_MGR->AddLog("%d", DeathCount);
	//LOG_MGR->AddLog("%d", renderObjects.size());
	//LOG_MGR->AddLog("%.2f", CalcLength(pPlayer->GetBaseObject()[0]->pTransform->GetWorldPosition(), vecGenPoint[3].p));
	//LOG_MGR->AddLog("%.2f", CalcLength(pPlayer->GetBaseObject()[0]->pTransform->GetWorldPosition(), D3DXVECTOR3(-128.f, -15.0f, 80.0f)));
	//LOG_MGR->AddLog("X : %.2f, Z : %.2f", pPlayer->GetBaseObject()[0]->pTransform->GetWorldPosition().x, pPlayer->GetBaseObject()[0]->pTransform->GetWorldPosition().z);
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

float cScene_main::CalcLength(D3DXVECTOR3 P1, D3DXVECTOR3 P2)
{
	float x = abs(P1.x - P2.x);
	float y = abs(P1.y - P2.y);
	float z = abs(P1.z - P2.z);

	float len = (x * x) + (y * y) + (z * z);

	return len;
}

void cScene_main::PlayerAttack(float timDelta)
{
	if (vecGenPoint[0].Gen == true)
		for (int i = 0; i < ENEMYMAX; i++)
		{
			if (pEnemy1[i]->GetState() != MonState::Death && pEnemy1[i]->GetState() != MonState::DeathWait)
			{
				m_pTickPlayer[i]->tickUpdate(timDelta);
				if (PHYSICS_MGR->IsOverlap(pPlayer->GetBaseObject()[4], pEnemy1[i]->GetBaseObject()[0]))
				{
					pEnemy1[i]->SetState(MonState::Stun);
					if (m_pTickPlayer[i]->tickStart())
					{
						pEnemy1[i]->SetHP(pEnemy1[i]->GetHP() - 1);
						//LOG_MGR->AddLog("%d번을 때렸다", i);
					}
						
					//0.0f, 0.75f, -0.025f
					D3DXVECTOR3 vCenter;
					float		ftemp;

					pPlayer->GetBaseObject()[4]->BoundBox.GetWorldCenterRadius(pPlayer->GetBaseObject()[4]->pTransform, &vCenter, &ftemp);
					pPlayerSkillEff->PlayEffect(EFF_ATTACK_01, vCenter);
				}

				if (PHYSICS_MGR->IsOverlap(pPlayer->GetBaseObject()[5], pEnemy1[i]->GetBaseObject()[0]))
				{
					pEnemy1[i]->SetState(MonState::Stun);
					if (m_pTickPlayer[i]->tickStart())
					{
						pEnemy1[i]->SetHP(pEnemy1[i]->GetHP() - 1);
						//LOG_MGR->AddLog("%d번을 때렸다", i);
					}
						
					//0.0f, 0.75f, -0.025f
					D3DXVECTOR3 vCenter;
					float		ftemp;

					pPlayer->GetBaseObject()[5]->BoundBox.GetWorldCenterRadius(pPlayer->GetBaseObject()[5]->pTransform, &vCenter, &ftemp);
					pPlayerSkillEff->PlayEffect(EFF_ATTACK_01, vCenter);
				}
			}
		}

	if (vecGenPoint[1].Gen == true)
		for (int i = 0; i < ENEMYMAX; i++)
		{
			if (pEnemy2[i]->GetState() != MonState::Death && pEnemy2[i]->GetState() != MonState::DeathWait)
			{
				m_pTickPlayer[i + 25]->tickUpdate(timDelta);
				if (PHYSICS_MGR->IsOverlap(pPlayer->GetBaseObject()[4], pEnemy2[i]->GetBaseObject()[0]))
				{
					pEnemy2[i]->SetState(MonState::Stun);
					if (m_pTickPlayer[i + 25]->tickStart())
					{
						pEnemy2[i]->SetHP(pEnemy2[i]->GetHP() - 1);
						//LOG_MGR->AddLog("%d번을 때렸다", i + 25);
					}
					
					//0.0f, 0.75f, -0.025f
					D3DXVECTOR3 vCenter;
					float		ftemp;

					pPlayer->GetBaseObject()[4]->BoundBox.GetWorldCenterRadius(pPlayer->GetBaseObject()[4]->pTransform, &vCenter, &ftemp);
					pPlayerSkillEff->PlayEffect(EFF_ATTACK_01, vCenter);
				}

				if (PHYSICS_MGR->IsOverlap(pPlayer->GetBaseObject()[5], pEnemy2[i]->GetBaseObject()[0]))
				{
					pEnemy2[i]->SetState(MonState::Stun);
					if (m_pTickPlayer[i + 25]->tickStart())
					{
						pEnemy2[i]->SetHP(pEnemy2[i]->GetHP() - 1);
						//LOG_MGR->AddLog("%d번을 때렸다", i + 25);
					}
					//0.0f, 0.75f, -0.025f
					D3DXVECTOR3 vCenter;
					float		ftemp;

					pPlayer->GetBaseObject()[5]->BoundBox.GetWorldCenterRadius(pPlayer->GetBaseObject()[5]->pTransform, &vCenter, &ftemp);
					pPlayerSkillEff->PlayEffect(EFF_ATTACK_01, vCenter);
				}
			}
		}

	if (vecGenPoint[2].Gen == true)
		for (int i = 0; i < ENEMYMAX; i++)
		{
			if (pEnemy3[i]->GetState() != MonState::Death && pEnemy3[i]->GetState() != MonState::DeathWait)
			{
				m_pTickPlayer[i + 50]->tickUpdate(timDelta);
				if (PHYSICS_MGR->IsOverlap(pPlayer->GetBaseObject()[4], pEnemy3[i]->GetBaseObject()[0]))
				{
					pEnemy3[i]->SetState(MonState::Stun);
					if (m_pTickPlayer[i + 50]->tickStart())
					{
						pEnemy3[i]->SetHP(pEnemy3[i]->GetHP() - 1);
						//LOG_MGR->AddLog("%d번을 때렸다", i + 50);
					}
					//0.0f, 0.75f, -0.025f
					D3DXVECTOR3 vCenter;
					float		ftemp;

					pPlayer->GetBaseObject()[4]->BoundBox.GetWorldCenterRadius(pPlayer->GetBaseObject()[4]->pTransform, &vCenter, &ftemp);
					pPlayerSkillEff->PlayEffect(EFF_ATTACK_01, vCenter);
				}

				if (PHYSICS_MGR->IsOverlap(pPlayer->GetBaseObject()[5], pEnemy3[i]->GetBaseObject()[0]))
				{
					pEnemy3[i]->SetState(MonState::Stun);
					if (m_pTickPlayer[i + 50]->tickStart())
					{
						pEnemy3[i]->SetHP(pEnemy3[i]->GetHP() - 1);
						//LOG_MGR->AddLog("%d번을 때렸다", i + 50);
					}
					//0.0f, 0.75f, -0.025f
					D3DXVECTOR3 vCenter;
					float		ftemp;

					pPlayer->GetBaseObject()[5]->BoundBox.GetWorldCenterRadius(pPlayer->GetBaseObject()[5]->pTransform, &vCenter, &ftemp);
					pPlayerSkillEff->PlayEffect(EFF_ATTACK_01, vCenter);
				}
			}
		}

	if (vecGenPoint[3].Gen == true)
		for (int i = 0; i < ENEMYMAX; i++)
		{
			if (pEnemy4[i]->GetState() != MonState::Death && pEnemy4[i]->GetState() != MonState::DeathWait)
			{
				m_pTickPlayer[i + 75]->tickUpdate(timDelta);
				if (PHYSICS_MGR->IsOverlap(pPlayer->GetBaseObject()[4], pEnemy4[i]->GetBaseObject()[0]))
				{
					pEnemy4[i]->SetState(MonState::Stun);
					if (m_pTickPlayer[i + 75]->tickStart())
					{
						pEnemy4[i]->SetHP(pEnemy4[i]->GetHP() - 1);
						//LOG_MGR->AddLog("%d번을 때렸다", i + 75);
					}
					//0.0f, 0.75f, -0.025f
					D3DXVECTOR3 vCenter;
					float		ftemp;

					pPlayer->GetBaseObject()[4]->BoundBox.GetWorldCenterRadius(pPlayer->GetBaseObject()[4]->pTransform, &vCenter, &ftemp);
					pPlayerSkillEff->PlayEffect(EFF_ATTACK_01, vCenter);
				}

				if (PHYSICS_MGR->IsOverlap(pPlayer->GetBaseObject()[5], pEnemy4[i]->GetBaseObject()[0]))
				{
					pEnemy4[i]->SetState(MonState::Stun);
					if (m_pTickPlayer[i + 75]->tickStart())
					{
						pEnemy4[i]->SetHP(pEnemy4[i]->GetHP() - 1);
						//LOG_MGR->AddLog("%d번을 때렸다", i + 75);
					}
					//0.0f, 0.75f, -0.025f
					D3DXVECTOR3 vCenter;
					float		ftemp;

					pPlayer->GetBaseObject()[5]->BoundBox.GetWorldCenterRadius(pPlayer->GetBaseObject()[5]->pTransform, &vCenter, &ftemp);
					pPlayerSkillEff->PlayEffect(EFF_ATTACK_01, vCenter);
				}
			}
		}

	if (DeathCount == 0)
	{
		if (pBoss->GetState() != MonState::Death && pBoss->GetState() != MonState::DeathWait)
		{
			m_pTickPlayer[ENEMYMAX_1]->tickUpdate(timDelta);
			if (PHYSICS_MGR->IsOverlap(pPlayer->GetBaseObject()[4], pBoss->GetBaseObject()[0]))
			{
				//pEnemy4[i]->SetState(MonState::Stun);
				if (m_pTickPlayer[ENEMYMAX_1]->tickStart())
				{
					pBoss->SetHP(pBoss->GetHP() - 1);
					//LOG_MGR->AddLog("%d번을 때렸다", i + 75);
				}
				//0.0f, 0.75f, -0.025f
				D3DXVECTOR3 vCenter;
				float		ftemp;

				pPlayer->GetBaseObject()[4]->BoundBox.GetWorldCenterRadius(pPlayer->GetBaseObject()[4]->pTransform, &vCenter, &ftemp);
				pPlayerSkillEff->PlayEffect(EFF_ATTACK_01, vCenter);
			}

			if (PHYSICS_MGR->IsOverlap(pPlayer->GetBaseObject()[5], pBoss->GetBaseObject()[0]))
			{
				//pEnemy4[i]->SetState(MonState::Stun);
				if (m_pTickPlayer[ENEMYMAX_1]->tickStart())
				{
					pBoss->SetHP(pBoss->GetHP() - 1);
					//LOG_MGR->AddLog("%d번을 때렸다", i + 75);
				}
				//0.0f, 0.75f, -0.025f
				D3DXVECTOR3 vCenter;
				float		ftemp;

				pPlayer->GetBaseObject()[5]->BoundBox.GetWorldCenterRadius(pPlayer->GetBaseObject()[5]->pTransform, &vCenter, &ftemp);
				pPlayerSkillEff->PlayEffect(EFF_ATTACK_01, vCenter);
			}
		}
	}
}

void cScene_main::GenSetup()
{
	//젠위치
	ST_GenPoint Point1;
	float y = pEntireMap->GetMap()->GetHeight(38.0f, 41.0f);
	Point1.p = D3DXVECTOR3(73.0f, y, 43.0f);
	Point1.Gen = false;

	ST_GenPoint Point2;
	y = pEntireMap->GetMap()->GetHeight(43.0f, 53.0f);
	Point2.p = D3DXVECTOR3(43.0f, y, 53.0f);
	Point2.Gen = false;

	ST_GenPoint Point3;
	y = pEntireMap->GetMap()->GetHeight(-27.0f, 43.0f);
	Point3.p = D3DXVECTOR3(-27.0f, y, 43.0f);
	Point3.Gen = false;

	ST_GenPoint Point4;
	y = pEntireMap->GetMap()->GetHeight(-72.0f, 53.0f);
	Point4.p = D3DXVECTOR3(-72.0f, y, 53.0f);
	Point4.Gen = false;

	vecGenPoint.push_back(Point1);
	vecGenPoint.push_back(Point2);
	vecGenPoint.push_back(Point3);
	vecGenPoint.push_back(Point4);
}

void cScene_main::MonsterSetup()
{
	//몬스터
	for (int x = 0; x < 5; x++)
	{
		for (int z = 0; z < 5; z++)
		{
			pEnemy1[(x * 5) + z] = new cEnemy();
			pEnemy1[(x * 5) + z]->Setup("./Tera/Monster/Kalan.X", &D3DXVECTOR3(70.0f + (x * 1), -10.0f, 40.0f + (z * 1)));
		}
	}

	for (int x = 0; x < 5; x++)
	{
		for (int z = 0; z < 5; z++)
		{
			pEnemy2[(x * 5) + z] = new cEnemy();
			pEnemy2[(x * 5) + z]->Setup("./Tera/Monster/Kalan.X", &D3DXVECTOR3(40.0f + (x * 1), -10.0f, 50.0f + (z * 1)));
		}
	}

	for (int x = 0; x < 5; x++)
	{
		for (int z = 0; z < 5; z++)
		{
			pEnemy3[(x * 5) + z] = new cEnemy();
			pEnemy3[(x * 5) + z]->Setup("./Tera/Monster/Kalan.X", &D3DXVECTOR3(-27.0f + (x * 1), -10.0f, 40.0f + (z * 1)));
		}
	}

	for (int x = 0; x < 5; x++)
	{
		for (int z = 0; z < 5; z++)
		{
			pEnemy4[(x * 5) + z] = new cEnemy();
			pEnemy4[(x * 5) + z]->Setup("./Tera/Monster/Kalan.X", &D3DXVECTOR3(-72.0f + (x * 1), -10.0f, 50.0f + (z * 1)));
		}
	}
}

void cScene_main::MonsterAttack(float timDelta)
{
	for (int i = 0; i < ENEMYMAX; i++)
	{
		if (pEnemy1[i]->GetState() == MonState::Attack)
		{
			
			m_pTick[i]->tickUpdate(timDelta);

			if (PHYSICS_MGR->IsOverlap(pEnemy1[i]->pWeaponTrans, &renderObjects[i]->BoundBox01, pPlayer->m_pRootTrans, &pPlayer->GetBaseObject()[0]->BoundBox))
			{
				if (m_pTick[i]->tickStart())
				{

				}
				//	LOG_MGR->AddLog("%d번 에게 맞았다!", i);
			}
		}
		if (pEnemy2[i]->GetState() == MonState::Attack)
		{

			m_pTick[i + 25]->tickUpdate(timDelta);

			if (PHYSICS_MGR->IsOverlap(pEnemy2[i]->pWeaponTrans, &renderObjects[i + 25]->BoundBox01, pPlayer->m_pRootTrans, &pPlayer->GetBaseObject()[0]->BoundBox))
			{
				if (m_pTick[i + 25]->tickStart())
				{

				}
				//	LOG_MGR->AddLog("%d번 에게 맞았다!", i + 25);
			}
		}
		if (pEnemy3[i]->GetState() == MonState::Attack)
		{

			m_pTick[i + 50]->tickUpdate(timDelta);

			if (PHYSICS_MGR->IsOverlap(pEnemy3[i]->pWeaponTrans, &renderObjects[i + 50]->BoundBox01, pPlayer->m_pRootTrans, &pPlayer->GetBaseObject()[0]->BoundBox))
			{
				if (m_pTick[i + 50]->tickStart())
				{

				}
				//	LOG_MGR->AddLog("%d번 에게 맞았다!", i + 50);
			}
		}
		if (pEnemy4[i]->GetState() == MonState::Attack)
		{

			m_pTick[i + 75]->tickUpdate(timDelta);

			if (PHYSICS_MGR->IsOverlap(pEnemy4[i]->pWeaponTrans, &renderObjects[i + 75]->BoundBox01, pPlayer->m_pRootTrans, &pPlayer->GetBaseObject()[0]->BoundBox))
			{
				if (m_pTick[i + 75]->tickStart())
				{

				}
				//	LOG_MGR->AddLog("%d번 에게 맞았다!", i + 75);
			}
		}
	}

	if (pBoss->GetState() == MonState::Attack)
	{
		m_pTickBoss->tickUpdate(timDelta);

		if (PHYSICS_MGR->IsOverlap(pBoss->pWeaponTrans, &pBoss->GetBaseObject()[0]->BoundBox01, pPlayer->m_pRootTrans, &pPlayer->GetBaseObject()[0]->BoundBox))
		{
			if (m_pTickBoss->tickStart())
				LOG_MGR->AddLog("보스에게 맞았다!");
		}
	}
}
