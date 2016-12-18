#include "stdafx.h"
#include "cLoadingScene.h"


cLoadingScene::cLoadingScene()
:m_pBG_Sprite(NULL)
, m_pBG_Texture(NULL)

, m_pLBfront_sp(NULL)
, m_pLBback_sp(NULL)
, m_pLBfront_texture(NULL)
, m_pLBback_texture(NULL)
{
}
cLoadingScene::~cLoadingScene()
{
	SAFE_DELETE(m_pBG_Sprite);
	SAFE_DELETE(m_pBG_Texture);

	SAFE_RELEASE(m_pLBfront_sp);
	SAFE_RELEASE(m_pLBback_sp);
	SAFE_RELEASE(m_pLBfront_texture);
	SAFE_RELEASE(m_pLBback_texture);

	//DeleteCriticalSection(&cs);

}

HRESULT cLoadingScene::Scene_Init()
{
	g_CursorImgType = 1;
	g_bRender = true;

	//배경
	D3DXCreateTextureFromFileEx(
		Device, "Tera/UI/LoadingScene/loadingimage_citywar_1_2.tga",
		D3DX_DEFAULT_NONPOW2,D3DX_DEFAULT_NONPOW2,D3DX_DEFAULT,
		0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,D3DX_DEFAULT,0,
		&m_BG_Sprite_Info,NULL,&m_pBG_Texture);
	D3DXCreateSprite(Device, &m_pBG_Sprite);

	//로딩바
	DWORD dwThID = 0;
	CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SetZealots, this, NULL/*CREATE_SUSPENDED*/, &dwThID));
	CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SetLoadingGauge, this, NULL/*CREATE_SUSPENDED*/, &dwThID));
	//InitializeCriticalSection(&cs); //cs는 d3d.cpp에서 선언하고 extern CRITICAL_SECTION cs; 라고 stdafx.h에 추가 

	D3DXCreateTextureFromFileEx(
		Device, "Tera/UI/LoadingScene/LoadingBar_front.tga", //"Tera/UI/StartScene/Image_ClientLoading_Tex_34.tga"
		D3DX_DEFAULT_NONPOW2,D3DX_DEFAULT_NONPOW2,D3DX_DEFAULT,
		0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,D3DX_DEFAULT,0,
		&m_LBfront_ImgInfo,NULL,&m_pLBfront_texture);
	D3DXCreateSprite(Device, &m_pLBfront_sp);

	D3DXCreateTextureFromFileEx(
		Device, "Tera/UI/LoadingScene/LoadingBar_back.tga",
		D3DX_DEFAULT_NONPOW2,D3DX_DEFAULT_NONPOW2,D3DX_DEFAULT,
		0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,D3DX_DEFAULT,0,
		&m_LBback_ImgInfo,NULL,&m_pLBback_texture);
	D3DXCreateSprite(Device, &m_pLBback_sp);

	SetRect(&m_rcLB_front, 200, 200, m_LBfront_ImgInfo.Width+200, m_LBfront_ImgInfo.Height+200);
	SetRect(&m_rcLB_back, 0, 0, m_LBback_ImgInfo.Width, m_LBback_ImgInfo.Height);

	return S_OK;
}
void cLoadingScene::Scene_Release()
{

}
void cLoadingScene::Scene_Update(float timDelta)
{
	
	g_CursorImgType = 1;
	if (KEY_MGR->IsOnceDown(VK_LBUTTON))
	{
		//SCENE_MGR->ChangeScene("Trailer");
	}
	
	SetRect(&m_rcLB_front, 200, 200, m_LBfront_ImgInfo.Width + 200, m_LBfront_ImgInfo.Height + 200);
}
void cLoadingScene::Scene_Render1()
{

	//배경
	D3DXMATRIXA16 matR;
	D3DXMatrixIdentity(&matR);
	RECT rcTemp;
	SetRect(&rcTemp, 0, 0, m_BG_Sprite_Info.Width, m_BG_Sprite_Info.Height);
	m_pBG_Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pBG_Sprite->SetTransform(&matR);
	m_pBG_Sprite->Draw(m_pBG_Texture,
		&rcTemp,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(rcTemp.left, rcTemp.top, 0),
		D3DCOLOR_XRGB(255, 255, 255));
	m_pBG_Sprite->End();


	//로딩바
	//if (m_rowCount >= MAXROWCOUNT * MAXROWCOUNT) {
	//	EnterCriticalSection(&cs);
	//	for each (auto p in m_vecSkinnedMesh)
	//	{
	//		if (m_pFrustum->IsIn(p->GetBoundingSphere()))
	//			p->UpdateAndRender();
	//	}
	//	LeaveCriticalSection(&cs);
	//}
	//size_t r = 0;
	//size_t t = strlen(szTemp);
	//float per = (float)m_rowCount / (float)(MAXROWCOUNT * MAXROWCOUNT);
	//r = (int)(per * t);
	//(r % 2 == 0 ? r : r -= 1);

	//if (m_rowCount > 1000)
	//	int a = 0;

	//텍스트
	//LPD3DXFONT pFont = g_pFontManager->GetFont(cFontManager::E_CHAT);
	//char szTemp[1024];
	RECT rc;
	SetRect(&rc, 120, 75, 121, 101);
	//sprintf(szTemp, "현재 %d 로딩중..../전체 %d", m_rowCount, MAXROWCOUNT * MAXROWCOUNT);
	//sprintf(szTemp, "현재 %d 로딩중..../전체 %d", 1, 100);
	//pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

	//로딩바처리
	float barWidth;
	//barWidth = m_LBback_ImgInfo.Width * per * 4.0f;
	barWidth = m_LBback_ImgInfo.Width * 0 * 4.0f;

	//로딩바이미지
	//RECT rcTemp2;
	//SetRect(&rcTemp2, 0, 0, m_LBfront_ImgInfo.Width, m_LBfront_ImgInfo.Height);
	m_pLBfront_sp->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pLBfront_sp->SetTransform(&matR);
	m_pLBfront_sp->Draw(m_pLBfront_texture,
		&m_rcLB_front,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(m_rcLB_front.left, m_rcLB_front.top, 0),
		D3DCOLOR_XRGB(255, 255, 255));
	m_pLBfront_sp->End();

	//로딩바이미지
	//RECT rcTemp3;
	//SetRect(&rcTemp3, 0, 0, m_LBback_ImgInfo.Width, m_LBback_ImgInfo.Height);
	//m_pLBback_sp->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	//m_pLBback_sp->SetTransform(&matR);
	//m_pLBback_sp->Draw(m_pLBback_texture,
	//	&m_rcLB_back,
	//	&D3DXVECTOR3(0, 0, 0),
	//	&D3DXVECTOR3(m_rcLB_back.left, m_rcLB_back.top, 0),
	//	D3DCOLOR_XRGB(255, 255, 255));
	//m_pLBback_sp->End();

	//SetRect(&rc, 30, 30, 101, 101);
	//sprintf(szTemp, "%d", g_pTimeManager->GetFPS());
	//pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

	//렌더테스트 텍스쳐
	//LPD3DXFONT pFont = g_pFontManager->GetFont(cFontManager::E_CHAT);
	//char szTemp[1024];
	//RECT rc;
	//SetRect(&rc, 10, 40, 11, 11);
	//sprintf(szTemp, "TEST", g_pTimeManager->GetFPS());
	//pFont->DrawTextA(NULL, szTemp, strlen(szTemp), &rc, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

}
void cLoadingScene::Scene_RenderSprite()
{

}

