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
		// ���֡��������
		sum += t;
		// ���֡��ǰm����������� ��Ӧ��Ƶ��Ϊm*50hz  1/T��hz��
		if (i <= m)
			count += t;
		if (t > peak)
		{
			peak = t;
			loc = i;
		}

	}
	
	//cout << "sum:" << sum << "  count:" << count;
	cout << "  ��ֵ:" << count / sum;
	delete[] temp;
	temp = NULL;
	if (count / sum > 0.8&& loc>20&& loc <= m)
		return true;
	else
		return false;
	
}