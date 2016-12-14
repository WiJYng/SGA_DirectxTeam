// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�
#include <string>


//�ʿ��� ��� (DirectSDK ��ġ����/Include)
//d3dx9.h
//d3d9.h
//#include "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include/d3d9.h"
//#include "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include/d3dx9.h"

//(DirectSDK ��ġ����/Include) ��ΰ� ������Ʈ�� System ������ ����� �Ǿ��ִٸ� < > �ε� ���԰���
#include <d3d9.h>
#include <d3dx9.h>

//System ���� (DirectSDK ��ġ����/Include) ��� ���
//�ַ��Ž���⿡�� ������Ʈ ��Ŭ��
//�Ӽ�
//�����Ӽ��� VC++ ���͸� �׸���
//â�� ����������.
//���Ե��丮ĭ�� �����ӹ��ڿ������� �����ϸ� ������ �Ʒ�ȭ��ǥ Ŭ��
//<����..> ���ڸ�Ŭ��
//���Ե��丮 â�� �����鼭 ���� ����� �����߰� ������Ŭ��
//Ŭ���ؼ� ������ �� ������ ... ��ư ����
//Ž���� �����鼭 (DirectSDK ��ġ����/Include) ����


//�ʿ���̺귯�� (DirectSDK ��ġ����/Lib/x86)
//d3dx9.lib
//d3d9.lib
//#pragma comment( lib, "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86/d3d9.lib" )
//#pragma comment( lib, "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86/d3dx9.lib" )
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )


//System ���� (DirectSDK ��ġ����/Lib/x86) ��� ���
//�ַ��Ž���⿡�� ������Ʈ ��Ŭ��
//�Ӽ�
//�����Ӽ��� VC++ ���͸� �׸���
//â�� ����������.
//���̺귯�� ���丮ĭ�� �����ӹ��ڿ������� �����ϸ� ������ �Ʒ�ȭ��ǥ Ŭ��
//<����..> ���ڸ�Ŭ��
//���Ե��丮 â�� �����鼭 ���� ����� �����߰� ������Ŭ��
//Ŭ���ؼ� ������ �� ������ ... ��ư ����
//Ž���� �����鼭 (DirectSDK ��ġ����/Lib/x86) ����





//
// ��ũ�� ���
//
#define WINSIZE_X	1200			//�ʱ� ������ ���� ũ��
#define WINSIZE_Y	900			//�ʱ� ������ ���� ũ��
#define WINPOS_X	0			//�ʱ� ������ ���� ��ġ X
#define WINPOS_Y	0			//�ʱ� ������ ���� ��ġ Y
#define WIN_CLASS	"Windows Exam"		//������ Ŭ���� �̸�
#define WIN_TITLE	"D3D_TERA"		//������ Ÿ��Ʋ �̸�
#define WIN_STYLE	WS_CAPTION | WS_SYSMENU | WS_BORDER	//������ ����


#define ONE_RAD 0.017453f				//����1 ��


//
// ��ũ�� �Լ�
//
#define SAFE_DELETE(p)		{ if(p){ delete (p); (p) = NULL; } }
#define SAFE_DELETE_ARR(p)	{ if(p){ delete[] (p); (p) = NULL; } }
#define SAFE_RELEASE(p)		{ if(p){ (p)->Release(); (p) = NULL; } }

//
// ���� ����
//
extern HWND			g_hWnd;		//������ �ڵ� ( �ڽ��� ���α׷����� �����ִ� ������ ��ȣ )
extern HINSTANCE	g_hInst;	//���α׷� �ν��Ͻ� �ڵ� ( OS �� �ο��� ���α׷� ��ȣ )
extern int			g_Wheel;

//extern bool         ex_wheelUp;
//extern bool         ex_wheelDown;
//extern bool         g_bDXRender;
//
#include <string>
#include <vector>
#include <map>
#include <set>


//
// �Ŵ���
//
#include "MyUtil.h"

using namespace MyUtil;
using namespace std;


//
// ��Ÿ ���
//
#include "cTimeMgr.h"
#include "cKeyMgr.h"
#include "cLogMgr.h"
#include "cDXFontManager.h"
#include "cGizmoManager.h"
#include "cPhysicManager.h"
#include "cSpriteManager.h"
#include "cScene_Mgr.h"
#include "cResourceMgr_Texture.h"
#include "cResourceMgr_ShaderFX.h"
#include "cResourceMgr_XStaticMesh.h"
#include "cResourceMgr_XSkinnedMesh.h"//enum
enum MonState
{
	Wait,
	Run,
	Attack,
	Stun,
	Death,
	DeathWait,
	Mempty
};

//��Į ����
enum E_DECALEFFECT
{
	DECAL_BASE = 0,
	DECAL_LOTATION,
};

//pt����ü
struct ST_PT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR2 t;

	ST_PT_VERTEX() : p(0, 0, 0), t(0, 0) {}
	ST_PT_VERTEX(D3DXVECTOR3 _p, D3DXVECTOR2 _t) : p(_p), t(_t) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1, };
};
