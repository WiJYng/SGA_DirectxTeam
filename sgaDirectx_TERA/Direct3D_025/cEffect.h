#pragma once
#include "cPartcleEmitter.h"
#include "cQuadParticleEmitter.h"


class cEffect
{
public :
	string							m_Name;
	cPartcleEmitter*				m_Particle;
	cQuadParticleEmitter*			m_QuadParticle;
	bool							m_isQuad;

public:
	cEffect();
	~cEffect();

	void Update(float _TimeDelta);
	void Render();
	
	void Start();
	void Stop();
};

