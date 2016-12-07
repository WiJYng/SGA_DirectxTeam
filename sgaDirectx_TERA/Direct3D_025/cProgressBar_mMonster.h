#pragma once
//test¡÷ºÆ 
#include "cProgressBar_Monster.h"

class cProgressBar_mMonster : public cProgressBar_Monster
{
private:

public:
	cProgressBar_mMonster();
	~cProgressBar_mMonster();

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

