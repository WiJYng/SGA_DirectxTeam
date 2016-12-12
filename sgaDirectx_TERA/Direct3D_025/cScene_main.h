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

class cScene_main : public cScene
{
private:
	std::vector<cBaseObject*>			renderObjects;			//���� ��ġ�� ���� ������Ʈ �迭
	std::vector<cBaseObject*>			cullObjects;			//�ø��� ������Ʈ
	std::vector<cLight*>				lights;					//������..

	cMeshMap*							pMap;
	cCharacter*							pPlayer;
	cEnemy*								pEnemy[36];
	cBoss*								pBoss;

	vector<cTrailRender*>				pVecTrailRender;
	cMap*								pEntireMap;

	cPlayerUI*							pPlayerUI;
	cProgressBar_Boss*					pProgressBar_Boss;
	
	cPlayerSkillEffect*					pPlayerSkillEff;




public:
	cScene_main();
	~cScene_main();

	//void Update(float timeDelta) override;

	virtual HRESULT Scene_Init();
	virtual void Scene_Release();
	virtual void Scene_Update(float timDelta);
	virtual void Scene_Render1();
	virtual void Scene_RenderSprite();
};

