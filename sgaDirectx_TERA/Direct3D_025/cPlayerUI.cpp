#include "stdafx.h"
//test�ּ� 
#include "cPlayerUI.h"


cPlayerUI::cPlayerUI()
: m_pProgressBar_Sprite(NULL)
, m_pProgressBar_Texture(NULL)

, m_pHP_Sprite(NULL)
, m_pMP_Sprite(NULL)
, m_pHP_Texture(NULL)
, m_pMP_Texture(NULL)

, m_pKcBoard_sprite(NULL)
, m_pkcNumber_sprite(NULL)
, m_pKcBoard_Texture(NULL)
, m_pkcNumber_Texture(NULL)

, m_bQWindowCenter_firstCheck(true)
, m_bQwindowCenter_On(true)
, m_bQwindowRight_On(false)
, m_bKeyWindow_On(false)

, m_pKeyWindow_Sprite(NULL)
, m_pKeyWindow_Texture(NULL)
, m_pQwindowCenter_Sprite(NULL)
, m_pQwindowCenter_Texture(NULL)
, m_pQwindowRight_Sprite(NULL)
, m_pQwindowRight_Texture(NULL)

, m_bBossMeet(false)
{ 
}
cPlayerUI::~cPlayerUI()
{
	SAFE_DELETE(m_pProgressBar_Sprite);
	SAFE_DELETE(m_pProgressBar_Texture);

	SAFE_DELETE(m_pHP_Sprite);
	SAFE_DELETE(m_pMP_Sprite);
	SAFE_DELETE(m_pHP_Texture);
	SAFE_DELETE(m_pMP_Texture);

	SAFE_DELETE(m_pKcBoard_sprite);
	SAFE_DELETE(m_pkcNumber_sprite);
	SAFE_DELETE(m_pKcBoard_Texture);
	SAFE_DELETE(m_pkcNumber_Texture);

	SAFE_DELETE(m_pKeyWindow_Sprite);
	SAFE_DELETE(m_pKeyWindow_Texture);
	SAFE_DELETE(m_pQwindowCenter_Sprite);
	SAFE_DELETE(m_pQwindowCenter_Texture);
	SAFE_DELETE(m_pQwindowRight_Sprite);
	SAFE_DELETE(m_pQwindowRight_Texture);
}

