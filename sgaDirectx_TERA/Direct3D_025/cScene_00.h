#pragma once
#include "cscene.h"

class cBaseObject;
class cCamera;
class cTrailRender;

class cScene_00 : public cScene
{
private:
	std::vector<cBaseObject*>			renderObjects;			//���� ��ġ�� ���� ������Ʈ �迭
	std::vector<cBaseObject*>			cullObjects;			//�ø��� ������Ʈ
	

	cTrailRender*						pTrailRender;






public:
	cScene_00(void);
	~cScene_00(void);


	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update( float timDelta );

	virtual void Scene_Render1();

	virtual void Scene_RenderSprite();


};

