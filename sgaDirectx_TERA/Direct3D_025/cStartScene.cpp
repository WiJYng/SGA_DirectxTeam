#include "stdafx.h"
#include "cStartScene.h"


cStartScene::cStartScene()
:m_pBG_Sprite(NULL)
, m_pBG_Texture(NULL)
{
}
cStartScene::~cStartScene()
{
	SAFE_DELETE(m_pBG_Sprite);
	SAFE_DELETE(m_pBG_Texture);
}

void cStartScene::Setup()
{
	//�ؽ������ϼ���
	D3DXCreateTextureFromFileEx(
		g_pD3DDevice, "Tera/UI/StartScene/Image_ClientLoading_Tex_34.tga",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT,
		0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_DEFAULT, 0,
		&m_BG_Sprite_Info, NULL, &m_pBG_Texture);
	D3DXCreateSprite(g_pD3DDevice, &m_pBG_Sprite);



}
void cStartScene::Update()
{
	if (GetKeyState(VK_LBUTTON) & 0x8000)
	{
		//��ü����
	}
}
void cStartScene::Render()
{

	//��������Ʈ �׸���
	D3DXMATRIXA16 matR;
	D3DXMatrixIdentity(&matR);
	RECT rcTemp;
	//SetRect(&rcTemp, 0, 0, m_BG_Sprite_Info.Width, m_BG_Sprite_Info.Height);

	//m_pBG_Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	//m_pBG_Sprite->SetTransform(&matR);
	//m_pBG_Sprite->Draw(m_pBG_Texture,
	//	&rcTemp,
	//	&D3DXVECTOR3(0, 0, 0),
	//	&D3DXVECTOR3(rcTemp.left, rcTemp.top, 0),
	//	D3DCOLOR_XRGB(255, 255, 255));
	//m_pBG_Sprite->End();

	SetRect(&rcTemp, 0, 0, m_BG_Sprite_Info.Width, m_BG_Sprite_Info.Height);
	m_pBG_Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pBG_Sprite->SetTransform(&matR);
	m_pBG_Sprite->Draw(m_pBG_Texture,
		&rcTemp,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(rcTemp.left, rcTemp.top, 0),
		D3DCOLOR_XRGB(255, 255, 255));
	m_pBG_Sprite->End();

	LPD3DXFONT pFont = g_pFontManager->GetFont(cFontManager::E_CHAT);
	char szTemp[1024];
	RECT rc;
	SetRect(&rc, 10, 40, 11, 11);
	sprintf(szTemp, "TEST", g_pTimeManager->GetFPS());
	pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

}
void cStartScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}

