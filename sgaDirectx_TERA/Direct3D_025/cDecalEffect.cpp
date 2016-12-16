#include "stdafx.h"
#include "cDecalEffect.h"
#include "cMeshMap.h"


cDecalEffect::cDecalEffect()
	: pDecalEffect(NULL)
{
	eDecal = DECAL_BASE;
	pDecalEffect = RESOURCE_FX->GetResource("./Tera/Effect/base_texture.fx");
	fTime = 0;
}


cDecalEffect::~cDecalEffect()
{
	SAFE_RELEASE(pDecalEffect);
}


void cDecalEffect::GenerateDecal(D3DXVECTOR3 pos, float r, LPD3DXMESH m)
{
	vecDecalVertex.clear();
	//D3DXVECTOR3 p0 = D3DXVECTOR3(pos.x - r, 0, pos.z - r);
	//D3DXVECTOR3 p1 = D3DXVECTOR3(pos.x - r, 0, pos.z + r);
	//D3DXVECTOR3 p2 = D3DXVECTOR3(pos.x + r, 0, pos.z + r);
	//D3DXVECTOR3 p3 = D3DXVECTOR3(pos.x + r, 0, pos.z - r);

	





	/*

	p0.y = map->GetHeight(p0.x, p0.z);
	p1.y = map->GetHeight(p1.x, p0.z);
	p2.y = map->GetHeight(p2.x, p0.z);
	p3.y = map->GetHeight(p3.x, p0.z);

	vecDecalVertex.push_back(ST_PT_VERTEX(p0, D3DXVECTOR2(0, 0)));
	vecDecalVertex.push_back(ST_PT_VERTEX(p1, D3DXVECTOR2(0, 1)));
	vecDecalVertex.push_back(ST_PT_VERTEX(p2, D3DXVECTOR2(1, 1)));
	vecDecalVertex.push_back(ST_PT_VERTEX(p0, D3DXVECTOR2(0, 0)));
	vecDecalVertex.push_back(ST_PT_VERTEX(p2, D3DXVECTOR2(1, 1)));
	vecDecalVertex.push_back(ST_PT_VERTEX(p3, D3DXVECTOR2(1, 0)));*/
}

void cDecalEffect::Update()
{
	fTime++;

	if (fTime > 100)
		fTime = 0;
}

void cDecalEffect::Render()
{
	if (vecDecalVertex.size() <= 0) return;

	if (pDecalEffect == NULL)
		SetEffect(DECAL_BASE);

	D3DXMATRIXA16 matWorld, matView, matProjection;
	D3DXMatrixIdentity(&matWorld);
	Device->GetTransform(D3DTS_VIEW, &matView);
	Device->GetTransform(D3DTS_PROJECTION, &matProjection);

	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	UINT numPasses = 0;

	switch (eDecal)
	{
	case DECAL_BASE:
		pDecalEffect->SetMatrix("matWorld", &matWorld);
		pDecalEffect->SetMatrix("matView", &matView);
		pDecalEffect->SetMatrix("matProj", &matProjection);

		pDecalEffect->SetTexture("DiffuseMap_Tex", RESOURCE_TEXTURE->GetResource("./Tera/Effect/MagicArray001_Tex.tga"));
		Device->SetFVF(ST_PT_VERTEX::FVF);

		pDecalEffect->Begin(&numPasses, NULL);

		for (UINT i = 0; i < numPasses; ++i)
		{
			pDecalEffect->BeginPass(i);

			Device->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
				vecDecalVertex.size() / 3,
				&vecDecalVertex[0],
				sizeof(ST_PT_VERTEX));

			pDecalEffect->EndPass();
		}

		pDecalEffect->End();

		break;
	}

	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

void cDecalEffect::SetEffect(E_DECALEFFECT e)
{
	eDecal = e;
	switch (e)
	{
	case DECAL_BASE :
		pDecalEffect = RESOURCE_FX->GetResource("./Tera/Effect/base_texture.fx");
		break;
	}
}
