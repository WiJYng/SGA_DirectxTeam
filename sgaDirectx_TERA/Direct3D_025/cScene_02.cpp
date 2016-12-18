#include "StdAfx.h"
#include "cScene_02.h"
#include "cLight_Direction.h"
#include "cXMesh_Static.h"
#include "cBaseObject.h"
#include "cTransform.h"
#include "cCamera.h"
#include "cTerrain.h"
#include "cSkinnedAnimation.h"
#include "cLight_Point.h"

cScene_02::cScene_02(void)
{
}
cScene_02::~cScene_02(void)
{
}

HRESULT cScene_02::Scene_Init()
{
	g_bRender = true;

	//배경
	D3DXCreateTextureFromFileEx(
		Device, "Tera/UI/LoadingScene/loadingimage.tga",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT,
		0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_DEFAULT, 0,
		&m_BG_Sprite_Info, NULL, &m_pBG_Texture);
	D3DXCreateSprite(Device, &m_pBG_Sprite);

	//로딩바

	D3DXCreateTextureFromFileEx(
		Device, "Tera/UI/LoadingScene/LoadingBar_front.tga", //"Tera/UI/StartScene/Image_ClientLoading_Tex_34.tga"
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT,
		0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_DEFAULT, 0,
		&m_LBfront_ImgInfo, NULL, &m_pLBfront_texture);
	D3DXCreateSprite(Device, &m_pLBfront_sp);

	D3DXCreateTextureFromFileEx(
		Device, "Tera/UI/LoadingScene/LoadingBar_back.tga",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT,
		0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_DEFAULT, 0,
		&m_LBback_ImgInfo, NULL, &m_pLBback_texture);
	D3DXCreateSprite(Device, &m_pLBback_sp);

	////g_bRender = true;

	////원래 있던 매쉬에서 다음과 같은 행렬로 보정시켜 
	////모든 정보를 틀어버린다.
	//D3DXMATRIXA16 matScale;
	//D3DXMatrixScaling( &matScale, 0.007f, 0.007f, 0.007f );
	//D3DXMATRIXA16 matCorrection = matScale;

	////원본 메쉬 로딩
	//cXMesh_Static* mesh = 
	//	RESOURCE_STATICXMESH->GetResource( 
	//	"./Resources/Meshes/Tree/PineTree_01.X", &matCorrection );

	//this->object = new cBaseObject();
	//this->object->SetActive( true );
	//this->object->SetMesh( mesh );

	////기본라이트 방향
	//this->pSceneBaseDirectionLight->pTransform->RotateWorld( 
	//	90.0f * ONE_RAD, 0, 0 );


	//this->pMainCamera->SetWorldPosition( 0, 5, -10 );


	return S_OK;
}

void cScene_02::Scene_Release()
{
	//오브젝트 해재
	SAFE_DELETE(  this->object);
	
}

void cScene_02::Scene_Update( float timDelta )
{
	HCURSOR hcur;
	hcur = LoadCursorFromFile("./Tera/UI/Mouse/Arrow.cur"); //Arrow.cur
	SetCursor(hcur);

	if (KEY_MGR->IsOnceDown(VK_LBUTTON))
	{
		//SCENE_MGR->ChangeScene("Trailer");
	}

	SetRect(&m_rcLB_front, 200, 200, m_LBfront_ImgInfo.Width + 200, m_LBfront_ImgInfo.Height + 200);
	
	
}

void cScene_02::Scene_Render1()
{
	////배경
	D3DXMATRIXA16 matR;
	D3DXMatrixIdentity(&matR);
	RECT rcTemp;
	SetRect(&rcTemp, 0, 0, m_BG_Sprite_Info.Width, m_BG_Sprite_Info.Height-100);
	m_pBG_Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pBG_Sprite->SetTransform(&matR);
	m_pBG_Sprite->Draw(m_pBG_Texture,
		&rcTemp,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(rcTemp.left, rcTemp.top, 0),
		D3DCOLOR_XRGB(255, 255, 255));
	m_pBG_Sprite->End();

	RECT screenRc;
	GetClientRect(g_hWnd, &screenRc);

	float wid = 1192-350;
	float hei = 765+45;

	//로딩바이미지
	//float hpWidth = m_HP_ImgInfo.Width* ((float)m_nHp / (float)m_nHpMax);
	SetRect(&m_rcLB_front, 0, 0, m_LBfront_ImgInfo.Width, m_LBfront_ImgInfo.Height);
	m_pLBfront_sp->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pLBfront_sp->SetTransform(&matR);
	m_pLBfront_sp->Draw(m_pLBfront_texture,
		&m_rcLB_front,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(wid, hei, 0),
		D3DCOLOR_XRGB(255, 255, 255));
	m_pLBfront_sp->End();

	//로딩바이미지
	float barWidth = m_LBback_ImgInfo.Width* ((float)SCENE_MGR->fProgress / (float)100);
	SetRect(&m_rcLB_back, 0, 0, barWidth, m_LBback_ImgInfo.Height);
	m_pLBback_sp->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pLBback_sp->SetTransform(&matR);
	m_pLBback_sp->Draw(m_pLBback_texture,
		&m_rcLB_back,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(wid, hei, 0),
		D3DCOLOR_XRGB(255, 255, 255));
	m_pLBback_sp->End();

	DXFONT_MGR->PrintText(SCENE_MGR->fString, wid+15, hei - 20, D3DCOLOR_XRGB(255, 255, 255));//0x00000000);
	char szTemp[128];
	sprintf(szTemp, "%.2f percent 로딩중", SCENE_MGR->fProgress);

	DXFONT_MGR->PrintText(szTemp, wid+15 + 150, hei - 20, D3DCOLOR_XRGB(255, 255, 255));
	
	//
	//cXMesh_Static::SetCamera( this->pMainCamera );
	//cXMesh_Static::SetTechniqueName("Base");		//쉐도우랑 같이 그릴려면 ReciveShadow 로 Technique 셋팅
	//cXMesh_Static::SetBaseLight( this->pSceneBaseDirectionLight );;


	//cXMesh_Skinned::SetCamera( this->pMainCamera );
	//cXMesh_Skinned::SetTechniqueName("ReciveShadow");
	//cXMesh_Skinned::sSkinnedMeshEffect->SetTexture("Ramp_Tex", RESOURCE_TEXTURE->GetResource("./Resources/Testures/Ramp_1.png") );
	//cXMesh_Skinned::SetBaseLight( this->pSceneBaseDirectionLight );
	//
	//this->object->Render();

}


void cScene_02::Scene_RenderSprite()
{

}


