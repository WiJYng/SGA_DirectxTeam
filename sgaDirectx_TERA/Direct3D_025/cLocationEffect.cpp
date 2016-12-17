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

}

void cLocationEffect::PlayEffect(EFFECT_NAME _Name, D3DXVECTOR3 pos)
{
	for (int i = 0; i < 5; i++)
	{
		D3DXMATRIXA16 mat;
		D3DXMatrixIdentity(&mat);

		cXMesh_Static* m = RESOURCE_STATICXMESH->GetResource("./Tera/Effect/E_SYLINDER.X", mat);


		//m_vecMesh
	}
}