void cPlayerUI::Setup()
{
	//Ű����â
	D3DXCreateTextureFromFileEx(
		Device, "Tera/UI/PlayerUI/KeyExplain2.tga",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT,
		0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_DEFAULT, 0,
		&m_KeyWindow_Sprite_Info, NULL, &m_pKeyWindow_Texture);
	D3DXCreateSprite(Device, &m_pKeyWindow_Sprite);

	//�߾�����Ʈâ
	D3DXCreateTextureFromFileEx(
		Device, "Tera/UI/PlayerUI/QuestWindow1.tga",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT,
		0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_DEFAULT, 0,
		&m_QwindowCenter_Sprite_Info, NULL, &m_pQwindowCenter_Texture);
	D3DXCreateSprite(Device, &m_pQwindowCenter_Sprite);

	//����������Ʈâ
	D3DXCreateTextureFromFileEx(
		Device, "Tera/UI/PlayerUI/QuestWindow3.tga",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT,
		0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_DEFAULT, 0,
		&m_QwindowRight_Sprite_Info, NULL, &m_pQwindowRight_Texture);
	D3DXCreateSprite(Device, &m_pQwindowRight_Sprite);

	//�� ���� 
	D3DXCreateTextureFromFileEx(
		Device, "Tera/UI/PlayerUI/ProgressBar.tga",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT,
		0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_DEFAULT, 0,
		&m_ProgressBar_Sprite_Info, NULL, &m_pProgressBar_Texture);
	D3DXCreateSprite(Device, &m_pProgressBar_Sprite);

	//HP�� 
	D3DXCreateTextureFromFileEx(
		Device, "Tera/UI/PlayerUI/HpBar.tga",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT,
		0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_DEFAULT, 0,
		&m_HP_ImgInfo, NULL, &m_pHP_Texture);
	D3DXCreateSprite(Device, &m_pHP_Sprite);

	//MP�� 
	D3DXCreateTextureFromFileEx(
		Device, "Tera/UI/PlayerUI/MpBar.tga",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT,
		0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_DEFAULT, 0,
		&m_MP_ImgInfo, NULL, &m_pMP_Texture);
	D3DXCreateSprite(Device, &m_pMP_Sprite);



	//ųī���� ����
	D3DXCreateTextureFromFileEx(
		Device, "Tera/UI/PlayerUI/KillCounter_Board.tga",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT,
		0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_DEFAULT, 0,
		&m_KcBoard_ImgInfo, NULL, &m_pKcBoard_Texture);
	D3DXCreateSprite(Device, &m_pKcBoard_sprite);

	//ųī���� ����
	D3DXCreateTextureFromFileEx(
		Device, "Tera/UI/PlayerUI/ComboCounter_Num2.tga",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT,
		0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_DEFAULT, 0,
		&m_KcNumber_ImgInfo, NULL, &m_pkcNumber_Texture);
	D3DXCreateSprite(Device, &m_pkcNumber_sprite);


}
void cPlayerUI::Update()
{
	if (m_bQWindowCenter_firstCheck)
	{
		if (KEY_MGR->IsOnceDown(VK_LBUTTON))
		{
			m_bQwindowCenter_On = false;
			m_bQWindowCenter_firstCheck = false;
			m_bQwindowRight_On = true;
		}
	}
	//if (m_bQwindowCenter_On == false)
	//{
	//	m_bQwindowRight_On = true;
	//}
	if (KEY_MGR->IsOnceDown('Z'))
	{
		m_bKeyWindow_On = !m_bKeyWindow_On;
	}

	if (m_nKillNum <= 0)
	{

	}
}
void cPlayerUI::Render()
{
	D3DXMATRIXA16 matR;
	D3DXMatrixIdentity(&matR);

	RECT screenRc;
	GetClientRect(g_hWnd, &screenRc);

	//Ű����â
	if (m_bKeyWindow_On)
	{
		SetRect(&m_rcKeyWindow, 0, 0, m_KeyWindow_Sprite_Info.Width, m_KeyWindow_Sprite_Info.Height);
		m_pKeyWindow_Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		m_pKeyWindow_Sprite->SetTransform(&matR);
		m_pKeyWindow_Sprite->Draw(m_pKeyWindow_Texture,
			&m_rcKeyWindow,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(
			screenRc.left + 20,
			screenRc.bottom - 285,
			0
			),
			D3DCOLOR_XRGB(255, 255, 255));
		m_pKeyWindow_Sprite->End();
	}

	//�߾�����Ʈâ
	if (m_bQwindowCenter_On)
	{
		SetRect(&m_rcQwindowCenter, 0, 0, m_QwindowCenter_Sprite_Info.Width, m_QwindowCenter_Sprite_Info.Height);
		m_pQwindowCenter_Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		m_pQwindowCenter_Sprite->SetTransform(&matR);
		m_pQwindowCenter_Sprite->Draw(m_pQwindowCenter_Texture,
			&m_rcQwindowCenter,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(
			screenRc.left + (screenRc.right - screenRc.left) / 2 - 250,
			screenRc.top + (screenRc.bottom - screenRc.top) / 2 - 100,
			0
			),
			D3DCOLOR_XRGB(255, 255, 255));
		m_pQwindowCenter_Sprite->End();
	}

	//����������Ʈâ
	if (m_bQwindowRight_On)
	{
		SetRect(&m_rcQwindowRight, 0, 0, m_QwindowRight_Sprite_Info.Width, m_QwindowRight_Sprite_Info.Height);
		m_pQwindowRight_Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		m_pQwindowRight_Sprite->SetTransform(&matR);
		m_pQwindowRight_Sprite->Draw(m_pQwindowRight_Texture,
			&m_rcQwindowRight,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(
			screenRc.right - 200,
			screenRc.top + (screenRc.bottom - screenRc.top) / 2 - 100,
			0
			),
			D3DCOLOR_XRGB(255, 255, 255));
		m_pQwindowRight_Sprite->End();
	}


	float wid = screenRc.left + 20;
	float hei = screenRc.bottom - (m_rcProgressBar.bottom - m_rcProgressBar.top) / 2 + 50;
		//(screenRc.left + (screenRc.right - screenRc.left) / 2) - (m_rcProgressBar.right - m_rcProgressBar.left) / 2;

	//�� ���� 
	SetRect(&m_rcProgressBar, 0, 0, m_ProgressBar_Sprite_Info.Width, m_ProgressBar_Sprite_Info.Height);
	m_pProgressBar_Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pProgressBar_Sprite->SetTransform(&matR);
	m_pProgressBar_Sprite->Draw(m_pProgressBar_Texture,
		&m_rcProgressBar,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(
		wid,
		hei - 80,
		0
		),
		D3DCOLOR_XRGB(255, 255, 255));
	m_pProgressBar_Sprite->End();

	//HP�� 
	float hpWidth = m_HP_ImgInfo.Width* ((float)m_nHp / (float)m_nHpMax);
	SetRect(&m_rcHP, 0, 0, hpWidth, m_HP_ImgInfo.Height);
	m_pHP_Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pHP_Sprite->SetTransform(&matR);
	m_pHP_Sprite->Draw(m_pHP_Texture,
		&m_rcHP,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(
		wid + 83,
		hei - 76,
		0),
		D3DCOLOR_XRGB(255, 255, 255));
	m_pHP_Sprite->End();

	//MP�� 
	float mpWidth = m_MP_ImgInfo.Width* ((float)m_nMp / (float)m_nMpMax);
	SetRect(&m_rcMP, 0, 0, mpWidth, m_MP_ImgInfo.Height);
	m_pMP_Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pMP_Sprite->SetTransform(&matR);
	m_pMP_Sprite->Draw(m_pMP_Texture,
		&m_rcMP,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(
		wid + 83,
		hei - 54,
		0),
		D3DCOLOR_XRGB(255, 255, 255));
	m_pMP_Sprite->End();


	if (!m_bBossMeet)
	{
		//ųī���� ����
		SetRect(&m_rcKcBoard, 0, 0, m_KcBoard_ImgInfo.Width, m_KcBoard_ImgInfo.Height);
		m_pKcBoard_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		m_pKcBoard_sprite->SetTransform(&matR);
		m_pKcBoard_sprite->Draw(m_pKcBoard_Texture,
			&m_rcKcBoard,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(m_rcKcBoard.left + 460, m_rcKcBoard.top + 15, 0),
			D3DCOLOR_XRGB(255, 255, 255));
		m_pKcBoard_sprite->End();

		m_nKillNum = 32;
		Cut_KillNum_Img();

		//1�ڸ� 
		SetRect(&m_rcKcNumber, m_nKillNumOne_x, 0, m_nKillNumOne_w, m_KcNumber_ImgInfo.Height - 5);
		m_pkcNumber_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		m_pkcNumber_sprite->SetTransform(&matR);
		m_pkcNumber_sprite->Draw(m_pkcNumber_Texture,
			&m_rcKcNumber,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(m_rcKcNumber.left + 720 - (m_nKillNumOne_w), m_rcKcNumber.top + 20, 0),
			D3DCOLOR_XRGB(255, 255, 255));
		m_pkcNumber_sprite->End();

		//2�ڸ� 
		SetRect(&m_rcKcNumber, m_nKillNumTen_x, 0, m_nKillNumTen_w, m_KcNumber_ImgInfo.Height - 5);
		m_pkcNumber_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		m_pkcNumber_sprite->SetTransform(&matR);
		m_pkcNumber_sprite->Draw(m_pkcNumber_Texture,
			&m_rcKcNumber,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(m_rcKcNumber.left + 690 - (m_nKillNumTen_w), m_rcKcNumber.top + 20, 0),
			D3DCOLOR_XRGB(255, 255, 255));
		m_pkcNumber_sprite->End();

		//3�ڸ� 
		SetRect(&m_rcKcNumber, m_nKillNumHun_x, 0, m_nKillNumHun_w, m_KcNumber_ImgInfo.Height - 5);
		m_pkcNumber_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		m_pkcNumber_sprite->SetTransform(&matR);
		m_pkcNumber_sprite->Draw(m_pkcNumber_Texture,
			&m_rcKcNumber,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(m_rcKcNumber.left + 660 - (m_nKillNumHun_w), m_rcKcNumber.top + 20, 0),
			D3DCOLOR_XRGB(255, 255, 255));
		m_pkcNumber_sprite->End();

		//4�ڸ�
		SetRect(&m_rcKcNumber, m_nKillNumTho_x, 0, m_nKillNumTho_w, m_KcNumber_ImgInfo.Height - 5);
		m_pkcNumber_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		m_pkcNumber_sprite->SetTransform(&matR);
		m_pkcNumber_sprite->Draw(m_pkcNumber_Texture,
			&m_rcKcNumber,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(m_rcKcNumber.left + 625 - (m_nKillNumTho_w), m_rcKcNumber.top + 20, 0),
			D3DCOLOR_XRGB(255, 255, 255));
		m_pkcNumber_sprite->End();
	}


}

