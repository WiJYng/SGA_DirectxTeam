#pragma once
//test�ּ� 
#include "cProgressBar_Monster.h"

class cProgressBar_Boss : public cProgressBar_Monster
{
private:
	//���α׷����� �� ����ȿ�� 
	LPD3DXSPRITE			m_pBarRed_Sprite;
	LPDIRECT3DTEXTURE9		m_pBarRed_Texture;
	D3DXIMAGE_INFO			m_BarRed_Sprite_Info;
	RECT					m_rcBarRed;

	//���α׷����� �� ȭ��Ʈȿ�� 
	LPD3DXSPRITE			m_pBarWhite_Sprite;
	LPDIRECT3DTEXTURE9		m_pBarWhite_Texture;
	D3DXIMAGE_INFO			m_BarWhite_Sprite_Info;
	RECT					m_rcBarWhite;

	//���� �� ����� �����ΰ� ���� 
	LPD3DXSPRITE			m_pEndLogo_Sprite;
	LPDIRECT3DTEXTURE9		m_pEndLogo_Texture;
	D3DXIMAGE_INFO			m_EndLogo_Sprite_Info;
	RECT					m_rcEndLogo;

	//ī�޶� ���� 

public:
	cProgressBar_Boss();
	~cProgressBar_Boss();

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

