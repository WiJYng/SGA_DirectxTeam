#include "stdafx.h"
#include "cTestVideo.h"


cTestVideo::cTestVideo()
{
}


cTestVideo::~cTestVideo()
{

}

HRESULT cTestVideo::Scene_Init()
{
	m_pVideo = new cVideo;
	m_pVideo->Init();
	g_bRender = false;
	m_bPlay = false;

	return S_OK;
}

void cTestVideo::Scene_Release()
{
	m_pVideo->Release();
	SAFE_DELETE(m_pVideo);
}

void cTestVideo::Scene_Update(float timeDelta)
{
	HCURSOR hcur;
	hcur = LoadCursorFromFile("./Tera/UI/Mouse/Arrow.cur");
	SetCursor(hcur);
	//if (KEY_MGR->IsOnceDown(VK_RETURN))
	if(!m_bPlay)
	{
		m_pVideo->Play("./Video/Trailer.wmv");
		m_bPlay = true;
	}
	if (KEY_MGR->IsOnceDown('1'))
	{
		m_pVideo->Stop();
	}
	if (KEY_MGR->IsOnceDown('2'))
	{
		m_pVideo->Replay();
	}
	if (KEY_MGR->IsOnceDown(VK_RETURN))
	{
		g_bRender = true;
		SCENE_MGR->ChangeScene("StartScene");
		//SCENE_MGR->ChangeSceneWithLoading("StartScene", "·Îµù¾À", 1, 1);
	}
}

void cTestVideo::Scene_Render1()
{
}
