#include "StdAfx.h"
#include "cLight_Direction.h"
#include "cTransform.h"

cLight_Direction::cLight_Direction(void)
{
	this->distancePow = 1.0f;
}

cLight_Direction::~cLight_Direction(void)
{
}

D3DXMATRIXA16 cLight_Direction::GetLightMatrix()
{
	// 라이트 행렬
	// Pos.x,         Pos.y,          Pos.z,         lightType ( 0 Direction, 1 Point, 2 Spot )
	// Dir.x,         Dir.y,          Dir.z,         DistancePow;
	// Color.r,       Color.g,        Color.b,       strength
	// MaxRange,      MinRange,       InAngle        OutAngle 

	D3DXMATRIXA16 matLight;
	D3DXMatrixIdentity( &matLight );
	matLight._14 = 0;		//Directional Light Type

	D3DXVECTOR3 forward = /*D3DXVECTOR3(-5.0f, -5.0f, 0.0f);*/this->pTransform->GetForward();
	forward = D3DXVECTOR3(1, 1, 1);
	memcpy( &matLight._21, &forward, sizeof( D3DXVECTOR3 ) );
	memcpy( &matLight._31, &Color, sizeof( FLOAT ) * 5 ); 
	matLight._34 = this->Intensity;
	//int a = 0;
	//D3DXMATRIXA16 matLight;
	//D3DXMatrixIdentity(&matLight);
	//matLight._14 = 1;		//Point Light Type
	//D3DXVECTOR3 pos = this->pTransform->GetWorldPosition(); /*D3DXVECTOR3(0, 10000, 0);*/
	//memcpy(&matLight._11, &pos, sizeof(D3DXVECTOR3));
	//memcpy(&matLight._31, &Color, sizeof(FLOAT)* 3);
	//Color = D3DXCOLOR(1, 1, 1, 1);
	//matLight._24 = 0;
	//matLight._41 = 10;
	//matLight._42 = 5;
	//matLight._34 = 1.0f;

	//matLight._11 = 0;
	//matLight._12 = 10000;
	//matLight._13 = 0;

	//matLight._41 = 5000;
	//matLight._42 = 0;
	//matLight._43 = 360;
	//matLight._44 = 360;

	return matLight;
}

void cLight_Direction::RenderGizmo()
{
	this->pTransform->RenderGimozo();

}
