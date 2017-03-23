#include<iostream>
using namespace std;

// 从时域的能量方面来排除一些不符合的噪声
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