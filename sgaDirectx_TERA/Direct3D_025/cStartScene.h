#pragma once
class cStartScene
{
private:

	LPD3DXSPRITE			m_pBG_Sprite;
	LPDIRECT3DTEXTURE9		m_pBG_Texture;
	D3DXIMAGE_INFO			m_BG_Sprite_Info; 


public:
	cStartScene();
	~cStartScene();

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

