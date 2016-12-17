#include "stdafx.h"
#include "cEnemy.h"
#include "cMeshMap.h"
#include "cTransform.h"
#include "cSkinnedAnimation.h"
#include "cProgressBar_sMonster.h"

#include "cEnemyEffect.h"


cEnemy::cEnemy()
{
}
cEnemy::~cEnemy()
{
	SAFE_DELETE(pMonTrans);
	SAFE_DELETE(pWeaponTrans);

	SAFE_DELETE(pEnemySkillEff);
}

void cEnemy::Setup(string PathMonster, D3DXVECTOR3* Pos)
{
	//UI추가
	ProgressBar = new cProgressBar_sMonster;
	ProgressBar->Setup();

	//바운드박스 충돌처리
	//cPhysicManager에 IsOverlap함수를 이용하여 충돌을 확인한다
	//cTickFunc을 이용하여 충돌이 여러번 들어가지 않도록 설정할 수 있다.

	m_State = Wait;
	bWait = true;
	bRun = false;
	bAtt = false;
	bDeath = false;
	bStun = false;
	PrevAngle = 0.0f;
	fRanderTime = 0.0f;

	m_fHP = m_fMAXHP = 3.0f;

	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);

	//if (Pos)
	//{
	//	D3DXMatrixTranslation(&mat, Pos->x, Pos->y, Pos->z);
	//}

	Setup(PathMonster, &mat, Pos);

	//effect
	pEnemySkillEff = new cEnemyEffect;
	pEnemySkillEff->Setup();

}

void cEnemy::Setup(string PathMonster, D3DXMATRIXA16 * mat, D3DXVECTOR3* Pos)
{
	//기본 1개의 파츠로 이루어져있다
	this->renderObjects.reserve(1);

	cXMesh_Skinned* pMonster = RESOURCE_SKINNEDXMESH->GetResource(PathMonster, mat);

	pMonTrans = new cTransform();
	pWeaponTrans = new cTransform();

	m_pBB = new cBoundBox();
	m_pBB->Init(D3DXVECTOR3(-0.1, 0.7, -0.1), D3DXVECTOR3(0.1, 1.0, 0.1));

	cBaseObject* pMonObj = new cBaseObject();
	pMonObj->SetMesh(pMonster);
	pMonObj->SetActive(true);
	pMonObj->pTransform->SetWorldPosition(*Pos);
	pMonObj->pSkinned->AddBoneTransform("Dummy_root", pMonTrans);
	pMonObj->pSkinned->AddBoneTransform("Bip01-Prop1", pWeaponTrans);

	renderObjects.push_back(pMonObj);

	renderObjects[0]->pSkinned->Play("Wait", 0.0f);
	renderObjects[0]->BoundBox.Init(D3DXVECTOR3(-0.4, 0, -0.5), D3DXVECTOR3(0.4, 1, 0.25));
	renderObjects[0]->BoundBox01.Init(D3DXVECTOR3(-0.1, 0, -0.1), D3DXVECTOR3(0.1, 1.0, 0.1));
}

void cEnemy::Release()
{
	SAFE_DELETE(pMonTrans);
	SAFE_DELETE(pWeaponTrans);
	
}

