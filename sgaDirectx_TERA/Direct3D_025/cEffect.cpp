#include "stdafx.h"
#include "cEffect.h"




cEffect::cEffect()
	: m_Particle(NULL)
	, m_QuadParticle(NULL)
{
	 
}

cEffect::~cEffect()
{
	m_Particle->Release();
	m_QuadParticle->Release();
}



void cEffect::InitParticle(string _Name, string _TexturePath, D3DXVECTOR3 _StartPos, D3DXVECTOR3 _EndPos)
{
	m_Name = _Name;

	m_Particle = new cPartcleEmitter;
	m_Particle->SetActive(true);

	VEC_COLOR c;
	c.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	c.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	VEC_SCALE s;
	s.push_back(1.0f);
	s.push_back(10.0f);
	
	m_Particle->Init(
		20,
		1.0f,
		2.f,
		3.f,
		_StartPos,
		_EndPos,
		D3DXVECTOR3(0, 0.5, 0),
		D3DXVECTOR3(0, 0.8, 0),
		c, s,
		1.0f, 3.0f,
		RESOURCE_TEXTURE->GetResource(_TexturePath),
		true
		);

	//m_Particle->StartEmission();
}

void cEffect::InitQuadParticle(string _Name, string _TexturePath, D3DXVECTOR3 _StartPos, D3DXVECTOR3 _EndPos)
{
	m_Name = _Name;

	m_QuadParticle = new cQuadParticleEmitter;
	m_QuadParticle->SetActive(true);

	VEC_COLOR c;
	c.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	c.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	VEC_SCALE s;
	s.push_back(1.0f);
	s.push_back(10.0f);

	m_QuadParticle->Init(
		20,
		10.0f,
		3.5f,
		4.0f,
		_StartPos,
		_EndPos,
		D3DXVECTOR3(0, 0.5, 0),
		D3DXVECTOR3(0, 0.8, 0),
		D3DXVECTOR3(-90 * ONE_RAD, 0, 90 * ONE_RAD),		//�ʱ���۽� ȸ��Min
		D3DXVECTOR3(-90 * ONE_RAD, 0, 0),     //�ʱ���۽� ȸ��Max
		D3DXVECTOR3(0, 0, 0.5),				//�ʴ� ȸ���� ȸ�� �� Min
		D3DXVECTOR3(0, 0, 0.5),				//�ʴ� ȸ���� ȭ�� �� Max
		D3DXVECTOR3(0, 0, 1),				//�ʴ� ȸ�� ���� Min
		D3DXVECTOR3(0, 0, 2),				//�ʴ� ȸ�� ���� Max
		c, s,
		1.0f, 3.0f,
		RESOURCE_TEXTURE->GetResource(_TexturePath),
		true);

	//m_QuadParticle->StartEmission();
}

void cEffect::Update(float _TimeDelta)
{
	if (m_isQuad)
		m_QuadParticle->Update(_TimeDelta);
	else
		m_Particle->Update(_TimeDelta);
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
		m_Particle->StartEmission();

}

void cEffect::Stop()
{
	if (m_isQuad)
		m_QuadParticle->StopEmission();
	else
		m_Particle->StopEmission();

}






//HRESULT cEffect::PushParticle(string name, D3DXVECTOR3 startPos, D3DXVECTOR3 endPos, float size, string texturePath)
//{
//	//�̸����� �ߺ��� ��� ����
//	if (m_Names.find(name) != m_Names.end())
//		return E_FAIL;
//
//	m_Names.insert(name);
//
//	
//
//
//
//
//	return S_OK;
//}
//
//HRESULT cEffect::PushQuadParticle(string name, D3DXVECTOR3 startPos, D3DXVECTOR3 endPos, float size, string texturePath)
//{
//	//�̸����� �ߺ��� ��� ����
//	if (m_Names.find(name) != m_Names.end())
//		return E_FAIL;
//
//	m_Names.insert(name);
//	cQuadParticleEmitter* c = new cQuadParticleEmitter();
//	c->SetActive(true);
//
//	VEC_COLOR colors;
//	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
//
//	VEC_SCALE scales;
//	scales.push_back(1.0f);
//	scales.push_back(5.0f);
//
//	c->Init(
//		100,
//		10.0f,
//		3.5f,
//		4.0f,
//		startPos,
//		endPos,
//		D3DXVECTOR3(0, 0.5, 0),
//		D3DXVECTOR3(0, 0.8, 0),
//		D3DXVECTOR3(-90 * ONE_RAD, 0, 90 * ONE_RAD),		//�ʱ���۽� ȸ��Min
//		D3DXVECTOR3(-90 * ONE_RAD, 0, 0),     //�ʱ���۽� ȸ��Max
//		D3DXVECTOR3(0, 0, 0.5),				//�ʴ� ȸ���� ȸ�� �� Min
//		D3DXVECTOR3(0, 0, 0.5),				//�ʴ� ȸ���� ȭ�� �� Max
//		D3DXVECTOR3(0, 0, 1),				//�ʴ� ȸ�� ���� Min
//		D3DXVECTOR3(0, 0, 2),				//�ʴ� ȸ�� ���� Max
//		colors, scales,
//		size, size,
//		RESOURCE_TEXTURE->GetResource(texturePath),
//		true);
//
//	c->StartEmission();
//	m_mapQuadParticle.insert(pair<string, cQuadParticleEmitter*>(name, c));
//
//	return S_OK;
//}
//
//void cEffect::Update(float deltaTime)
//{
//
//}
//
//void cEffect::Render(vector<string> renderList)
//{
//	//RenderList������
//
//	vector<string> PartList;
//	vector<string> QuadList;
//
//	for each(auto s in renderList)
//	{
//		if (m_mapParticle.find(s) != m_mapParticle.end()) {
//			PartList.push_back(s);
//		}
//
//		if (m_mapQuadParticle.find(s) != m_mapQuadParticle.end()) {
//			QuadList.push_back(s);
//		}
//	}
//
//
//	//��������....
//
//}
