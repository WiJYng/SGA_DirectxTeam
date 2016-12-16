#include "stdafx.h"
//test주석 
#include "cProgressBar_Boss.h"


cProgressBar_Boss::cProgressBar_Boss()
:m_pBarRed_Sprite(NULL)
, m_pBarRed_Texture(NULL)

, m_pBarWhite_Sprite(NULL)
, m_pBarWhite_Texture(NULL)

, m_pEndLogo_Sprite(NULL)
, m_pEndLogo_Texture(NULL)
{
}
cProgressBar_Boss::~cProgressBar_Boss()
{
	SAFE_DELETE(m_pBarRed_Sprite);
	SAFE_DELETE(m_pBarRed_Texture);

	SAFE_DELETE(m_pBarWhite_Sprite);
	SAFE_DELETE(m_pBarWhite_Texture);

	SAFE_DELETE(m_pEndLogo_Sprite);
	SAFE_DELETE(m_pEndLogo_Texture);
}

void cProgressBar_Boss::Setup()
{
	//바 바탕들
	//기본
	D3DXCreateTextureFromFileEx(
		Device, "Tera/UI/ProgressBar_Monster/GageBoss_bar.tga",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT,
		0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_DEFAULT, 0,
		&m_ProgressBar_Sprite_Info, NULL, &m_pProgressBar_Texture);
	D3DXCreateSprite(Device, &m_pProgressBar_Sprite);

	//레드
	D3DXCreateTextureFromFileEx(
		Device, "Tera/UI/ProgressBar_Monster/GageBoss_bar2.tga",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT,
		0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_DEFAULT, 0,
		&m_BarRed_Sprite_Info, NULL, &m_pBarRed_Texture);
	D3DXCreateSprite(Device, &m_pBarRed_Sprite);

	//화이트
	D3DXCreateTextureFromFileEx(
		Device, "Tera/UI/ProgressBar_Monster/GageBoss_bar3.tga",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT,
		0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_DEFAULT, 0,
		&m_BarWhite_Sprite_Info, NULL, &m_pBarWhite_Texture);
	D3DXCreateSprite(Device, &m_pBarWhite_Sprite);


	//HP바 
	D3DXCreateTextureFromFileEx(
		Device, "Tera/UI/ProgressBar_Monster/GageBoss_Hp.tga",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT,
		0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_DEFAULT, 0,
		&m_HP_ImgInfo, NULL, &m_pHP_Texture);
	D3DXCreateSprite(Device, &m_pHP_Sprite);

	//HP바 
	D3DXCreateTextureFromFileEx(
		Device, "Tera/UI/Monster/EndLogo.tga",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT,
		0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_DEFAULT, 0,
		&m_EndLogo_Sprite_Info, NULL, &m_pEndLogo_Texture);
	D3DXCreateSprite(Device, &m_pEndLogo_Sprite);

	m_bDeath = false;

}
void cProgressBar_Boss::Update()
{
	if (m_nHp <= 0)
	{
		m_bDeath = true;
		m_nHp = 0;
	}
		
}
void cProgressBar_Boss::Render()
{
	D3DXMATRIXA16 matR;
	D3DXMatrixIdentity(&matR);

	//바 바탕들
	//화이트
	//D3DXMatrixIdentity(&matR);
	//SetRect(&m_rcBarWhite, 0, 0, m_BarWhite_Sprite_Info.Width, m_BarWhite_Sprite_Info.Height);
	//m_pBarWhite_Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	//m_pBarWhite_Sprite->SetTransform(&matR);
	//m_pBarWhite_Sprite->Draw(m_pBarWhite_Texture,
	//	&m_rcBarWhite,
	//	&D3DXVECTOR3(0, 0, 0),
	//	&D3DXVECTOR3(m_rcBarWhite.left + 235, m_rcBarWhite.top + 5, 0),
	//	D3DCOLOR_XRGB(255, 255, 255));
	//m_pBarWhite_Sprite->End();

	//기본
	SetRect(&m_rcProgressBar, 0, 0, m_ProgressBar_Sprite_Info.Width, m_ProgressBar_Sprite_Info.Height);
	m_pProgressBar_Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pProgressBar_Sprite->SetTransform(&matR);
	m_pProgressBar_Sprite->Draw(m_pProgressBar_Texture,
		&m_rcProgressBar,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(m_rcProgressBar.left + 435 - 80, m_rcProgressBar.top + 5, 0), // 460,15
		D3DCOLOR_XRGB(255, 255, 255));
	m_pProgressBar_Sprite->End();

	//레드
	D3DXMatrixIdentity(&matR);
	SetRect(&m_rcBarRed, 0, 0, m_BarRed_Sprite_Info.Width, m_BarRed_Sprite_Info.Height);
	m_pBarRed_Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pBarRed_Sprite->SetTransform(&matR);
	m_pBarRed_Sprite->Draw(m_pBarRed_Texture,
		&m_rcBarRed,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(m_rcBarRed.left + 415 - 80, m_rcBarRed.top - 10, 0),
		D3DCOLOR_XRGB(255, 255, 255));
	m_pBarRed_Sprite->End();

	//HP바 
	//플레이어 hp와의 작용 
	float width = m_HP_ImgInfo.Width* ((float)m_nHp / (float)m_nHpMax);
	SetRect(&m_rcHP, 0, 0, width, m_HP_ImgInfo.Height);
	m_pHP_Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pHP_Sprite->SetTransform(&matR);
	m_pHP_Sprite->Draw(m_pHP_Texture,
		&m_rcHP,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(m_rcProgressBar.left + 485 - 80, m_rcProgressBar.top + 23, 0),
		D3DCOLOR_XRGB(255, 255, 255));
	m_pHP_Sprite->End();

	//엔딩로고 
	if (m_bDeath)
	{
		D3DXMatrixIdentity(&matR);
		SetRect(&m_rcEndLogo, 0, 0, m_EndLogo_Sprite_Info.Width, m_EndLogo_Sprite_Info.Height);
		m_pEndLogo_Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		m_pEndLogo_Sprite->SetTransform(&matR);
		m_pEndLogo_Sprite->Draw(m_pEndLogo_Texture,
			&m_rcEndLogo,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(m_rcEndLogo.left + 455, m_rcEndLogo.top + 270, 0),
			D3DCOLOR_XRGB(255, 255, 255));
		m_pEndLogo_Sprite->End();
	}
}
void cProgressBar_Boss::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}
