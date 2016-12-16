#pragma once
//test주석 
class cPartcleEmitter;

class cProgressBar_Monster
{
protected:
	cPartcleEmitter*		m_ptProgressBar;

	//프로그레스바 바탕
	LPD3DXSPRITE			m_pProgressBar_Sprite;
	LPDIRECT3DTEXTURE9		m_pProgressBar_Texture;
	D3DXIMAGE_INFO			m_ProgressBar_Sprite_Info;
	RECT					m_rcProgressBar;

	//체력바
	LPD3DXSPRITE			m_pHP_Sprite; //loadingBar front
	LPDIRECT3DTEXTURE9		m_pHP_Texture;
	D3DXIMAGE_INFO			m_HP_ImgInfo;

	RECT					m_rcHP;

	int						m_nHp;
	int						m_nHpMax;
	bool					m_bDeath; 

	//위치
	float					m_fX;
	float					m_fY;





public:
	cProgressBar_Monster();
	~cProgressBar_Monster();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void SetHp(float value){ m_nHp = value; }
	float GetHp(){ return m_nHp; }

	void SetHpMax(float value){ m_nHpMax = value; }
	float GetHpMax(){ return m_nHpMax; }

	void SetX(float value){ m_fX = value; }
	float GetX(){ return m_fX; }

	void SetY(float value){ m_fY = value; }
	float GetY(){ return m_fY; }

	void SetIsDeath(bool value){ m_bDeath = value; }
	float GetIsDeath(){ return m_bDeath; }

};

