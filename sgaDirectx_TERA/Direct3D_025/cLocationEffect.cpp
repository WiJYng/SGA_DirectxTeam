#include "stdafx.h"
#include "cLocationEffect.h"


cLocationEffect::cLocationEffect()
{
}


cLocationEffect::~cLocationEffect()
{
}

void cLocationEffect::Setup()
{

}

void cLocationEffect::Update(float _delta)
{

}

void cLocationEffect::Render()
{
	for each(auto v in m_vecMesh)
	{
		v->Render();
	}
}

void cLocationEffect::PlayEffect(EFFECT_NAME _Name, D3DXVECTOR3 pos)
{

	switch (_Name)
	{
	case LOCATION_ARROW_01:
		LocationEffect(0, pos);
		break;

	case LOCATION_ARROW_02:
		LocationEffect(1, pos);
		break;

	case LOCATION_ARROW_03:
		LocationEffect(2, pos);
		break;

	case LOCATION_ARROW_04:
		LocationEffect(3, pos);
		break;

	case LOCATION_ARROW_BOSS:
		LocationEffect(4, pos);
		break;
	}
}

void cLocationEffect::LocationEffect(int idx, D3DXVECTOR3 pos)
{
	m_vecMesh[idx]->pTransform->SetWorldPosition(pos);
	m_vecMesh[idx]->SetActive(true);
}


void cLocationEffect::InitLocationEffect()
{
	//=================================================
	//	지면표시
	//=================================================
	for (int i = 0; i < 5; i++)
	{
		D3DXMATRIXA16 mat;
		D3DXMatrixIdentity(&mat);

		cXMesh_Static* m = RESOURCE_STATICXMESH->GetResource("./Tera/Effect/E_SYLINDER.X", mat);
		cBaseObject* o = new cBaseObject;
		o->SetMesh(m);
		o->SetActive(false);

		m_vecMesh.push_back(o);
	}
}