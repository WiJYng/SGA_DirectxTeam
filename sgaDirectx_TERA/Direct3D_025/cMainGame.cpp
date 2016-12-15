#include "StdAfx.h"
#include "cMainGame.h"
#include "cImage.h"
#include "cScene_00.h"
#include "cScene_01.h"
#include "cScene_02.h"
#include "cScene_main.h"
#include "cTestVideo.h"
#include "cStartScene.h"
#include "cLoadingScene.h"

cMainGame::cMainGame(void)
{
}

cMainGame::~cMainGame(void)
{
}

//����
HRESULT cMainGame::Init(void)
{
	//�����õ�
	SetRandomSeed();
	
	//����̽� ����
	CreateDevice();

	//�Ŵ��� ����
	TIME_MGR->Init();
	//LOG_MGR->Init( LOG_WINDOW | LOG_FILE, g_hWnd, "Dump" );
	DXFONT_MGR->Init( Device );	
	GIZMO_MGR->Init( Device );
	SPRITE_MGR->Init( Device );
	SCENE_MGR->Init();
	
	//���ӿ� ���Ǵ� �� �߰�
	//SCENE_MGR->AddScene( "Test00", new cScene_00() );
	SCENE_MGR->AddScene("InGame", new cScene_main());
	SCENE_MGR->AddScene("Trailer", new cTestVideo());
	SCENE_MGR->AddScene("StartScene", new cStartScene());
	SCENE_MGR->AddScene("LoadingScene", new cLoadingScene());
	SCENE_MGR->AddLoadingScene( "�ε���", new cScene_02() );

	//���� ���۾�
	SCENE_MGR->ChangeScene( "StartScene" );
	
	//return E_FAIL;
	return S_OK;		
}	

//����
void cMainGame::Release()
{
	
	//������
	//m_pNowScene->Release();
	//SAFE_DELETE( m_pNowScene );

	//�Ŵ��� ����
	GIZMO_MGR->Release();
	cGizmoManager::ReleaseInstance();
	TIME_MGR->Release();
	cTimeMgr::ReleaseInstance();
	KEY_MGR->Release();
	cKeyMgr::ReleaseInstance();
	LOG_MGR->Release();
	cLogMgr::ReleaseInstance();
	DXFONT_MGR->Release();
	cDXFontManager::ReleaseInstance();
	SPRITE_MGR->Release();
	cSpriteManager::ReleaseInstance();
	SCENE_MGR->Release();
	cScene_Mgr::ReleaseInstance();
	cPhysicManager::ReleaseInstance();

	RESOURCE_TEXTURE->ClearResource();
	cResourceMgr_Texture::ReleaseInstance();
	RESOURCE_FX->ClearResource();
	cResourceMgr_ShaderFX::ReleaseInstance();
	RESOURCE_STATICXMESH->ClearResource();
	cResourceMgr_XStaticMesh::ReleaseInstance();
	RESOURCE_SKINNEDXMESH->ClearResource();
	cResourceMgr_XSkinnedMesh::ReleaseInstance();




	//����̽� ����
	ReleaseDevice();
}

//������Ʈ
void cMainGame::Update()
{
	//Ÿ�ӸŴ��� ������Ʈ
	TIME_MGR->UpdateTime( 60.0f );
	
	//�������� ���� �ð�
	double timeDelta = TIME_MGR->GetFrameDeltaSec();

	//��������Ʈ
	SCENE_MGR->Update( timeDelta );
}

//��ο�
void cMainGame::Draw()
{
	//���۸� û���Ѵ�
	HRESULT result = Device->Clear(
		0,							//û���� ������ D3DRECT �迭 ����		( ��ü Ŭ���� 0 )
		NULL,						//û���� ������ D3DRECT �迭 ������		( ��ü Ŭ���� NULL )
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,		//û�ҵ� ���� �÷��� ( D3DCLEAR_TARGET �÷�����, D3DCLEAR_ZBUFFER ���̹���, D3DCLEAR_STENCIL ���ٽǹ���
		D3DCOLOR_XRGB(255, 255, 255),					//�÷����۸� û���ϰ� ä���� ����( 0xAARRGGBB )
		1.0f,						//���̹��۸� û���Ұ� ( 0 ~ 1, 0 �� ī�޶󿡼� ���ϰ���� 1 �� ī�޶󿡼� ���� �� )
		0							//���ٽ� ���۸� ä�ﰪ
		);
	
	//���� û�Ұ� �����ߴٸ�.......
	if( SUCCEEDED( result ) )
	{
		//����̽� ������ ���� ���
		Device->BeginScene();

		//������ ���

		//������
		SCENE_MGR->Render();


#ifdef _DEBUG		//����� ��忡���� ����
		//����̽� ������ ���� ���
		//���� �׸���
		//GIZMO_MGR->WorldGrid( 1, 10 );

		//Ÿ������ ���
		//TIME_MGR->DrawTimeInfo();
#endif

		Device->EndScene();


		//�������� ���۳����� ȭ�鿡 ����
		Device->Present(  0, 0, 0, 0 );
	}
	

}



//////////////////////////////////////////////////////////////////////////

//���� ���ν��� �Լ�
LRESULT cMainGame::MainProc( HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam )
{
	switch( iMessage )
	{	
	case WM_MOUSEWHEEL:
		g_Wheel = (short)HIWORD(wParam);
		break;
	case WM_TIMER:
		Update();
		break;

	case WM_KEYDOWN:
		switch( wParam )
		{
		case VK_ESCAPE:
			DestroyWindow( hWnd );
			break;
		}
		break;

	case WM_DESTROY:			//�����찡 �ı��ȴٸ�..
		PostQuitMessage( 0 );	//���α׷� ���� ��û ( �޽��� ������ ���������� �ȴ� )
		break;
	}
	return DefWindowProc( hWnd, iMessage, wParam, lParam );
}

