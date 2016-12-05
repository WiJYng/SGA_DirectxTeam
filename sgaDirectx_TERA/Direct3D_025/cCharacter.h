#pragma once

class cCamera;

class cCharacter
{
private:
	enum CHARACTERMESH_PART {
		 P_BODY = 0,
		P_FACE = 1,
		P_HAIR = 2,
		P_TAIL = 3,
		P_RWEAPON = 4,
		P_LWEAPON = 5
	};


	std::vector<cBaseObject*>			renderObjects;			//������Ʈ �迭
	cBaseObject*						rootObject;				//��Ʈ

	//cBody*		m_pBody;
	//cFace*		m_pFace;
	//cHair*		m_pHair;
	//cTail*		m_pTail;
	//cWeapon*		m_pLWeapon;
	//cWeapon*		m_pRWeapon;
	cSkinnedAnimation*					m_pBodyAni;
	cSkinnedAnimation*					m_pFaceAni;
	cSkinnedAnimation*					m_pHairAni;
	cSkinnedAnimation*					m_pTailAni;
	
	cXMesh_Static*						m_pRWeaponMesh;
	cXMesh_Static*						m_pLWeaponMesh;

	cTransform*							m_pSkinnedTrans;
	cTransform*							m_pSkinnedTrans1;
	cTransform*							m_pSkinnedTrans2;
	cTransform*							m_pSkinnedTrans3;
	cTransform*							m_pSkinnedTrans4;
	cTransform*							m_pSkinnedTrans5;

public:
	cCharacter();
	~cCharacter();

	void Setup(string PathBody, string PathFace, string PathHair, string PathTail, string PathRWeapon, string PathLWeapon);
	void Setup(string PathBody, string PathFace, string PathHair, string PathTail, string PathRWeapon, string PathLWeapon, D3DXMATRIXA16* mat);
	
	void Update(D3DXVECTOR3 worldPos);
	void Update(D3DXVECTOR3 worldPos, float timDelta);
	void Render();


	//Getter/Setter
	void SetWorldPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetWorldPosition();

private:
	
};

