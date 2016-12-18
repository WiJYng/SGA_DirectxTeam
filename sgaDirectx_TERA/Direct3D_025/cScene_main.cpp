#include "stdafx.h"
#include "cScene_main.h"
#include "cLight_Point.h"
#include "cLight_Direction.h"
#include "cXMesh_Static.h"
#include "cBaseObject.h"
#include "cTransform.h"
#include "cCamera.h"
#include "cCharacter.h"
#include "cEnemy.h"
#include "cBoss.h"
#include "cMeshMap.h"
#include "cTerrain.h"
#include "cMap.h"
#include "cPlayerUI.h"
#include "cProgressBar_Boss.h"
#include "cTickFunc.h"
#include "cVideo.h"

#include "cPlayerSkillEffect.h"
#include "cBossEffect.h"
#include "cLocationEffect.h"

#include "cAudioFile.h"


cScene_main::cScene_main()
{
}
cScene_main::~cScene_main()
{
}


HRESULT cScene_main::Scene_Init()
{
	//Sound Loading
	InitSoundResource();
	
	m_pAudioFile = new cAudioFile;
	m_pAudioFile->Setup();

	g_CursorImgType = 0;
	g_bRender = true;

	SCENE_MGR->fProgress = 40.0f;
	SCENE_MGR->fString = "Map loading..";
	this->SetEnvironment("Tera/Map/Sky.dds");

	pEntireMap = new cMap();
	pEntireMap->Setup();


	SCENE_MGR->fProgress = 50.0f;
	SCENE_MGR->fString = "Player loading..";
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
	

	SCENE_MGR->fProgress = 80.0f;
	SCENE_MGR->fString = "Monster loading..";
	//몬스터
	MonsterSetup();

	//보스
	pBoss = new cBoss();
	pBoss->Setup("./Tera/Monster/Drowned.X", &D3DXVECTOR3(-120.f, -15.0f, 76.0f));
	//pBoss->Setup("./Tera/Monster/Drowned.X", &D3DXVECTOR3(70.0f, 0.0f, 65.0f));
	
	m_pBossVideo = new cVideo;
	m_pBossVideo->Init();
	m_bBossVideoPlay = false;
	m_bBossVideoEnd = false;

	//보스몬스터UI 테스트 //20161207 승현추가
	//pProgressBar_Boss = new cProgressBar_Boss();
	//pProgressBar_Boss->Setup();

	//렌더 오브젝트 푸쉬
	//this->renderObjects.push_back(pMapObject);

	SCENE_MGR->fProgress = 100.0f;
	SCENE_MGR->fString = "loading complete";
	//라이트 위치
	this->pSceneBaseDirectionLight->pTransform->SetWorldPosition(0, 0, 0);
	this->pSceneBaseDirectionLight->pTransform->SetRotateWorld(90.0f * ONE_RAD, 0, 0);
	
	cTransform* tempTrans = pPlayer->m_pRootTrans;
	this->pMainCamera->AttachTo(tempTrans);
	this->pMainCamera->SetWorldPosition(pPlayer->m_pRootTrans->GetWorldPosition().x, pPlayer->m_pRootTrans->GetWorldPosition().y + 3.0f, pPlayer->m_pRootTrans->GetWorldPosition().z - 5.0f);
	
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

	//Effect
	pPlayerSkillEff = new cPlayerSkillEffect;
	pPlayerSkillEff->Setup();

	pLocationEffect = new cLocationEffect;
	pLocationEffect->Setup(); 


	bDraw = false;
	//pPlayerUI->SetKillNum(0);
	pPlayerUI->SetMp(100);
	pPlayerUI->SetMpMax(100);
	
	SOUND_MGR->play("BGM_01", 0.5f);
	return S_OK;
}

void cScene_main::Scene_Release()
{
	m_pBossVideo->Release();
	SAFE_DELETE(m_pBossVideo);

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

	SAFE_DELETE(pPlayerSkillEff);

}

