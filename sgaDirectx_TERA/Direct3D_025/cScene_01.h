#pragma once
#include "cscene.h"

class cBaseObject;
class cCamera;
class cTerrain;
class cSkinnedAnimation;
class cQuad;

#define OBJECT_NUM 30

class cTrailRender;


class cScene_01 : public cScene
{
private:
	std::vector<cBaseObject*>			renderObjects;			//���� ��ġ�� ���� ������Ʈ �迭
	std::vector<cBaseObject*>			cullObjects;			//�ø��� ������Ʈ
	std::vector<cLight*>				lights;					//������..

	cTerrain*		m_pTerrain;
	cTerrain*		m_pTerrainShadow;

	cQuad*			pQuad;
	cTransform*		pQuadTrans;
	
	cTrailRender*						pTrailRender;

public:
	cScene_01(void);
	~cScene_01(void);


	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update( float timDelta );

	virtual void Scene_Render1();

	virtual void Scene_RenderSprite();

	virtual void Scene_Render_AfterPostEffect( LPDIRECT3DTEXTURE9 pScreen );


};

