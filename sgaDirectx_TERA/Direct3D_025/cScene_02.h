#pragma once
#include "cscene.h"

class cBaseObject;
class cCamera;
class cTerrain;
class cSkinnedAnimation;

class cScene_02 : public cScene
{
private:
	cBaseObject*						object;
	
	//���
	LPD3DXSPRITE			m_pBG_Sprite;
	LPDIRECT3DTEXTURE9		m_pBG_Texture;
	D3DXIMAGE_INFO			m_BG_Sprite_Info;

	//�ε��� 
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
	cScene_02(void);
	~cScene_02(void);


	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update( float timDelta );

	virtual void Scene_Render1();

	virtual void Scene_RenderSprite();


};

