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

	void InitParticle(string _Name, string _TexturePath, D3DXVECTOR3 _StartPos, D3DXVECTOR3 _EndPos);
	void InitQuadParticle(string _Name, string _TexturePath, D3DXVECTOR3 _StartPos, D3DXVECTOR3 _EndPos);

	void Update(float _TimeDelta);
	void Render();

	void Start();
	void Stop();
};