void cScene_main::Scene_Update(float timDelta)
{
	
	//마우스
	//g_CursorImgType = 0;
	//HCURSOR hcur;
	//hcur = LoadCursorFromFile("./Tera/UI/Mouse/Arrow.cur");
	//SetCursor(hcur);

	//배경음악
	//if (!SOUND_MGR->isPlaySound("BGM_01"))
	//	SOUND_MGR->play("BGM_01", 0.3f);


	pPlayerUI->Update();
	pPlayerUI->SetHp(pPlayer->m_fHP);
	pPlayerUI->SetHpMax(pPlayer->m_fMaxHP);

	DeathCount = ENEMYMAX_1;
	//DeathCount = 99;
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
	pPlayerUI->SetKillNum(DeathCount);


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

	if (pPlayer->GetIsAttack())
	{
		PlayerAttack(timDelta);

		D3DXVECTOR3 weaponPos;
		float		fTemp;

		pPlayer->GetBaseObject()[4]->BoundBox.GetWorldCenterRadius(pPlayer->GetBaseObject()[4]->pTransform, &weaponPos, &fTemp);
		pPlayerSkillEff->PlayEffect(PLAYER_ATTACK_01_L, weaponPos);

		pPlayer->GetBaseObject()[5]->BoundBox.GetWorldCenterRadius(pPlayer->GetBaseObject()[5]->pTransform, &weaponPos, &fTemp);
		pPlayerSkillEff->PlayEffect(PLAYER_ATTACK_01_R, weaponPos);
	}

	pEntireMap->m_pMap->pCharPosition = pPlayer->GetWorldPosition();

	//몬스터 공격
	MonsterAttack(timDelta);

	//스킬이펙트
	pPlayerSkillEff->Update(timDelta);
	pLocationEffect->Update(timDelta);

	//if (KEY_MGR->IsOnceDown(VK_SPACE))
	//{
	//	pLocationEffect->PlayEffect(LOCATION_ARROW_01, pPlayer->GetWorldPosition());
	//}

	//this->pMainCamera->SetWorldPosition(D3DXVECTOR3(pPlayer->m_pRootTrans->GetWorldPosition().x + 5, pPlayer->m_pRootTrans->GetWorldPosition().y + 5, pPlayer->m_pRootTrans->GetWorldPosition().z + 1));
	
	//************************************
	//this->pMainCamera->DefaultControl(timDelta);
	this->pMainCamera->DefaultControl4(timDelta, pPlayer->m_pRootTrans); //★



	//this->pMainCamera->ShakeUpdate(timDelta);
	//this->pMainCamera->DefaultControl(timDelta); //★

	if (DeathCount <= 0)
	{
		if (!m_bBossVideoPlay)
		{
			m_bBossVideoPlay = true;
			g_bRender = false;
			m_pBossVideo->Play("./Video/Boss.wmv");
			pPlayerUI->SetBossMeet(true);
			//m_bBossVideoPlay = false;
			SOUND_MGR->stop("BGM_01");
	
		}
		pPlayerUI->SetKillNum(-1);
		if (!m_pBossVideo->GetIsPlay())
		{
			//LOG_MGR->AddLog("끝");
			if (!m_bBossVideoEnd)
			{
				g_bRender = true;
				m_pBossVideo->Stop();
				pPlayerUI->SetBossMeet(true);
				pBoss->SetUIon(true);
				m_bBossVideoEnd = true;
				SOUND_MGR->play("BGM_02", 0.5);
			}
		}
	}



	if (KEY_MGR->IsOnceDown('1'))
	{
		m_bBossVideoPlay = true;
		g_bRender = false;
		m_pBossVideo->Play("./Video/Boss.wmv");
		pPlayerUI->SetBossMeet(true);
		//m_bBossVideoPlay = false;
		SOUND_MGR->stop("BGM_01");
	}
	if (KEY_MGR->IsOnceDown('2'))
	{
		g_bRender = true;
		m_pBossVideo->Stop();
		pPlayerUI->SetBossMeet(true);
		pBoss->SetUIon(true);
		m_bBossVideoEnd = true;
		SOUND_MGR->play("BGM_02", 0.5f);
	}

	//if (KEY_MGR->IsStayDown('0'))
	if (pBoss->bS)
	{
		//this->pMainCamera->ShakePos(0.00000000001, 0);
		this->pMainCamera->ShakeRot(0.01, -1);
		//this->pMainCamera->LookDirection(pPlayer->GetBaseObject()[0]->pTransform->GetWorldPosition());
		this->pMainCamera->ShakeUpdate(timDelta);
	}

	if (KEY_MGR->IsOnceDown('B'))
	{
		g_bBox = !g_bBox;
	}

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
	MonsterRender();

	//this->cullObjects.clear();
	//for (int i = 0; i < this->renderObjects.size(); i++) {
	//	//프러스텀 안에 있니?
	//	if (this->pMainCamera->Frustum.IsInFrustum(this->renderObjects[i]))
	//	{
	//		
	//	}
	//		//this->cullObjects.push_back(this->renderObjects[i]);
	//}
	//
	//for (int i = 0; i < this->cullObjects.size(); i++)
	//{
	//	cullObjects[i]->Render();
	//}

	if(bDraw) pBoss->Render();

	//프러텀을 그려보장
	//this->pDirectionLightCamera->Frustum.RenderGizmo();
	this->pSceneBaseDirectionLight->pTransform->RenderGimozo();

	//-----------------------------
	//Effect Rendering
	//-----------------------------

	if (pPlayerSkillEff)
		pPlayerSkillEff->Render();

	if (pLocationEffect)
		pLocationEffect->Render();


	

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
					pPlayerSkillEff->PlayEffect(PLAYER_ATTACL_02, vCenter);

					//SOUND TEST -- WJY
					//if (!SOUND_MGR->isPlaySound("ATT_01"))
					//	SOUND_MGR->play("ATT_01");
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
					pPlayerSkillEff->PlayEffect(PLAYER_ATTACL_02, vCenter);

					//SOUND TEST -- WJY
					//if (!SOUND_MGR->isPlaySound("ATT_01"))
					//	SOUND_MGR->play("ATT_01");
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
					pPlayerSkillEff->PlayEffect(PLAYER_ATTACL_02, vCenter);
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
					pPlayerSkillEff->PlayEffect(PLAYER_ATTACL_02, vCenter);
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
					pPlayerSkillEff->PlayEffect(PLAYER_ATTACL_02, vCenter);
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
					pPlayerSkillEff->PlayEffect(PLAYER_ATTACL_02, vCenter);
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
					pPlayerSkillEff->PlayEffect(PLAYER_ATTACL_02, vCenter);
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
					pPlayerSkillEff->PlayEffect(PLAYER_ATTACL_02, vCenter);
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
				pPlayerSkillEff->PlayEffect(PLAYER_ATTACL_02, vCenter);
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
				pPlayerSkillEff->PlayEffect(PLAYER_ATTACL_02, vCenter);
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
					if (pPlayer->m_fHP > 0)
					{
						(pPlayer->m_fHP)--;
					}
					else
					{
						pPlayer->m_fHP = 0;
					}
				D3DXVECTOR3 pos;
				float fTemp;
				renderObjects[i]->BoundBox01.GetWorldCenterRadius(pEnemy1[i]->pWeaponTrans, &pos, &fTemp);
				pEnemy1[i]->pEnemySkillEff->PlayEffect(ENEMY_ATTACK_02, pos);
				}
			}
		}
		if (pEnemy2[i]->GetState() == MonState::Attack)
		{

			m_pTick[i + 25]->tickUpdate(timDelta);

			if (PHYSICS_MGR->IsOverlap(pEnemy2[i]->pWeaponTrans, &renderObjects[i + 25]->BoundBox01, pPlayer->m_pRootTrans, &pPlayer->GetBaseObject()[0]->BoundBox))
			{
				if (m_pTick[i + 25]->tickStart())
				{
					if (pPlayer->m_fHP > 0)
					{
						(pPlayer->m_fHP)--;
					}
					else
					{
						pPlayer->m_fHP = 0;
					}
					D3DXVECTOR3 pos;
					float fTemp;
					renderObjects[i + 25]->BoundBox01.GetWorldCenterRadius(pEnemy2[i]->pWeaponTrans, &pos, &fTemp);
					pEnemy2[i]->pEnemySkillEff->PlayEffect(ENEMY_ATTACK_02, pos);
				}
			}
		}
		if (pEnemy3[i]->GetState() == MonState::Attack)
		{

			m_pTick[i + 50]->tickUpdate(timDelta);

			if (PHYSICS_MGR->IsOverlap(pEnemy3[i]->pWeaponTrans, &renderObjects[i + 50]->BoundBox01, pPlayer->m_pRootTrans, &pPlayer->GetBaseObject()[0]->BoundBox))
			{
				if (m_pTick[i + 50]->tickStart())
				{
					if (pPlayer->m_fHP > 0)
					{
						(pPlayer->m_fHP)--;
					}
					else
					{
						pPlayer->m_fHP = 0;
					}
					D3DXVECTOR3 pos;
					float fTemp;

					renderObjects[i + 50]->BoundBox01.GetWorldCenterRadius(pEnemy3[i]->pWeaponTrans, &pos, &fTemp);
					pEnemy3[i]->pEnemySkillEff->PlayEffect(ENEMY_ATTACK_02, pos);
				}
			}
		}
		if (pEnemy4[i]->GetState() == MonState::Attack)
		{

			m_pTick[i + 75]->tickUpdate(timDelta);

			if (PHYSICS_MGR->IsOverlap(pEnemy4[i]->pWeaponTrans, &renderObjects[i + 75]->BoundBox01, pPlayer->m_pRootTrans, &pPlayer->GetBaseObject()[0]->BoundBox))
			{
				if (m_pTick[i + 75]->tickStart())
				{
					if (pPlayer->m_fHP > 0)
					{
						(pPlayer->m_fHP)--;
					}
					else
					{
						pPlayer->m_fHP = 0;
					}
					D3DXVECTOR3 pos;
					float fTemp;

					renderObjects[i + 75]->BoundBox01.GetWorldCenterRadius(pEnemy4[i]->pWeaponTrans, &pos, &fTemp);
					pEnemy4[i]->pEnemySkillEff->PlayEffect(ENEMY_ATTACK_02, pos);
				}
			}
		}
	}

	if (pBoss->GetState() == MonState::Attack)
	{
		m_pTickBoss->tickUpdate(timDelta);

		if (PHYSICS_MGR->IsOverlap(pBoss->pWeaponTrans, &pBoss->GetBaseObject()[0]->BoundBox01, pPlayer->m_pRootTrans, &pPlayer->GetBaseObject()[0]->BoundBox))
		{
			if (m_pTickBoss->tickStart())
			{
				if (pPlayer->m_fHP > 0)
				{
					pPlayer->m_fHP = (pPlayer->m_fHP) - 10;
				}
				
				if (pPlayer->m_fHP <= 0)
				{
					pPlayer->m_fHP = 0;
				}

				D3DXVECTOR3 pos;
				float fTemp;

				//pBoss->GetBaseObject()[0]->BoundBox01.GetWorldCenterRadius(pBoss->pWeaponTrans, &pos, &fTemp);
				pPlayer->GetBaseObject()[0]->BoundBox.GetWorldCenterRadius(pPlayer->m_pRootTrans, &pos, &fTemp);
				pos.y -= 0.25;
				pBoss->pBossEffect->PlayEffect(BOSS_ATTACK_01, pos);
			}

			//LOG_MGR->AddLog("보스에게 맞았다!");
		}
	}
}

