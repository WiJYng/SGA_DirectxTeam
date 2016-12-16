#include "stdafx.h"
//test주석 
#include "cProgressBar_sMonster.h"
#include "cPartcleEmitter.h"


cProgressBar_sMonster::cProgressBar_sMonster()
{
}
cProgressBar_sMonster::~cProgressBar_sMonster()
{
}

void cProgressBar_sMonster::Setup()
{
	//바 바탕들
	//기본
	D3DXCreateTextureFromFileEx(
		Device, "Tera/UI/ProgressBar_Monster/GageSmonster_bar.tga",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT,
		0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_DEFAULT, 0,
		&m_ProgressBar_Sprite_Info, NULL, &m_pProgressBar_Texture);
	D3DXCreateSprite(Device, &m_pProgressBar_Sprite);

	//HP바 
	D3DXCreateTextureFromFileEx(
		Device, "Tera/UI/ProgressBar_Monster/GageSmonster_Hp.tga",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT,
		0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_DEFAULT, 0,
		&m_HP_ImgInfo, NULL, &m_pHP_Texture);
	D3DXCreateSprite(Device, &m_pHP_Sprite);

	m_bDeath = false;

}
void cProgressBar_sMonster::Update()
{
	if (m_nHp <= 0)
		m_bDeath = true;
}
void cProgressBar_sMonster::Render()
{
	if (!m_bDeath)
	{
		D3DXMATRIXA16 matR;
		D3DXMatrixIdentity(&matR);

		//기본
		SetRect(&m_rcProgressBar, 0, 0, m_ProgressBar_Sprite_Info.Width, m_ProgressBar_Sprite_Info.Height);
		m_pProgressBar_Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		m_pProgressBar_Sprite->SetTransform(&matR);
		m_pProgressBar_Sprite->Draw(m_pProgressBar_Texture,
			&m_rcProgressBar,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(m_rcProgressBar.left + m_fX - (m_ProgressBar_Sprite_Info.Width/2), m_rcProgressBar.top + m_fY, 0), // + 숫자 부분에 X,Y 대입 
			D3DCOLOR_XRGB(255, 255, 255));
		m_pProgressBar_Sprite->End();

		//HP바 
		float width = m_HP_ImgInfo.Width* ((float)m_nHp / (float)m_nHpMax);
		SetRect(&m_rcHP, 0, 0, width, m_HP_ImgInfo.Height);
		m_pHP_Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		m_pHP_Sprite->SetTransform(&matR);
		m_pHP_Sprite->Draw(m_pHP_Texture,
			&m_rcHP,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(m_rcProgressBar.left + m_fX - (m_ProgressBar_Sprite_Info.Width / 2)+4, m_rcProgressBar.top + m_fY + 3, 0), // + 숫자 부분에 X+3,Y+3 대입 
			D3DCOLOR_XRGB(255, 255, 255));
		m_pHP_Sprite->End();
	}


}
void cProgressBar_sMonster::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}

