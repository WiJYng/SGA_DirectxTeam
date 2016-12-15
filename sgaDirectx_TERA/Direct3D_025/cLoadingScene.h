#pragma once

class cLoadingScene : public cScene
{
private:
	
	//배경
	LPD3DXSPRITE			m_pBG_Sprite;
	LPDIRECT3DTEXTURE9		m_pBG_Texture;
	D3DXIMAGE_INFO			m_BG_Sprite_Info;
	
	//로딩바 
	LPD3DXSPRITE			m_pLBfront_sp; //loadingBar front
	LPD3DXSPRITE			m_pLBback_sp;	//loadingBar back

	LPDIRECT3DTEXTURE9		m_pLBfront_texture;
	LPDIRECT3DTEXTURE9		m_pLBback_texture;

	D3DXIMAGE_INFO			m_LBfront_ImgInfo;
	D3DXIMAGE_INFO			m_LBback_ImgInfo;

	RECT					m_rcLB_front;
	RECT					m_rcLB_frontMove;
	RECT					m_rcLB_back;
	RECT					m_rcLB_backMove;


public:
	
	cLoadingScene();
	~cLoadingScene();

	virtual HRESULT Scene_Init();
	virtual void Scene_Release();
	virtual void Scene_Update(float timDelta);
	virtual void Scene_Render1();
	virtual void Scene_RenderSprite();

	static void SetZealots(LPVOID pParam);
	static void SetLoadingGauge(LPVOID pParam);

};

