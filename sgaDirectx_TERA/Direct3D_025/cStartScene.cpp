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

HRESULT cStartScene::Scene_Init()
{
	g_CursorImgType = 0;
	g_bRender = true;
	SOUND_MGR->addSound("StartBGM", "./Tera/Audio/PoraEllinu.ogg", true, true);

	SOUND_MGR->play("StartBGM");
	//텍스쳐파일셋팅
	D3DXCreateTextureFromFileEx(
		Device, "Tera/UI/StartScene/openingImage.tga",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT,
		0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_DEFAULT, 0,
		&m_BG_Sprite_Info, NULL, &m_pBG_Texture);
	D3DXCreateSprite(Device, &m_pBG_Sprite);




	return S_OK;

}
void cStartScene::Scene_Release()
{

}
void cStartScene::Scene_Update(float timDelta)
{
	g_CursorImgType = 0;
	HCURSOR hcur;
	hcur = LoadCursorFromFile("./Tera/UI/Mouse/Arrow.cur");
	SetCursor(hcur);

	if (KEY_MGR->IsOnceDown(VK_LBUTTON))
	{
		SOUND_MGR->stop("StartBGM");
		SCENE_MGR->ChangeSceneWithLoading("InGame", "로딩씬", 1, 1);
	}
}
void cStartScene::Scene_Render1()
{

	//스프라이트 그리기
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

	//LPD3DXFONT pFont = g_pFontManager->GetFont(cFontManager::E_CHAT);
	//char szTemp[1024];
	//RECT rc;
	//SetRect(&rc, 10, 40, 11, 11);
	//sprintf(szTemp, "TEST", g_pTimeManager->GetFPS());
	//pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

}
void cStartScene::Scene_RenderSprite()
{

}