void cEnemy::Update(float timDelta, cMeshMap * _Map, D3DXVECTOR3* _PlayerPos)
{
	//ProgressBar->SetX(renderObjects[0]->pTransform->GetWorldPosition().x);
	//ProgressBar->SetY(renderObjects[0]->pTransform->GetWorldPosition().y);
	D3DXVECTOR3 temp = renderObjects[0]->pTransform->GetWorldPosition();
	temp.y += 1.25;

	D3DXMATRIXA16 viewMat, projectMat,worldMat;
	D3DVIEWPORT9  viewPort;
	D3DXMatrixIdentity(&worldMat);

	Device->GetTransform(D3DTS_VIEW, &viewMat);
	Device->GetTransform(D3DTS_PROJECTION, &projectMat);
	Device->GetViewport(&viewPort);
	D3DXVec3Project(&temp, &temp, &viewPort, &projectMat, &viewMat, &worldMat);

	//D3DXVec3TransformCoord(&temp, &temp, &viewMat);
	//D3DXVec3TransformCoord(&temp, &temp, &projectMat);

	ProgressBar->SetX(temp.x);
	ProgressBar->SetY(temp.y);
	ProgressBar->SetHp(m_fHP);
	ProgressBar->SetHpMax(m_fMAXHP);

	renderObjects[0]->Update(timDelta);

	//레이 세팅
	D3DXVECTOR3 currentPos = renderObjects[0]->pTransform->GetWorldPosition();

	//float len = CalcLen(_PlayerPos, &renderObjects[0]->pTransform->GetWorldPosition());
	D3DXVECTOR3 dirToTarget = *_PlayerPos - renderObjects[0]->pTransform->GetWorldPosition();
	float dist = D3DXVec3Length(&dirToTarget);
	dirToTarget.y = 0;

	//float angle = CalcAngle(_PlayerPos, &renderObjects[0]->pTransform->GetWorldPosition());
	
	if (m_State != Stun && m_State != Death && m_State != DeathWait)
	{
		//방향을 구한다.
		D3DXVec3Normalize(&dirToTarget, &dirToTarget);
		dirToTarget.y = 0;
		D3DXVECTOR3 forward = renderObjects[0]->pTransform->GetForward();
		forward.y = 0;
		D3DXVec3Normalize(&forward, &forward);

		float angle = acosf(D3DXVec3Dot(&dirToTarget, &forward));
		if (angle >= 90 * ONE_RAD)
		{
			renderObjects[0]->pTransform->RotateSelf(0, 5 * ONE_RAD, 0);

			//LOG_MGR->AddLog("%.2f, %d", angle * 180 / 3.14, m_nIndex);
		}
	
	

	D3DXVECTOR3 lerp = renderObjects[0]->pTransform->GetForward();
	D3DXVec3Lerp(&lerp, &lerp, &dirToTarget, 0.2);
	renderObjects[0]->pTransform->LookDirection(lerp, renderObjects[0]->pTransform->GetUp());
	}

	//이동량
	float deltaMove = 5.0f * TIME_MGR->GetFrameDeltaSec();
	float t = Clamp01(deltaMove / dist);

	//D3DXVECTOR3 pos;
	//레이랑 터레인 체크하자
	//if (pTerrain->IsIntersectRay(&pos, &ray))
	{
		//renderObjects[0]->pTransform->SetWorldPosition(pos);
	//	currentPos = renderObjects[0]->pTransform->GetWorldPosition();
	}

	// 레이랑 케릭터 거리가 멀어지면 레이가 더이상 넘어가지 못하게 만든다.
	//float rayCheckDis = D3DXVec3Length(&(ray.origin - currentPos));
	//if (rayCheckDis > t + 0.01f) // 상수 값은 속력 보다 조금 높은 값.
	//{
	//	ray.origin = currentPos;
	//	ray.origin.y += 3;
	//}


	if (m_State != Death && !bDeath && m_State != Stun)
	{
		if (dist > 15.0f)
		{
			if (m_State != Wait && !bWait)
			{
				renderObjects[0]->pSkinned->Play("Wait", 0.0f);
				m_State = Wait;
				bWait = true;
				bRun = bAtt = false;
			}
		}
		else if (dist <= 15.0f && dist > 1.5f)
		{
			if (m_State != Run && !bRun)
			{
				renderObjects[0]->pSkinned->Play("Run", 0.0f);
				m_State = Run;
				bRun = true;
				bWait = bAtt = false;
			}
			renderObjects[0]->pTransform->MovePositionWorld(renderObjects[0]->pTransform->GetForward()*timDelta);
			
		}
		else if (dist <= 1.5f && dist > 0.0f)
		{
			if (m_State != Attack && !bAtt)
			{
				renderObjects[0]->pSkinned->Play("Attack", 0.0f);
				m_State = Attack;
				bAtt = true;
				bWait = bRun = false;
			}

			if (m_State == Attack && renderObjects[0]->pSkinned->GetFactor() >= 0.5f)
			{
				D3DXVECTOR3 weaponPos;
				float		fTemp;

				m_pBB->GetWorldCenterRadius(pWeaponTrans, &weaponPos, &fTemp);
				weaponPos.y += 0.03;
				pEnemySkillEff->PlayEffect(ENEMY_ATTACK_01, weaponPos);
			}

			if (renderObjects[0]->pSkinned->GetFactor() >= 0.15 && renderObjects[0]->pSkinned->GetFactor() < 0.17)
			{
				//몬스터 공격 사운드 플레이
				SOUND_MGR->play("M_ATT_01", 0.2);
			}
		}
	}
	else if (m_State == Death && !bDeath)
	{
		if (renderObjects[0]->pSkinned->GetFactor() >= 0.95f)
		{
			if (m_State != DeathWait)
			{
				D3DXVECTOR3 vTemp = D3DXVECTOR3(pMonTrans->GetWorldPosition().x, 0.0f, pMonTrans->GetWorldPosition().z);
				renderObjects[0]->pTransform->SetWorldPosition(vTemp);

				renderObjects[0]->pSkinned->Play("DeathWait", 0.0f);
				m_State = DeathWait;
				bDeath = true;
				bWait = bRun = bAtt = false;
			}
		}
	}

	if (m_State == Stun)
	{
		if (!bStun)
		{
			renderObjects[0]->pSkinned->Play("Stun", 0.0f);
			bStun = true;
			bWait = bRun = bAtt = false;
			//LOG_MGR->AddLog("충돌했니?");
		}
		if (renderObjects[0]->pSkinned->GetFactor() >= 0.95f)
		{
			m_State = Mempty;
			bWait = bRun = bAtt = bStun = false;
		}
		
	}
	

	if (m_fHP <= 0.0f && bStun && m_State == Stun)
	{
		if (m_State != Death)
		{
			renderObjects[0]->pSkinned->PlayOneShotAfterHold("Death", 0.0f);
			m_State = Death;
			bStun = true;
			bWait = bRun = bAtt = false;
			m_fHP = 0;
			//몬스터 죽는 사운드
			SOUND_MGR->play("M_DEATH", 0.2);
		}
	}

	
	if (_Map)
	{
		if (m_State != Death)
		{
			float y = _Map->GetHeight(renderObjects[0]->pTransform->GetWorldPosition().x, renderObjects[0]->pTransform->GetWorldPosition().z);
			D3DXVECTOR3 vTemp = D3DXVECTOR3(renderObjects[0]->pTransform->GetWorldPosition().x, y, renderObjects[0]->pTransform->GetWorldPosition().z);
			renderObjects[0]->pTransform->SetWorldPosition(vTemp);
		}
		else
		{
			float y = _Map->GetHeight(pMonTrans->GetWorldPosition().x, pMonTrans->GetWorldPosition().z);
			D3DXVECTOR3 vTemp = D3DXVECTOR3(renderObjects[0]->pTransform->GetWorldPosition().x, y, renderObjects[0]->pTransform->GetWorldPosition().z);
			renderObjects[0]->pTransform->SetWorldPosition(vTemp);
		}
	}
	

	pEnemySkillEff->Update(timDelta);


	if (fRanderTime < 11.0f && bDeath)
	{
		fRanderTime += (0.1);
		//LOG_MGR->AddLog("%.2f", fRanderTime);
	}


	//PrevAngle = angle;

	//char str[1024];
	//sprintf_s(str, "%.2f", dist);
	//sprintf_s(str, "%.2f", angle);
	//LOG_MGR->AddLog(str);
}

