#pragma once

class cMeshMap;

class cEnemy
{
private:
	std::vector<cBaseObject*>			renderObjects;			//������Ʈ �迭

public:
	cEnemy();
	~cEnemy();

	void Setup(string PathMonster, D3DXVECTOR3* Pos = NULL);
	void Setup(string PathMonster, D3DXMATRIXA16* mat);

	void Update(D3DXVECTOR3 worldPos);
	void Update(float timDelta, cMeshMap* _Map);
	void Render();


	//Getter/Setter
	void SetWorldPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetWorldPosition();

};

