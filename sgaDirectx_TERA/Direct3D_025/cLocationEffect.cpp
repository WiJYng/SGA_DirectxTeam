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
	InitLocationEffect();
}

void cLocationEffect::Update(float _delta)
{

}

void cLocationEffect::Render()
{
	DWORD prevLight;

	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	Device->SetRenderState(D3DRS_ZWRITEENABLE, false);
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_SUBTRACT);
	
	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
	//==============================================================
	
	for each(auto v in m_vecMesh)
	{
		v->Render();
	}

	//==============================================================

	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	Device->SetRenderState(D3DRS_ZWRITEENABLE, true);
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
		//D3DXMatrixScaling(&mat, 0.1, 0.1, 0.1);

		cXMesh_Static* m = RESOURCE_STATICXMESH->GetResource("./Tera/Effect/E_SYLINDER.X", mat);
		cBaseObject* o = new cBaseObject;
		o->SetMesh(m);
		o->SetActive(false);

		m_vecMesh.push_back(o);
	}
}