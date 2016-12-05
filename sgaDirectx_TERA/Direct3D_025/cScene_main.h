#pragma once

class cBaseObject;
class cCamera;
class cTrailRender;
class cCharacter;
class cMeshMap;


class cScene_main : public cScene
{
private:
	std::vector<cBaseObject*>			renderObjects;			//���� ��ġ�� ���� ������Ʈ �迭
	std::vector<cBaseObject*>			cullObjects;			//�ø��� ������Ʈ
	std::vector<cLight*>				lights;					//������..

	cMeshMap*							pMap;
	cCharacter*							pPlayer;

	cTrailRender*						pTrailRender;

public:
	cScene_main();
	~cScene_main();

	virtual HRESULT Scene_Init();
	virtual void Scene_Release();
	virtual void Scene_Update(float timDelta);
	virtual void Scene_Render1();
	virtual void Scene_RenderSprite();
};

