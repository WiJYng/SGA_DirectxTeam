#include "stdafx.h"
#include "cEffect.h"




cEffect::cEffect()
	: m_Particle(NULL)
	, m_QuadParticle(NULL)
{
	m_QuadParticle = new cQuadParticleEmitter;
	m_Particle = new cPartcleEmitter;
}

cEffect::~cEffect()
{
	m_Particle->Release();
	m_QuadParticle->Release();
}


void cEffect::Update(float _TimeDelta)
{
	m_QuadParticle->pTransform->DefaultControl2(_TimeDelta);
	m_Particle->pTransform->DefaultControl2(_TimeDelta);


	//if (m_isQuad)
	//	m_QuadParticle->Update(_TimeDelta);
	//else
	//	m_Particle->Update(_TimeDelta);

}

void cEffect::Render()
{
	if (m_isQuad)
		m_QuadParticle->Render();
	else
		m_Particle->Render();

}


void cEffect::Start()
{
	if (m_isQuad)
		m_QuadParticle->StartEmission();
	else
	{
		//m_Particle->StartEmission();
		m_Particle->Burst(100, 1.4f, 2.7f, 0.1f, 0.5f);

	}
		

}

void cEffect::Stop()
{
	if (m_isQuad)
		m_QuadParticle->StopEmission();
	else
		m_Particle->StopEmission();

}