#include "stdafx.h"
#include "cTickFunc.h"

cTickFunc::cTickFunc()
{
	countTime = 0.f;
	start = false;
}

cTickFunc::~cTickFunc()
{

}

void cTickFunc::init(float tick)
{
	tickTime = tick;
}

void cTickFunc::tickUpdate(float timeDelta)
{
	//ó�� �Լ� �������� ī��Ʈ �ǰڱ� ��.
	if (start == true)
	{
		if (countTime < tickTime)
		{
			countTime += timeDelta;  // �ð� ���� ���.
			//hit = false;
		}
		else if (countTime >= tickTime)
		{
			countTime = 0.f; // 
			start = false;
			//hit = true;
		}
	}
}

bool cTickFunc::tickStart()
{
	if (start == false)  // false�� �ʱⰪ
	{
		start = true;
		//hit = true;
		return true;
	}
	return false;
}

