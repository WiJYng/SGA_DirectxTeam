#pragma once

class cMeshMap;
class cTickFunc;
class cProgressBar_Boss;
class cBossEffect;
class cCamera;

class cBoss
{
private:
	cProgressBar_Boss*					BossUI;
	bool								bUIon;

	std::vector<cBaseObject*>			renderObjects;			//오브젝트 배열

	MonState							m_State;
	bool								bWait;
	bool								bRun;
	bool								bAtt;
	bool								bDeath;
	bool								bStun;
	bool								bUWait;
	bool								bEffectOn;
	float								PrevAngle;

	cTransform*							pMonTrans;
	

	float								m_fHP;
	float								m_fMAXHP;

	int									m_nCount;

	cTickFunc*							m_pTick[3];
	D3DXVECTOR3 Targetdir;

public:
	cTransform*							pWeaponTrans;
	cBossEffect*						pBossEffect;
	bool								bS;
	
	cBoss();
	~cBoss();

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

	void AttackFuntion(float timDelta, cMeshMap* _Map);

	void SetUIon(bool value){ bUIon = value; }
	bool GetUIon(){ return bUIon; }
};

