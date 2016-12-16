#pragma once
#include "cEnemyEffect.h"

class cMeshMap;
class cProgressBar_sMonster;
class cEnemyEffect;

class cEnemy
{
private:
	
	cProgressBar_sMonster*				ProgressBar;
	std::vector<cBaseObject*>			renderObjects;			//오브젝트 배열

	MonState							m_State;
	bool								bWait;
	bool								bRun;
	bool								bAtt;
	bool								bDeath;
	bool								bStun;
	float								fRanderTime;
	float								PrevAngle;

	cTransform*							pMonTrans;
	

	float								m_fHP;
	float								m_fMAXHP;

public:
	cTransform*							pWeaponTrans;
	cEnemyEffect*						pEnemySkillEff;

	cBoundBox*							m_pBB;

	cEnemy();
	~cEnemy();

	void Setup(string PathMonster, D3DXVECTOR3* Pos = NULL);
	void Setup(string PathMonster, D3DXMATRIXA16* mat, D3DXVECTOR3* Pos);

	void Release();

	void Update(D3DXVECTOR3 worldPos);
	void Update(float timDelta, cMeshMap* _Map, D3DXVECTOR3* _PlayerPos);
	void Render();

	float CalcLen(D3DXVECTOR3* _PlayerPos, D3DXVECTOR3* _ThisPos);
	float CalcAngle(D3DXVECTOR3* _PlayerPos, D3DXVECTOR3* _ThisPos);

	//Getter/Setter
	void SetWorldPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetWorldPosition();

	void SetState(MonState _State)
	{
		m_State = _State;
	}
	MonState GetState()
	{
		return m_State;
	}

	std::vector<cBaseObject*> GetBaseObject()
	{
		return renderObjects;
	}

	float GetHP()
	{
		return m_fHP;
	}
	void SetHP(float _fHP)
	{
		m_fHP = _fHP;
	}

};

#define PI		3.141592654f
#define PI2		(PI * 2)