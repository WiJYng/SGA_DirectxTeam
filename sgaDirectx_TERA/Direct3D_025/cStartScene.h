#pragma once
class cStartScene : public cScene
{
private:

	LPD3DXSPRITE			m_pBG_Sprite;
	LPDIRECT3DTEXTURE9		m_pBG_Texture;
	D3DXIMAGE_INFO			m_BG_Sprite_Info; 


public:
	cStartScene();
	~cStartScene();

	virtual HRESULT Scene_Init();
	virtual void Scene_Release();
	virtual void Scene_Update(float timDelta);
	virtual void Scene_Render1();
	virtual void Scene_RenderSprite();

};

