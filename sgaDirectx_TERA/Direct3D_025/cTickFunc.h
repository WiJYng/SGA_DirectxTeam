#pragma once

class cTickFunc
{
	float countTime; // ��꿡 ���� ����
	float tickTime;  // ƽ �ð�

	bool start;
	//bool hit;

public:
	cTickFunc();
	~cTickFunc();

	void init(float tick);
	void tickUpdate(float timeDelta);
	bool tickStart();
};

