#pragma once

class cBaseObject;

class cMeshMap
{
private:
	cBaseObject*		pMap;

public:
	cMeshMap();
	~cMeshMap();

	void Setup(string PathMap);
	void Setup(string PathMap, D3DXMATRIXA16* mat);
	
	void Render();
	
	//Getter/Setter
	float GetHeight(float x, float z);
};

