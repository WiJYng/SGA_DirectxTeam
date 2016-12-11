#include "stdafx.h"
#include "cMeshMap.h"
#include "cXMesh_Static.h"


cMeshMap::cMeshMap()
{
}


cMeshMap::~cMeshMap()
{
	SAFE_RELEASE(pDecalEffect);

}


void cMeshMap::Setup(string PathMap)
{
	D3DXMATRIXA16 matCorrection;
	D3DXMatrixIdentity(&matCorrection);

	//Map
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 0, -20, 0);
	//D3DXMatrixRotationY(&matT, 180.0f * ONE_RAD);
	matCorrection = matT;

	Setup(PathMap, &matCorrection);
}

void cMeshMap::Setup(string PathMap, D3DXMATRIXA16* mat)
{
	cXMesh_Static* mesh = RESOURCE_STATICXMESH->GetResource(PathMap, mat);
	mesh->SetTechniqueName("StaticMesh2.fx");
	//m_pTerrainEffect = RESOURCE_FX->GetResource( "./Resources/Shaders/TerrainBase.fx");
	
	pMap = new cBaseObject();
	pMap->SetMesh(mesh);
	pMap->SetActive(true);
	pMap->IgnoreCreateShadow = false;		//�׸��� �ȱ׸���.
	pMap->ApplyShadow = true;

	//effect
	pDecalEffect = RESOURCE_FX->GetResource("./Tera/Effect/decal_shader.fx");

	//RenderToTerrian();
}

void cMeshMap::Render()
{
	if (pMap)
	{
		//pMap->Render();
		D3DXMATRIXA16 matWorld, matView, matProj;
		D3DXMatrixIdentity(&matWorld);
		Device->GetTransform(D3DTS_VIEW, &matView);
		Device->GetTransform(D3DTS_PROJECTION, &matProj);
		
		pDecalEffect->SetMatrix("matWorld", &matWorld);
		pDecalEffect->SetMatrix("matView", &matView);
		pDecalEffect->SetMatrix("matProjection", &matProj);
		//MagicArray001_Tex.tga
		LPDIRECT3DTEXTURE9 tex = RESOURCE_TEXTURE->GetResource("./Tera/Effect/MagicArray001_Tex.tga"); 
		pDecalEffect->SetTexture("Diffuse_Tex", tex);
		
		pDecalEffect->SetFloat("fRange", 3.0f);
		D3DXVECTOR4 vPos[2];
		vPos[0] = D3DXVECTOR4(1, 3, 0, 1);
		vPos[1] = D3DXVECTOR4(0, 3, 1, 1);
		pDecalEffect->SetVectorArray("vPos", vPos, 2);
		
		UINT numPasses = 0;
		pDecalEffect->Begin(&numPasses, NULL);
		
		for (UINT i = 0; i < numPasses; ++i)
		{
			pDecalEffect->BeginPass(i);
			
			//((cXMesh_Static*)pMap->pMesh)->GetMesh()->DrawSubset(0);
		
			//(cXMesh_Static*)(pMap->pMesh)
			pMap->Render();
			//pMap->pMesh->Render(pMap->pTransform);
			
			pDecalEffect->EndPass();
		}
		
		pDecalEffect->End();
	}
}

float cMeshMap::GetHeight(float x, float z)
{
	float result = 0;
	float buffer = 99999;

	LPRay vR = new Ray;
	vR->origin = D3DXVECTOR3(x, buffer, z);
	vR->direction = D3DXVECTOR3(0, -1, 0);

	cXMesh_Static* m = (cXMesh_Static*)pMap->pMesh;
	

	float d;
	BOOL isHit;
	D3DXIntersect(m->GetMesh(), &vR->origin, &vR->direction, &isHit, NULL, NULL, NULL, &d, NULL, NULL);

	if (isHit)
		result = buffer - d;

	return result;
}


void cMeshMap::RenderToTerrian()
{
	float minX, minZ, minY, maxX, maxZ, maxY;

	cXMesh_Static* m = (cXMesh_Static*)pMap->pMesh;
	DWORD verNum = m->GetMesh()->GetNumVertices();
	vecToTerrian.reserve(verNum);

	//���� Element �� ��� ���� ������ ����
	D3DVERTEXELEMENT9 pVerElement[MAX_FVF_DECL_SIZE];
	DWORD verSize = D3DXGetFVFVertexSize(m->GetMesh()->GetFVF());

	void* p = NULL;
	m->GetMesh()->LockVertexBuffer(0, &p);

	for (DWORD i = 0; i < verNum; i++){
		//���ؽ� ���� �ּ�
		char* pVertex = ((char*)p + (i * verSize));
		D3DXVECTOR3* pos = (D3DXVECTOR3*)(pVertex);
		
		vecToTerrian.push_back(*pos);

		if (i == 0)
		{
			minX = pos->x;
			minZ = pos->z;
			maxX = pos->x;
			maxZ = pos->z;
			minY = pos->y;
			maxY = pos->y;
		}
		else {
			if (minX > pos->x)
				minX = pos->x;
			
			if (maxX < pos->x)
				maxX = pos->x;

			if (minZ > pos->z)
				minZ = pos->z;
			
			if (maxZ < pos->z)
				maxZ = pos->z;

			if (minY > pos->y)
				minY = pos->y;

			if (maxY < pos->y)
				maxY = pos->y;
		}
	}

	int xLen = floor(maxX - minX);
	int zLen = floor(maxZ - minZ);
	int yLen = floor(maxY - minY);

	float buffer = xLen / 256.f;	
	float calYBuffer = yLen / 256.f;
	
	FILE* f = NULL;
	f = fopen("./Tera/Map/matTest/MAP_EXPORT.raw", "wb");
	char data[256][256];

	int iIdx = 0;
	int jIdx = 0;

	for (float i = minX + buffer / 2; i < maxX - buffer; i += buffer)
	{
		jIdx = 0;
		for (float j = minZ + buffer / 2; j < maxZ - buffer; j += buffer) {
			data[iIdx][jIdx] = { '\0' };

			float yBuffer = 99999   ;
			LPRay vR = new Ray;
			vR->origin = D3DXVECTOR3(i, yBuffer, j);
			vR->direction = D3DXVECTOR3(0, -1, 0);

			cXMesh_Static* m = (cXMesh_Static*)pMap->pMesh;


			float d, res;
			BOOL isHit;
			D3DXIntersect(m->GetMesh(), &vR->origin, &vR->direction, &isHit, NULL, NULL, NULL, &d, NULL, NULL);

			if (isHit)
				res = yBuffer - d;

			int idx = 0;
			if (iIdx == 165 && jIdx == 85)
			{
				int a = 0;
			}

			for (float k = minY; k <= maxY; k += calYBuffer)
			{
				if (res >= k && res < k + calYBuffer)
					break;

				idx++;
			}
			data[iIdx][jIdx] = idx;
			jIdx++;
		}
		iIdx++;
	}

	fwrite(&data, 1, (256*256), f);
	fclose(f);
}