#pragma once

class cMeshMap;

class cEnemy
{
private:
	enum MonState
	{
		Wait,
		Run,
		Attack,
		Stun,
		Death,
		DeathWait
	};

	std::vector<cBaseObject*>			renderObjects;			//오브젝트 배열

	MonState							m_State;
	bool								bWait;
	bool								bRun;
	bool								bAtt;
	bool								bDeath;
	float								PrevAngle;

	cTransform*							pMonTrans;
	cTransform*							pWeaponTrans;

public:
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

};

#define PI		3.141592654f
#define PI2		(PI * 2)