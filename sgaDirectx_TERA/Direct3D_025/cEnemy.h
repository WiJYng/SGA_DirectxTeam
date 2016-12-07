#pragma once

class cMeshMap;

class cEnemy
{
private:
	enum MonState
	{
		Wait,
		Run,
		Attack
	};

	std::vector<cBaseObject*>			renderObjects;			//������Ʈ �迭

	MonState							m_State;
	bool								bWait;
	bool								bRun;
	bool								bAtt;

public:
	cEnemy();
	~cEnemy();

	void Setup(string PathMonster, D3DXVECTOR3* Pos = NULL);
	void Setup(string PathMonster, D3DXMATRIXA16* mat, D3DXVECTOR3* Pos);

	void Update(D3DXVECTOR3 worldPos);
	void Update(float timDelta, cMeshMap* _Map, D3DXVECTOR3* _PlayerPos);
	void Render();

	float CalcLen(D3DXVECTOR3* _PlayerPos, D3DXVECTOR3* _ThisPos);

	//Getter/Setter
	void SetWorldPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetWorldPosition();

};

