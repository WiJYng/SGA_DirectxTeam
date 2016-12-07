#pragma once
#include "cPartcleEmitter.h"
#include "cQuadParticleEmitter.h"

class cEffect
{
private:
	vector<cPartcleEmitter*>		m_mapParticle;
	vector<cQuadParticleEmitter*>	m_mapQuadParticle;

	D3DXVECTOR3						m_startPosition;

	bool							m_isStart; 

public:
	cEffect();
	~cEffect();

	//텍스쳐랑, 사이즈, 시작위치, 종료위치 등등 설정
	void PushParticle();
	void PushQuadParticle();
	void Update(float deltaTime);
	void Render();

	void SetPosition();

	void Start();
};

