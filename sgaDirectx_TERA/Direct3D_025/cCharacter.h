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


	std::vector<cBaseObject*>			renderObjects;			//오브젝트 배열
	cBaseObject*						rootObject;				//루트

	D3DXMATRIX							matRootTm;
	D3DXMATRIX							matNeckTm;
	D3DXMATRIX							matHairTm;
	D3DXMATRIX							matTalim;
	D3DXMATRIX							matRWeaponTm;
	D3DXMATRIX							matLWeaponTm;


public:
	cCharacter();
	~cCharacter();

	void Setup(string PathBody, string PathFace, string PathHair, string PathTail, string PathRWeapon, string PathLWeapon);
	void Setup(string PathBody, string PathFace, string PathHair, string PathTail, string PathRWeapon, string PathLWeapon, D3DXMATRIXA16* mat);
	
	void Update(D3DXVECTOR3 worldPos);
	void Render();
	
	
	//Getter/Setter
	void SetWorldPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetWorldPosition();



private:
	void calculateMeshPosition(D3DXMATRIXA16* mat);					//각각의 파츠 위치 맞추기



	//D3DXMATRIX * GetRootBone() { return m_pBody->GetRootTM(); }
	//bool GetAniEnd(int _index) { return m_pBody->GetAniEnd(_index); }
	//float GetAniTime() { return m_pBody->GetAniTime(); }
};

