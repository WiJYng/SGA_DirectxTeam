#pragma once

class cBaseObject;
class cCamera;
class cCharacter;
class cEnemy;
class cBoss;
class cMeshMap;
class cTerrain;
class cMap;
class cProgressBar_Boss;

class cPlayerUI;
class cPlayerSkillEffect;
class cLocationEffect;

class cTickFunc;
class cVideo;
class cAudioFile;

#define ENEMYMAX	25
#define ENEMYMAX_1	100
#define TICKMAX		1

class cScene_main : public cScene
{
private:

	cVideo*								m_pBossVideo;
	bool								m_bBossVideoPlay;
	bool								m_bBossVideoEnd;

	std::vector<cBaseObject*>			renderObjects;			//씬에 배치된 랜더 오브젝트 배열
	std::vector<cBaseObject*>			cullObjects;			//컬링된 오브젝트
	std::vector<cLight*>				lights;					//라이팅..
	std::vector<ST_GenPoint>			vecGenPoint;

	cMeshMap*							pMap;
	cCharacter*							pPlayer;				//캐릭터
	cEnemy*								pEnemy1[ENEMYMAX];		//몬스터 젠 1번
	cEnemy*								pEnemy2[ENEMYMAX];		//몬스터 젠 2번
	cEnemy*								pEnemy3[ENEMYMAX];		//몬스터 젠 3번
	cEnemy*								pEnemy4[ENEMYMAX];		//몬스터 젠 4번
	cBoss*								pBoss;					//보스

	cMap*								pEntireMap;

	cPlayerUI*							pPlayerUI;
	cProgressBar_Boss*					pProgressBar_Boss;

	cPlayerSkillEffect*					pPlayerSkillEff;

	cTickFunc*							m_pTick[ENEMYMAX_1];
	cTickFunc*							m_pTickPlayer[ENEMYMAX_1 + 1];
	cTickFunc*							m_pTickBoss;

	int									DeathCount;
	bool								bDraw;

	cLocationEffect*					pLocationEffect;

	cAudioFile*							m_pAudioFile;
	//bool								soundStartTest;

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
	void MonsterRender();

private:
	void InitSoundResource();
};