void cPlayerUI::Cut_KillNum_Img()
{
	//ųī���� ���� // 
	//4 (x=0,w=50), 0 (x=50,w=100), 1 (x=100,w=150), 2 (x=140,w=180),  
	//3 (x=180,w=220), 5 (x=222,w=262), 6 (x=265,w=305), 7 (x=307,w=347), 
	//8 (x=349,w=389), 9 (x=391,w=435), 
	
	//1�ڸ�
	m_nKillNumOne = m_nKillNum % 10;
	m_nKillNumTen = m_nKillNum / 10;
	m_nKillNumHun = m_nKillNum / 100;
	m_nKillNumTho = m_nKillNum / 1000;

	if (m_nKillNumOne == 0)
	{
		m_nKillNumOne_x = 50;
		m_nKillNumOne_w = 100;
	}
	else if (m_nKillNumOne == 1)
	{
		m_nKillNumOne_x = 100;
		m_nKillNumOne_w = 138;
	}
	else if (m_nKillNumOne == 2)
	{
		m_nKillNumOne_x = 137;
		m_nKillNumOne_w = 177;
	}
	else if (m_nKillNumOne == 3)
	{
		m_nKillNumOne_x = 180;
		m_nKillNumOne_w = 220;
	}
	else if (m_nKillNumOne == 4)
	{
		m_nKillNumOne_x = 0;
		m_nKillNumOne_w = 50;
	}
	else if (m_nKillNumOne == 5)
	{
		m_nKillNumOne_x = 222;
		m_nKillNumOne_w = 262;
	}
	else if (m_nKillNumOne == 6)
	{
		m_nKillNumOne_x = 265;
		m_nKillNumOne_w = 305;
	}
	else if (m_nKillNumOne == 7)
	{
		m_nKillNumOne_x = 307;
		m_nKillNumOne_w = 347;
	}
	else if (m_nKillNumOne == 8)
	{
		m_nKillNumOne_x = 349;
		m_nKillNumOne_w = 389;
	}
	else if (m_nKillNumOne == 9)
	{
		m_nKillNumOne_x = 391;
		m_nKillNumOne_w = 435;
	}

	//2�ڸ�
	if (m_nKillNumTen == 0)
	{
		m_nKillNumTen_x = 50;
		m_nKillNumTen_w = 100;
	}
	else if (m_nKillNumTen == 1)
	{
		m_nKillNumTen_x = 100;
		m_nKillNumTen_w = 138;
	}
	else if (m_nKillNumTen == 2)
	{
		m_nKillNumTen_x = 140;
		m_nKillNumTen_w = 180;
	}
	else if (m_nKillNumTen == 3)
	{
		m_nKillNumTen_x = 180;
		m_nKillNumTen_w = 220;
	}
	else if (m_nKillNumTen == 4)
	{
		m_nKillNumTen_x = 0;
		m_nKillNumTen_w = 50;
	}
	else if (m_nKillNumTen == 5)
	{
		m_nKillNumTen_x = 222;
		m_nKillNumTen_w = 262;
	}
	else if (m_nKillNumTen == 6)
	{
		m_nKillNumTen_x = 265;
		m_nKillNumTen_w = 305;
	}
	else if (m_nKillNumTen == 7)
	{
		m_nKillNumTen_x = 307;
		m_nKillNumTen_w = 347;
	}
	else if (m_nKillNumTen == 8)
	{
		m_nKillNumTen_x = 349;
		m_nKillNumTen_w = 389;
	}
	else if (m_nKillNumTen == 9)
	{
		m_nKillNumTen_x = 391;
	 	m_nKillNumTen_w = 435;
	}

	//3�ڸ�
	if (m_nKillNumHun == 0)
	{
		m_nKillNumHun_x = 50;
		m_nKillNumHun_w = 100;
	}
	else if (m_nKillNumHun == 1)
	{
		m_nKillNumHun_x = 100;
		m_nKillNumHun_w = 150;
	}
	else if (m_nKillNumHun == 2)
	{
		m_nKillNumHun_x = 140;
		m_nKillNumHun_w = 180;
	}
	else if (m_nKillNumHun == 3)
	{
		m_nKillNumHun_x = 180;
		m_nKillNumHun_w = 220;
	}
	else if (m_nKillNumHun == 4)
	{
		m_nKillNumHun_x = 0;
		m_nKillNumHun_w = 50;
	}
	else if (m_nKillNumHun == 5)
	{
		m_nKillNumTho_x = 222;
		m_nKillNumHun_w = 262;
	}
	else if (m_nKillNumHun == 6)
	{
		m_nKillNumHun_x = 265;
		m_nKillNumHun_w = 305;
	}
	else if (m_nKillNumHun == 7)
	{
		m_nKillNumHun_x = 307;
		m_nKillNumHun_w = 347;
	}
	else if (m_nKillNumHun == 8)
	{
		m_nKillNumHun_x = 349;
		m_nKillNumHun_w = 389;
	}
	else if (m_nKillNumHun == 9)
	{
		m_nKillNumHun_x = 391;
		m_nKillNumHun_w = 435;
	}

	//4�ڸ�
	if (m_nKillNumTho == 0)
	{
		m_nKillNumTho_x = 50;
		m_nKillNumTho_w = 100;
	}
	else if (m_nKillNumTho == 1)
	{
		m_nKillNumTho_x = 100;
		m_nKillNumTho_w = 150;
	}
	else if (m_nKillNumTho == 2)
	{
		m_nKillNumTho_x = 140;
		m_nKillNumTho_w = 180;
	}
	else if (m_nKillNumTho == 3)
	{
		m_nKillNumTho_x = 180;
		m_nKillNumTho_w = 220;
	}
	else if (m_nKillNumTho == 4)
	{
		m_nKillNumTho_x = 0;
		m_nKillNumTho_w = 50;
	}
	else if (m_nKillNumTho == 5)
	{
		m_nKillNumTho_x = 222;
		m_nKillNumTho_w = 262;
	}
	else if (m_nKillNumTho == 6)
	{
		m_nKillNumTho_x = 265;
		m_nKillNumTho_w = 305;
	}
	else if (m_nKillNumTho == 7)
	{
		m_nKillNumTho_x = 307;
		m_nKillNumTho_w = 347;
	}
	else if (m_nKillNumTho == 8)
	{
		m_nKillNumTho_x = 349;
		m_nKillNumTho_w = 389;
	}
	else if (m_nKillNumTho == 9)
	{
		m_nKillNumTho_x = 391;
		m_nKillNumTho_w = 435;
	}
}
