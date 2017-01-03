#include "dft.h"
#include<math.h>
#include<iostream>
using namespace std;
//-----------dft------------
//****inΪ�������� outΪ�������
//****n Ϊ�������ݳ���   mΪ�����жϵĵ�ĸ���
bool my_dft(double* in, int n, int m)
{
	double sum = 0; // ��¼һ��dft���ܷ�ֵ
	double count = 0; // ��¼ǰm����ĺ�
	double type = 0;  // ��¼��ֵ ��Ϊ�жϱ�׼
	my_complex* temp = new my_complex[n];
	memset(temp, 0, sizeof(my_complex)*n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			temp[i].re += in[j] * cos(i*j*2.0*PI / n);
			temp[i].im += -in[j] * sin(i*j*2.0*PI / n);
		}
		int t = sqrt(temp[i].re*temp[i].re + temp[i].im*temp[i].im);
		// ���֡��������
		sum += t;
		// ���֡��ǰ3000hz��������
		if (i <= m)
			count += t;

	}
	//cout << "sum:" << sum << "  count:" << count;
	//cout << "  ��ֵ:" << count / sum;
	delete[] temp;
	temp = NULL;
	if (count / sum > 0.3)
		return true;
	else
		return false;
	
}