void cLoadingScene::SetZealots(LPVOID pParam)
{
	//cMainGame* pThis = (cMainGame*)pParam;

	//for (int x = -(MAXROWCOUNT / 2); x < (MAXROWCOUNT / 2); ++x)
	//{
	//	for (int z = -(MAXROWCOUNT / 2); z < (MAXROWCOUNT / 2); ++z)
	//	{
	//		EnterCriticalSection(&cs);

	//		cSkinnedMesh* p = new cSkinnedMesh("Zealot/", "zealot.X");
	//		p->SetPosition(D3DXVECTOR3(x, 0, z));
	//		p->SetRandomTrackPosition();
	//		p->SetAnimationIndex(rand() % 5);
	//		pThis->m_vecSkinnedMesh.push_back(p);

	//		LeaveCriticalSection(&cs);
	//	}
	//}
}
void cLoadingScene::SetLoadingGauge(LPVOID pParam)
{
	//cMainGame* pThis = (cMainGame*)pParam;

	//while (pThis->m_rowCount <= (MAXROWCOUNT * MAXROWCOUNT))
	//{
	//	if (pThis->m_rowCount == (MAXROWCOUNT * MAXROWCOUNT)) break;

	//	EnterCriticalSection(&cs);
	//	pThis->m_rowCount = pThis->m_vecSkinnedMesh.size();

	//	LeaveCriticalSection(&cs);
	//}
}
