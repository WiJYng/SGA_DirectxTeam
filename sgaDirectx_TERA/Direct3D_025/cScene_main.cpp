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


cScene_main::cScene_main()
{
}
cScene_main::~cScene_main()
{
}


HRESULT cScene_main::Scene_Init()
{
	g_bRender = true;

	SCENE_MGR->fProgress = 40.0f;
	SCENE_MGR->fString = "Map loading..";
	this->SetEnvironment("Tera/Map/Sky.dds");

	pEntireMap = new cMap();
	pEntireMap->Setup();


	SCENE_MGR->fProgress = 50.0f;
	SCENE_MGR->fString = "Player loading..";
	//�� ��ġ
	GenSetup();

	//�÷��̾�
	pPlayer = new cCharacter();
	pPlayer->Setup("./Tera/Character/Elin_Body_WDCR.X"
		, "./Tera/Character/Elin_Face_WDCR.X"
		, "./Tera/Character/Elin_Hair_WDCR.X"
		, "./Tera/Character/Elin_Tail_WDCR.X"
		, "./Tera/Character/Weapon_R.X"
		, "./Tera/Character/Weapon_R.X");

	//PlayerUI //20161207 �����߰�
	pPlayerUI = new cPlayerUI();
	pPlayerUI->Setup();
	

	SCENE_MGR->fProgress = 80.0f;
	SCENE_MGR->fString = "Monster loading..";
	//����
	MonsterSetup();

	//����
	pBoss = new cBoss();
	//pBoss->Setup("./Tera/Monster/Drowned.X", &D3DXVECTOR3(-120.f, -15.0f, 76.0f));
	pBoss->Setup("./Tera/Monster/Drowned.X", &D3DXVECTOR3(70.0f, 0.0f, 65.0f));
	
	m_pBossVideo = new cVideo;
	m_pBossVideo->Init();
	m_bBossVideoPlay = false;
	m_bBossVideoEnd = false;

	//��������UI �׽�Ʈ //20161207 �����߰�
	//pProgressBar_Boss = new cProgressBar_Boss();
	//pProgressBar_Boss->Setup();

	//���� ������Ʈ Ǫ��
	//this->renderObjects.push_back(pMapObject);

	SCENE_MGR->fProgress = 100.0f;
	SCENE_MGR->fString = "loading complete";
	//����Ʈ ��ġ
	this->pSceneBaseDirectionLight->pTransform->SetWorldPosition(0, 0, 0);
	this->pSceneBaseDirectionLight->pTransform->SetRotateWorld(90.0f * ONE_RAD, 0, 0);
	
	cTransform* tempTrans = pPlayer->m_pRootTrans;
	//tempTrans->SetRotateWorld(0.0f, 90.0f, 0.0f);

	this->pMainCamera->AttachTo(tempTrans);
	//this->pMainCamera->SetWorldPosition(pPlayer->m_pRootTrans->GetWorldPosition().x, pPlayer->m_pRootTrans->GetWorldPosition().y + 5.0f, pPlayer->m_pRootTrans->GetWorldPosition().z - 10.0f);
	this->pMainCamera->SetWorldPosition(pPlayer->m_pRootTrans->GetWorldPosition().x, pPlayer->m_pRootTrans->GetWorldPosition().y + 3.0f, pPlayer->m_pRootTrans->GetWorldPosition().z - 5.0f);
	//this->pMainCamera->RotateWorld(D3DXVECTOR3(0, 0, 3));
	//this->pMainCamera->SetWorldPosition(pPlayer->m_pRootTrans->GetWorldPosition().x, pPlayer->m_pRootTrans->GetWorldPosition().y + 2.0f, pPlayer->m_pRootTrans->GetWorldPosition().z - 2.0f);
	//this->pMainCamera->SetWorldPosition(0,10.0f, 1);
	//this->pMainCamera->ShakePos(10.0f, 10.0f);

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

	//effTest = new cBossEffect;
	//effTest->Setup();


	bDraw = false;
	pPlayerUI->SetKillNum(0);

	//Sound Loading
	InitSoundResource();

	return S_OK;
}

