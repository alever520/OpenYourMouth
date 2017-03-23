#include "fft.h"
#include<iostream>
#include<math.h>
#include<string>
void fft(my_complex* in, int n)
{

	int L = 1; //�����������
	while (n = n >> 1)
		L++;
	int len = 1 << L;// �������һά�������Ϊ N=2^L
	int N; // ��Ҫ�������ĳ���
	my_complex* expand = in;// �����Ҫ ָ������������
	if (n * 2 == len)
		L -= 1;
	else if (n < len)
	{
		N = len; // ��Ҫ�������ĳ���
		expand = new my_complex[N]; // ����������
		memset(expand, 0, sizeof(my_complex)*N);
		memcpy(expand, in, sizeof(my_complex)*n);// ��֮ǰ����������ݸ��ƹ���
	}
	my_complex* exchange = new my_complex[N];  // ������ʱ����������
	for (int i = 0; i < N; i++)
	{
		int p = 0;
		for (int j = 0; j < L; j++)
			if (i&(1 << j))
				p += 1 << (L - j - 1);
		exchange[i] = expand[p];
	}
	memcpy(expand, exchange, sizeof(double)*N);// ������������ݸ��Ƶ�expand��
	delete[]exchange;
	exchange = NULL;
	//------��ת����----------------
	my_complex* W = new my_complex[N / 2];
	memset(W, 0, sizeof(my_complex)*N / 2);// ������ת�������� ����0
	for (int i = 0; i < N / 2; i++)
		W[i] = my_complex(cos(-2.0*3.1415926*i / N), sin(-2.0*3.1415926*i / N));
	//--------FFT�㷨--------------
	my_complex* out_temp = new my_complex[N]; //�����벹��󳤶���ͬ����ʱ�������
	for (int i = 0; i < L; i++) // �����������
	{
		int G = 1 << (L - i);
		int num = 1 << i; // ÿ��Ԫ�ظ���
		for (int j = 0; j<num; j++)
			for (int k = 0; k < G; k++) //ÿ�������
			{
				my_complex x1 = expand[k*num + j];
				my_complex x2 = expand[(k + 1)*num + j];
				expand[k*num + j] = x1 + W[j*(1 << (L - i - 1))] * x2;
				expand[(k + 1)*num + j] = x1 - W[j*(1 << (L - i - 1))] * x2;
			}
	}
	if (expand != NULL&&expand != in)
	{
		memcpy(in, expand, sizeof(my_complex)*n);
		delete[] expand;
		expand = NULL;
	}
	if (W != NULL)
	{
		delete[] W;
		W = NULL;
	}
	//my_complex* out = new my_complex[n]; // ��������������һ�������������
	//memset(out, 0, sizeof(my_complex)*n);
	//memcpy(out, out_temp, sizeof(my_complex)*n); // ����ǰn��������
	//delete[]expand;
	//delete[]W;
	//delete[]out_temp;
	//return out_temp;


}