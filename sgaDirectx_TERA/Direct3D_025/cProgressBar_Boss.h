#pragma once
//test주석 
#include "cProgressBar_Monster.h"

class cProgressBar_Boss : public cProgressBar_Monster
{
private:
	//프로그레스바 뒤 레드효과 
	LPD3DXSPRITE			m_pBarRed_Sprite;
	LPDIRECT3DTEXTURE9		m_pBarRed_Texture;
	D3DXIMAGE_INFO			m_BarRed_Sprite_Info;
	RECT					m_rcBarRed;

	//프로그레스바 뒤 화이트효과 
	LPD3DXSPRITE			m_pBarWhite_Sprite;
	LPDIRECT3DTEXTURE9		m_pBarWhite_Texture;
	D3DXIMAGE_INFO			m_BarWhite_Sprite_Info;
	RECT					m_rcBarWhite;

	//보스 다 잡고나면 엔딩로고 띄우기 
	LPD3DXSPRITE			m_pEndLogo_Sprite;
	LPDIRECT3DTEXTURE9		m_pEndLogo_Texture;
	D3DXIMAGE_INFO			m_EndLogo_Sprite_Info;
	RECT					m_rcEndLogo;

	//카메라도 변경 

public:
	cProgressBar_Boss();
	~cProgressBar_Boss();

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

