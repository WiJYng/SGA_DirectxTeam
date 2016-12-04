#pragma once

class cCamera;

class cCharacter
{
private:
	std::vector<cBaseObject*>			renderObjects;			//������Ʈ �迭
	cBaseObject*						rootObject;				//��Ʈ

	//cBody*		m_pBody;
	//cFace*		m_pFace;
	//cHair*		m_pHair;
	//cTail*		m_pTail;
	//cWeapon*		m_pLWeapon;
	//cWeapon*		m_pRWeapon;

public:
	cCharacter();
	~cCharacter();

	void Setup(string PathBody, string PathFace, string PathHair, string PathTail);
	void Update(D3DXVECTOR3 worldPos);
	void Render();
	
	
	//Getter/Setter
	void SetWorldPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetWorldPosition();



	//D3DXMATRIX * GetRootBone() { return m_pBody->GetRootTM(); }
	//bool GetAniEnd(int _index) { return m_pBody->GetAniEnd(_index); }
	//float GetAniTime() { return m_pBody->GetAniTime(); }
};
