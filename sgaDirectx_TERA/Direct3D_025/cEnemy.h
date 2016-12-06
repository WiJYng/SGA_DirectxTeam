#pragma once

class cMeshMap;

class cEnemy
{
private:
	std::vector<cBaseObject*>			renderObjects;			//오브젝트 배열

public:
	cEnemy();
	~cEnemy();

	void Setup(string PathBody, string PathFace, string PathHair, string PathTail, string PathRWeapon, string PathLWeapon);
	void Setup(string PathBody, string PathFace, string PathHair, string PathTail, string PathRWeapon, string PathLWeapon, D3DXMATRIXA16* mat);

	void Update(D3DXVECTOR3 worldPos);
	void Update(D3DXVECTOR3 worldPos, float timDelta, cMeshMap* _Map);
	void Render();


	//Getter/Setter
	void SetWorldPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetWorldPosition();

};

