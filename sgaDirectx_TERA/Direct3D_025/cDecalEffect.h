#pragma once

class cMeshMap;

class cDecalEffect
{
private:
	LPD3DXEFFECT				pDecalEffect;

	std::vector<ST_PT_VERTEX>	vecDecalVertex;

	E_DECALEFFECT				eDecal;
	float						fTime;


public:
	void GenerateDecal(D3DXVECTOR3 pos, float r, LPD3DXMESH m);
	void Update();
	void Render();

	void SetEffect(E_DECALEFFECT e);

	cDecalEffect();
	~cDecalEffect();


	LPD3DXEFFECT LoadEffect(const char* szFileName);
};

