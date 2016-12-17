#pragma once

class cCamera;
class cMeshMap;

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

	enum tagState
	{
		Combo1,
		Combo2,
		Combo3,
		Combo4,
		Dash,
		Wait,
		Rapid1,
		Rapid2,
		Rapid3
	};


	std::vector<cBaseObject*>			renderObjects;			//오브젝트 배열
	cBaseObject*						rootObject;				//루트
	std::vector<cLight*>				lights;					//라이팅..

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

	//cTransform*							m_pRootTrans;
	cTransform*							m_pNeckTrans;
	cTransform*							m_pHairTrans;
	cTransform*							m_pTailTrans;
	cTransform*							m_pRWeaponTrans;
	cTransform*							m_pLWeaponTrans;

	bool								m_bAttack;
	tagState							m_tState;

public:
	cTransform*							m_pRootTrans;
	cTransform*							m_pBottomTrans;

	float								m_fHP;
	float								m_fMaxHP;

	cCharacter();
	~cCharacter();

	void Setup(string PathBody, string PathFace, string PathHair, string PathTail, string PathRWeapon, string PathLWeapon);
	void Setup(string PathBody, string PathFace, string PathHair, string PathTail, string PathRWeapon, string PathLWeapon, D3DXMATRIXA16* mat);
	
	void Update(D3DXVECTOR3 worldPos);
	void Update(D3DXVECTOR3 worldPos, float timDelta, cMeshMap* _Map);
	void Render(cLight_Direction* pDirLight);


	//Getter/Setter
	void SetWorldPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetWorldPosition();

	std::vector<cBaseObject*> GetBaseObject()
	{
		return renderObjects;
	}
	bool GetIsAttack()
	{
		return m_bAttack;
	}

private:

	void CharPlaySound(int n);
	
};

