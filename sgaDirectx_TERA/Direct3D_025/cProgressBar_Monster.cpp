#include "stdafx.h"
//test¡÷ºÆ 
#include "cProgressBar_Monster.h"


cProgressBar_Monster::cProgressBar_Monster()
: m_pProgressBar_Sprite(NULL)
, m_pProgressBar_Texture(NULL)

, m_pHP_Sprite(NULL)
, m_pHP_Texture(NULL)
{
}
cProgressBar_Monster::~cProgressBar_Monster()
{
	SAFE_DELETE(m_pProgressBar_Sprite);
	SAFE_DELETE(m_pProgressBar_Texture);

	SAFE_DELETE(m_pHP_Sprite);
	SAFE_DELETE(m_pHP_Texture);
}

void cProgressBar_Monster::Setup()
{

}
void cProgressBar_Monster::Update()
{

}
void cProgressBar_Monster::Render()
{

}
void cProgressBar_Monster::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}
