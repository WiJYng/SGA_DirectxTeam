#pragma once
//test¡÷ºÆ 
#include "cProgressBar_Monster.h"

class cProgressBar_sMonster : public cProgressBar_Monster
{
public:
	cProgressBar_sMonster();
	~cProgressBar_sMonster();

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