void cScene_main::MonsterRender()
{
	//0번포인트
	if (vecGenPoint[0].Gen)
	{
		for (int i = 0; i < ENEMYMAX; i++)
		{
			if (this->pMainCamera->Frustum.IsInFrustum(pEnemy1[i]->GetBaseObject()[0]))
			{
				pEnemy1[i]->Render();
			}
		}
	}
	//1번포인트
	if (vecGenPoint[1].Gen)
	{
		for (int i = 0; i < ENEMYMAX; i++)
		{
			if (this->pMainCamera->Frustum.IsInFrustum(pEnemy2[i]->GetBaseObject()[0]))
			{
				pEnemy2[i]->Render();
			}
		}
	}
	//2번포인트
	if (vecGenPoint[2].Gen)
	{
		for (int i = 0; i < ENEMYMAX; i++)
		{
			if (this->pMainCamera->Frustum.IsInFrustum(pEnemy3[i]->GetBaseObject()[0]))
			{
				pEnemy3[i]->Render();
			}
		}
	}
	//3번포인트
	if (vecGenPoint[3].Gen)
	{
		for (int i = 0; i < ENEMYMAX; i++)
		{
			if (this->pMainCamera->Frustum.IsInFrustum(pEnemy4[i]->GetBaseObject()[0]))
			{
				pEnemy4[i]->Render();
			}
		}
	}
}