void cScene_main::Scene_Release()
{
	m_pBossVideo->Release();
	SAFE_DELETE(m_pBossVideo);

	//������Ʈ ����
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

	pPlayerUI->Update();
	pPlayerUI->SetHp(pPlayer->m_fHP);
	pPlayerUI->SetHpMax(pPlayer->m_fMaxHP);

	//DeathCount = ENEMYMAX_1;
	DeathCount = 0;
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
			LOG_MGR->AddLog("������ ��Ÿ����");
		}
	}

	this->pMainCamera->UpdateFrustum();
	this->cullObjects.clear();
	//�������� �ȿ� �ִ�?
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
	

	//20161206���� getMap���� �ٲٱ�
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

	//���� ����
	MonsterAttack(timDelta);

	//��ų����Ʈ
	pPlayerSkillEff->Update(timDelta);
	//effTest->Update(timDelta);
	//
	//D3DXVECTOR3 pTemp = pPlayer->GetWorldPosition();
	//if (KEY_MGR->IsOnceDown(VK_SPACE))
	//{
	//	pTemp.y += 0.1;
	//	effTest->PlayEffect(BOSS_ATTACK_GROUND, pTemp);
	//}
	//else {
	//	effTest->PlayEffect(BOSS_ATTACK_GROUND_STOP, pTemp);
	//}

	//pEnemySkillEff->PlayEffect(ENEMY_ATTACK_01, pPlayer->GetWorldPosition(), 0);

	//this->pMainCamera->SetWorldPosition(D3DXVECTOR3(pPlayer->m_pRootTrans->GetWorldPosition().x + 5, pPlayer->m_pRootTrans->GetWorldPosition().y + 5, pPlayer->m_pRootTrans->GetWorldPosition().z + 1));
	this->pMainCamera->DefaultControl4(timDelta, pPlayer->m_pRootTrans); //��
	
	//this->pMainCamera->ShakeUpdate(timDelta);
	//this->pMainCamera->DefaultControl(timDelta); //��

	if (pPlayerUI->getKillNum() == 0)
	{
		if (!m_bBossVideoPlay)
		{	
			m_bBossVideoPlay = true;
			g_bRender = false;
			m_pBossVideo->Play("./Video/Boss.wmv");
			pPlayerUI->SetBossMeet(true);
			//m_bBossVideoPlay = false;
		}
		pPlayerUI->SetKillNum(-1);
	}

	if (!m_pBossVideo->GetIsPlay())
	{
		//LOG_MGR->AddLog("��");
		if (!m_bBossVideoEnd)
		{
			g_bRender = true;
			m_pBossVideo->Stop();
			pPlayerUI->SetBossMeet(true);
			pBoss->SetUIon(true);
			m_bBossVideoEnd = true;
		}
	}

	if (KEY_MGR->IsOnceDown('1'))
	{
		g_bRender = false;
		m_pBossVideo->Play("./Video/Boss.wmv");
	}
	if (KEY_MGR->IsOnceDown('2'))
	{
		g_bRender = true;
		m_pBossVideo->Stop();
		pPlayerUI->SetBossMeet(true);
		pBoss->SetUIon(true);
		m_bBossVideoEnd = true;
	}

	//if (KEY_MGR->IsStayDown('0'))
	if(pBoss->bS)
	{
		//this->pMainCamera->ShakePos(0.00000000001, 0);
		this->pMainCamera->ShakeRot(0.01, -1);
		//this->pMainCamera->LookDirection(pPlayer->GetBaseObject()[0]->pTransform->GetWorldPosition());
		this->pMainCamera->ShakeUpdate(timDelta);
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
	//if (pMap) //20161206 �����ּ�
	//	pMap->Render();

	if (pEntireMap)
		pEntireMap->Render();

	//Player
	if (pPlayer)
		pPlayer->Render(this->pSceneBaseDirectionLight);

	//PlayerUI //20161207 �����߰�
	if (pPlayerUI)
		pPlayerUI->Render();

	//�������������� //20161207 �����߰�
	//if (pProgressBar_Boss)
	//	pProgressBar_Boss->Render();

	//�ø��� ������Ʈ��
	MonsterRender();

	//this->cullObjects.clear();
	//for (int i = 0; i < this->renderObjects.size(); i++) {
	//	//�������� �ȿ� �ִ�?
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

	//�������� �׷�����
	//this->pDirectionLightCamera->Frustum.RenderGizmo();
	this->pSceneBaseDirectionLight->pTransform->RenderGimozo();

	//-----------------------------
	//Effect Rendering
	//-----------------------------

	if (pPlayerSkillEff)
		pPlayerSkillEff->Render();

	//if (effTest)
	//	effTest->Render();

	

	//this->pTrailRender->Render();
	//LOG_MGR->AddLog("%d", DeathCount);
	//LOG_MGR->AddLog("%d", renderObjects.size());
	//LOG_MGR->AddLog("%.2f", CalcLength(pPlayer->GetBaseObject()[0]->pTransform->GetWorldPosition(), vecGenPoint[3].p));
	//LOG_MGR->AddLog("%.2f", CalcLength(pPlayer->GetBaseObject()[0]->pTransform->GetWorldPosition(), D3DXVECTOR3(-128.f, -15.0f, 80.0f)));
	//LOG_MGR->AddLog("X : %.2f, Z : %.2f", pPlayer->GetBaseObject()[0]->pTransform->GetWorldPosition().x, pPlayer->GetBaseObject()[0]->pTransform->GetWorldPosition().z);
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
						//LOG_MGR->AddLog("%d���� ���ȴ�", i);
					}
						
					//0.0f, 0.75f, -0.025f
					D3DXVECTOR3 vCenter;
					float		ftemp;

					pPlayer->GetBaseObject()[4]->BoundBox.GetWorldCenterRadius(pPlayer->GetBaseObject()[4]->pTransform, &vCenter, &ftemp);
					pPlayerSkillEff->PlayEffect(PLAYER_ATTACL_02, vCenter);
				}

				if (PHYSICS_MGR->IsOverlap(pPlayer->GetBaseObject()[5], pEnemy1[i]->GetBaseObject()[0]))
				{
					pEnemy1[i]->SetState(MonState::Stun);
					if (m_pTickPlayer[i]->tickStart())
					{
						pEnemy1[i]->SetHP(pEnemy1[i]->GetHP() - 1);
						//LOG_MGR->AddLog("%d���� ���ȴ�", i);
					}
						
					//0.0f, 0.75f, -0.025f
					D3DXVECTOR3 vCenter;
					float		ftemp;

					pPlayer->GetBaseObject()[5]->BoundBox.GetWorldCenterRadius(pPlayer->GetBaseObject()[5]->pTransform, &vCenter, &ftemp);
					pPlayerSkillEff->PlayEffect(PLAYER_ATTACL_02, vCenter);
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
						//LOG_MGR->AddLog("%d���� ���ȴ�", i + 25);
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
						//LOG_MGR->AddLog("%d���� ���ȴ�", i + 25);
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
						//LOG_MGR->AddLog("%d���� ���ȴ�", i + 50);
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
						//LOG_MGR->AddLog("%d���� ���ȴ�", i + 50);
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
						//LOG_MGR->AddLog("%d���� ���ȴ�", i + 75);
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
						//LOG_MGR->AddLog("%d���� ���ȴ�", i + 75);
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
					//LOG_MGR->AddLog("%d���� ���ȴ�", i + 75);
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
					//LOG_MGR->AddLog("%d���� ���ȴ�", i + 75);
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
	//����ġ
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
	//����
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

			//LOG_MGR->AddLog("�������� �¾Ҵ�!");
		}
	}
}

void cScene_main::MonsterRender()
{
	//0������Ʈ
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
	//1������Ʈ
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
	//2������Ʈ
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
	//3������Ʈ
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
	//SOUND_MGR->addSound("name", "mp3", true, true);



}