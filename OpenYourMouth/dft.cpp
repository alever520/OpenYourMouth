#include "dft.h"
#include<math.h>
#include<iostream>
using namespace std;
//-----------dft------------
//****in为输入数据 out为输出数据
//****n 为输入数据长度   m为参与判断的点的个数
bool my_dft(double* in, int n, int m)
{
	double sum = 0; // 记录一次dft的总幅值
	double count = 0; // 记录前m个点的和
	double type = 0;  // 记录比值 作为判断标准
	my_complex* temp = new my_complex[n/2];
	memset(temp, 0, sizeof(my_complex)*(n/2));
	//hamming(in, n);
	double peak = 0.0;
	int loc = 0;
	for (int i = 0; i < n/2; i++)
	{
		for (int j = 0; j < n; j++)
		{
			temp[i].re += in[j] * cos(i*j*2.0*PI / n);
			temp[i].im += -in[j] * sin(i*j*2.0*PI / n);
		}
		int t = sqrt(temp[i].re*temp[i].re + temp[i].im*temp[i].im);
		// 求此帧的能量和
		sum += t;
		// 求此帧的前m个点的能量和 对应的频率为m*50hz  1/T的hz数
		if (i <= m)
			count += t;
		if (t > peak)
		{
			peak = t;
			loc = i;
		}

	}
	
	//cout << "sum:" << sum << "  count:" << count;
	cout << "  比值:" << count / sum;
	delete[] temp;
	temp = NULL;
	if (count / sum > 0.8&& loc>20&& loc <= m)
		return true;
	else
		return false;
	
}