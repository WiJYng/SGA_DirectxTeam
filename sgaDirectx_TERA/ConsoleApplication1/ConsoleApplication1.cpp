// ConsoleApplication1.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"


int swap(int &ref1, int &ref2)
{
	int temp = ref1;
	ref1 =ref2;
	ref2 = temp;
	int tt= temp*3;
	return tt;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int val1 = 30 ;
	int val2 = 60;
	int tt = swap(val1,val2);

	cout << "val1 : " << val1<<endl;
	cout << "val2 : " << val2 << endl;
	cout << tt<<endl;
	return 0;
}

