#include<iostream>
using namespace std;

// ��ʱ��������������ų�һЩ�����ϵ�����
bool time_piece(double* data, int n)
{
	double enegy = 0;
	for (int i = 0; i < n; i++)
	{
		enegy += abs(data[i]);
	}
	cout << "enegy:" << enegy;
	if (enegy > 200)
		return true;
	else
		return false;
	
}