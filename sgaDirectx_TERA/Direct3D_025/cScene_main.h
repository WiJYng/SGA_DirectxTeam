#pragma once

class cBaseObject;
class cCamera;
class cTrailRender;
class cCharacter;
class cEnemy;
class cMeshMap;
class cTerrain;
class cMap;
class cProgressBar_Boss;

class cPlayerUI;
class cPlayerSkillEffect;

class cScene_main : public cScene
{
private:
	std::vector<cBaseObject*>			renderObjects;			//씬에 배치된 랜더 오브젝트 배열
	std::vector<cBaseObject*>			cullObjects;			//컬링된 오브젝트
	std::vector<cLight*>				lights;					//라이팅..

	cMeshMap*							pMap;
	cCharacter*							pPlayer;
	cEnemy*								pEnemy[36];

	cTrailRender*						pTrailRender;
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

