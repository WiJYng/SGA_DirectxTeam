#pragma once
#include "clight.h"

class cLight_Direction : public cLight
{
public:
	float				minRange;			//���� �ּҰŸ� 
	float				maxRange;			//���� �ִ�Ÿ�
	float				distancePow;		//�Ÿ� ������

public:
	cLight_Direction(void);
	~cLight_Direction(void);

	virtual D3DXMATRIXA16 GetLightMatrix();

	virtual void RenderGizmo();

};

