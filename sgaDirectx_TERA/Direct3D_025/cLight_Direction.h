#pragma once
#include "clight.h"

class cLight_Direction : public cLight
{
public:
	float				minRange;			//빛의 최소거리 
	float				maxRange;			//빛의 최대거리
	float				distancePow;		//거리 감쇠율

public:
	cLight_Direction(void);
	~cLight_Direction(void);

	virtual D3DXMATRIXA16 GetLightMatrix();

	virtual void RenderGizmo();

};

