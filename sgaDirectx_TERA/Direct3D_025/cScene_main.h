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


class cTickFunc;
class cVideo;

#define ENEMYMAX	25
#define ENEMYMAX_1	100
#define TICKMAX		1

class cScene_main : public cScene
{
private:

	cVideo*								m_pBossVideo;
	bool								m_bBossVideoPlay;

	std::vector<cBaseObject*>			renderObjects;			//���� ��ġ�� ���� ������Ʈ �迭
	std::vector<cBaseObject*>			cullObjects;			//�ø��� ������Ʈ
	std::vector<cLight*>				lights;					//������..
	std::vector<ST_GenPoint>			vecGenPoint;

	cMeshMap*							pMap;
	cCharacter*							pPlayer;				//ĳ����
	cEnemy*								pEnemy1[ENEMYMAX];		//���� �� 1��
	cEnemy*								pEnemy2[ENEMYMAX];		//���� �� 2��
	cEnemy*								pEnemy3[ENEMYMAX];		//���� �� 3��
	cEnemy*								pEnemy4[ENEMYMAX];		//���� �� 4��
	cBoss*								pBoss;					//����

	cMap*								pEntireMap;

	cPlayerUI*							pPlayerUI;
	cProgressBar_Boss*					pProgressBar_Boss;

	cPlayerSkillEffect*					pPlayerSkillEff;

	cTickFunc*							m_pTick[ENEMYMAX_1];
	cTickFunc*							m_pTickPlayer[ENEMYMAX_1 + 1];
	cTickFunc*							m_pTickBoss;

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
	
	//�÷��̾�
	void PlayerAttack(float timDelta);
	//��
	void GenSetup();
	//����
	void MonsterSetup();
	void MonsterAttack(float timDelta);
	void MonsterRender();
};