void cScene_main::InitSoundResource()
{
	//캐릭터 목소리
	SOUND_MGR->addSound("ATT_01", "./Tera/Audio/Player/Attack/AttackF_00.ogg", false, false);
	SOUND_MGR->addSound("ATT_02", "./Tera/Audio/Player/Attack/AttackF_01.ogg", false, false);
	SOUND_MGR->addSound("ATT_03", "./Tera/Audio/Player/Attack/AttackF_02.ogg", false, false);
	SOUND_MGR->addSound("ATT_04", "./Tera/Audio/Player/Attack/AttackF_03.ogg", false, false);
	SOUND_MGR->addSound("ATT_05", "./Tera/Audio/Player/Attack/AttackF_04.ogg", false, false);
	
	SOUND_MGR->addSound("ATT_06", "./Tera/Audio/Player/Attack/AttackM_00.ogg", false, false);
	SOUND_MGR->addSound("ATT_07", "./Tera/Audio/Player/Attack/AttackM_01.ogg", false, false);
	SOUND_MGR->addSound("ATT_08", "./Tera/Audio/Player/Attack/AttackM_02.ogg", false, false);
	SOUND_MGR->addSound("ATT_09", "./Tera/Audio/Player/Attack/AttackM_03.ogg", false, false);
	SOUND_MGR->addSound("ATT_10", "./Tera/Audio/Player/Attack/AttackM_04.ogg", false, false);

	SOUND_MGR->addSound("ATT_11", "./Tera/Audio/Player/Attack/AttackL_00.ogg", false, false);
	SOUND_MGR->addSound("ATT_12", "./Tera/Audio/Player/Attack/AttackL_01.ogg", false, false);
	SOUND_MGR->addSound("ATT_13", "./Tera/Audio/Player/Attack/AttackL_02.ogg", false, false);
	SOUND_MGR->addSound("ATT_14", "./Tera/Audio/Player/Attack/AttackL_03.ogg", false, false);
	SOUND_MGR->addSound("ATT_15", "./Tera/Audio/Player/Attack/AttackL_04.ogg", false, false);
	SOUND_MGR->addSound("ATT_16", "./Tera/Audio/Player/Attack/AttackL_05.ogg", false, false);

	//캐릭터 스킬
	//SOUND_MGR->addSound("ATT_S01", "./Tera/Audio/Player/Skill/Warrior_Attack_00.ogg", false, false);
	SOUND_MGR->addSound("ATT_S01", "./Tera/Audio/Player/Skill/Attack_01.ogg", false, false);
	//SOUND_MGR->addSound("ATT_S02", "./Tera/Audio/Player/Skill/Warrior_Attack_01.ogg", false, false);
	SOUND_MGR->addSound("ATT_S02", "./Tera/Audio/Player/Skill/Attack_02.ogg", false, false);
	//SOUND_MGR->addSound("ATT_S03", "./Tera/Audio/Player/Skill/Warrior_Attack_02.ogg", false, false);
	SOUND_MGR->addSound("ATT_S03", "./Tera/Audio/Player/Skill/Attack_03.ogg", false, false);
	//SOUND_MGR->addSound("ATT_S04", "./Tera/Audio/Player/Skill/Warrior_Attack_03.ogg", false, false);
	SOUND_MGR->addSound("ATT_S04", "./Tera/Audio/Player/Skill/Attack_04.ogg", false, false);

	SOUND_MGR->addSound("RAPID_01", "./Tera/Audio/Player/Skill/Rapid_01.ogg", false, false);
	SOUND_MGR->addSound("RAPID_02", "./Tera/Audio/Player/Skill/Rapid_02.ogg", false, false);
	SOUND_MGR->addSound("RAPID_03", "./Tera/Audio/Player/Skill/Warrior_RivalDancing_00.ogg", false, false);
	SOUND_MGR->addSound("RAPID_04", "./Tera/Audio/Player/Skill/Warrior_RivalDancing_01.ogg", false, false);

	//몬스터
	SOUND_MGR->addSound("M_ATT_01", "./Tera/Audio/Monster/KalanHeavyWarrior_Atk04.ogg", false, false);
	SOUND_MGR->addSound("M_DEATH", "./Tera/Audio/Monster/KalanHeavyWarrior_Death.ogg", false, false);

	//보스
	SOUND_MGR->addSound("B_ATT_01", "./Tera/Audio/Boss/DrownedSailor_Atk06.ogg", false, false);
	SOUND_MGR->addSound("B_ATT_02", "./Tera/Audio/Boss/DrownedSailor_Atk01.ogg", false, false);
	SOUND_MGR->addSound("B_ATT_03", "./Tera/Audio/Boss/DrownedSailor_Atk03.ogg", false, false);
	SOUND_MGR->addSound("B_DEATH", "./Tera/Audio/Boss/DrownedSailor_Death.ogg", false, false);
	
	//걷는소리
	SOUND_MGR->addSound("RS", "./Tera/Audio/Player/PCStep_Dirt_RS_01.ogg", false, false);
	
	//배경음
	SOUND_MGR->addSound("BGM_01", "./Tera/Audio/Tricksome.mp3", true, true);
	SOUND_MGR->addSound("BGM_02", "./Tera/Audio/Crown_00.ogg", true, true);
	SOUND_MGR->addSound("BGM_03", "./Tera/Audio/EndBg.mp3", true, true);
}