void cEnemy::Render()
{
	if (!bDeath)
	{
		ProgressBar->Render();
		//LOG_MGR->AddLog("쥬금");
	}
	if (fRanderTime <= 10.0f)
	{
		renderObjects[0]->Render();
		
	}
	if(g_bBox)renderObjects[0]->BoundBox.RenderGizmo(pMonTrans);
	if(g_bBox)renderObjects[0]->BoundBox01.RenderGizmo(pWeaponTrans);
	//renderObjects[0]->pTransform->RenderGimozo();
	//m_pBB->RenderGizmo(pWeaponTrans);

	

	if (pEnemySkillEff)
		pEnemySkillEff->Render();
}

float cEnemy::CalcLen(D3DXVECTOR3 * _PlayerPos, D3DXVECTOR3 * _ThisPos)
{
	float x = abs(_PlayerPos->x - _ThisPos->x);
	float y = abs(_PlayerPos->y - _ThisPos->y);
	float z = abs(_PlayerPos->z - _ThisPos->z);

	float len = (x * x) + (y * y) + (z * z);

	return len;
}

float cEnemy::CalcAngle(D3DXVECTOR3 * _PlayerPos, D3DXVECTOR3 * _ThisPos)
{
	float x = _PlayerPos->x - _ThisPos->x;
	float z = _PlayerPos->z - _ThisPos->z;

	float distance = sqrtf(x * x + z * z);
	float angle = acosf(x / distance);

	//if (z > 0) angle = PI2 - angle;

	return angle;
}
