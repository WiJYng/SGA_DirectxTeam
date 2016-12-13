#pragma once

class cBaseObject;
class cCamera;
class cTrailRender;
class cCharacter;
class cEnemy;
class cBoss;
class cMeshMap;
class cTerrain;
class cMap;
class cProgressBar_Boss;

class cPlayerUI;
class cPlayerSkillEffect;

class cTickFunc;

#define ENEMYMAX	25
#define ENEMYMAX_1	100
#define TICKMAX		1

class cScene_main : public cScene
{
private:
	std::vector<cBaseObject*>			renderObjects;			//씬에 배치된 랜더 오브젝트 배열
	std::vector<cBaseObject*>			cullObjects;			//컬링된 오브젝트
	std::vector<cLight*>				lights;					//라이팅..
	std::vector<ST_GenPoint>			vecGenPoint;

	cMeshMap*							pMap;
	cCharacter*							pPlayer;
	cEnemy*								pEnemy1[ENEMYMAX];
	cEnemy*								pEnemy2[ENEMYMAX];
	cEnemy*								pEnemy3[ENEMYMAX];
	cEnemy*								pEnemy4[ENEMYMAX];
	cBoss*								pBoss;

	vector<cTrailRender*>				pVecTrailRender;
	cMap*								pEntireMap;

	cPlayerUI*							pPlayerUI;
	cProgressBar_Boss*					pProgressBar_Boss;

	cPlayerSkillEffect*					pPlayerSkillEff;

	cTickFunc*							m_pTick[ENEMYMAX_1];
	cTickFunc*							m_pTickPlayer[ENEMYMAX_1 + 1];

	int									DeathCount;
	bool								bDraw;

public:
	cScene_main();
	~cScene_main();

	//void Update(float timeDelta) override;

	virtual HRESULT Scene_Init();
	virtual void Scene_Release();
	virtual void Scene_Update(float timDelta);
	virtual void Scene_Render1();
	virtual void Scene_RenderSprite();

	virtual float CalcLength(D3DXVECTOR3 P1, D3DXVECTOR3 P2);
	
	//플레이어
	void PlayerAttack(float timDelta);
	//젠
	void GenSetup();
	//몬스터
	void MonsterSetup();
	void MonsterAttack(float timDelta);
};

