#pragma once
#include "cEffect.h"

class cLocationEffect : public cEffect
{
private:
	vector<cBaseObject*>		m_vecMesh;

public:
	cLocationEffect();
	~cLocationEffect();

	void Setup() override;
	void Update(float _delta) override;
	void Render() override;
	void PlayEffect(EFFECT_NAME _Name, D3DXVECTOR3 pos) override;

private:
	void InitLocationEffect();
	void LocationEffect(int idx, D3DXVECTOR3 pos);
};

