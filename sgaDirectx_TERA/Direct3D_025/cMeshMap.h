#pragma once

class cBaseObject;

class cMeshMap
{
private:
	cBaseObject*		pMap;
	LPD3DXEFFECT		pDecalEffect;
	
	
	vector<D3DXVECTOR3> vecToTerrian;

public :
	D3DXVECTOR3			pCharPosition;
public:
	cMeshMap();
	~cMeshMap();

	void Setup(string PathMap);
	void Setup(string PathMap, D3DXMATRIXA16* mat);
	
	void Render();
	
	//Getter/Setter
	float GetHeight(float x, float z);

private:
	void RenderToTerrian();
};

