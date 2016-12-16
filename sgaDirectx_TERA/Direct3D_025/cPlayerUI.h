#pragma once
//test주석 
class cPlayerUI
{
private:
	int						m_nQuestNum;
	bool					m_bBossMeet;
	bool					m_bQWindowCenter_firstCheck;
	bool					m_bQwindowCenter_On;
	bool					m_bQwindowRight_On;
	bool					m_bKeyWindow_On;


	//키설명창
	LPD3DXSPRITE			m_pKeyWindow_Sprite;
	LPDIRECT3DTEXTURE9		m_pKeyWindow_Texture;
	D3DXIMAGE_INFO			m_KeyWindow_Sprite_Info;
	RECT					m_rcKeyWindow;

	//중앙퀘스트창
	LPD3DXSPRITE			m_pQwindowCenter_Sprite;
	LPDIRECT3DTEXTURE9		m_pQwindowCenter_Texture;
	D3DXIMAGE_INFO			m_QwindowCenter_Sprite_Info;
	RECT					m_rcQwindowCenter;


	//오른쪽퀘스트창
	LPD3DXSPRITE			m_pQwindowRight_Sprite;
	LPDIRECT3DTEXTURE9		m_pQwindowRight_Texture;
	D3DXIMAGE_INFO			m_QwindowRight_Sprite_Info;
	LPD3DXSPRITE			m_pQwindowRight_Sprite2;
	LPDIRECT3DTEXTURE9		m_pQwindowRight_Texture2;
	D3DXIMAGE_INFO			m_QwindowRight_Sprite_Info2;
	RECT					m_rcQwindowRight;
	RECT					m_rcQwindowRightMove;
	bool					m_bQWindowRightClick;


	//프로그레스바 바탕
	LPD3DXSPRITE			m_pProgressBar_Sprite;
	LPDIRECT3DTEXTURE9		m_pProgressBar_Texture;
	D3DXIMAGE_INFO			m_ProgressBar_Sprite_Info;
	RECT					m_rcProgressBar;

	//체력바, MP (게이지바)
	LPD3DXSPRITE			m_pHP_Sprite;
	LPD3DXSPRITE			m_pMP_Sprite;	

	LPDIRECT3DTEXTURE9		m_pHP_Texture;
	LPDIRECT3DTEXTURE9		m_pMP_Texture;

	D3DXIMAGE_INFO			m_HP_ImgInfo;
	D3DXIMAGE_INFO			m_MP_ImgInfo;

	RECT					m_rcHP;
	RECT					m_rcMP;


	//킬카운터
	bool					m_bKillCounterOff;
	LPD3DXSPRITE			m_pKcBoard_sprite; //kill counter
	LPD3DXSPRITE			m_pkcNumber_sprite;

	LPDIRECT3DTEXTURE9		m_pKcBoard_Texture;
	LPDIRECT3DTEXTURE9		m_pkcNumber_Texture;

	D3DXIMAGE_INFO			m_KcBoard_ImgInfo;
	D3DXIMAGE_INFO			m_KcNumber_ImgInfo;

	RECT					m_rcKcBoard;
	RECT					m_rcKcNumber;

	int						m_nHp;
	int						m_nHpMax;
	int						m_nMp;
	int						m_nMpMax;

	int						m_nKillNum;
	int						m_nKillNumTho; //4자리
	int						m_nKillNumHun; //3자리
	int						m_nKillNumTen; //2자리
	int						m_nKillNumOne; //1자리
	int						m_nKillNumTho_x, m_nKillNumTho_w;
	int						m_nKillNumHun_x, m_nKillNumHun_w;
	int						m_nKillNumTen_x, m_nKillNumTen_w;
	int						m_nKillNumOne_x, m_nKillNumOne_w;


public:
	cPlayerUI();
	~cPlayerUI();

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Cut_KillNum_Img();


	void SetHp(int value){ m_nHp = value; }
	int GetHp(){ return m_nHp; }
	void SetHpMax(int value){ m_nHpMax = value; }
	int GetHpMax(){ return m_nHpMax; }

	void SetMp(int value){ m_nMp = value; }
	int GetMp(){ return m_nMp; }
	void SetMpMax(int value){ m_nMpMax = value; }
	int GetMpMax(){ return m_nMpMax; }

	void SetKillNum(int value){ m_nKillNum = value; }
	int getKillNum(){ return m_nKillNum; }

	void SetBossMeet(bool value){ m_bBossMeet = value; }
	bool GetBossMeet(){ return m_bBossMeet; }


};

