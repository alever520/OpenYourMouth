#include"recognize.h"
#include<iostream>
using namespace std;

// ��ԭʼ���ݲ��� �������T ��ÿ����������Ϊn = T*freq
//�任���ִ���Ϊ L = length / n ��ͳ��ǰ m = 3000 * T ��ֵ��Ϊ�Ƚ�
// 3000Ϊ��ֵ
void recognize(double* data, double T, int freq, int length)
{
	int n = T*freq; // ÿ�α任�ĵ���
	int L = length / n; //�任���ִ��� Ҳ����Ҫ��dft��Ƭ����
	int m = 3000 * T;
	for (int i = 0; i < L; i++)
	{
		double* data_test = new double[n];
		for (int j = 0; j < n; j++)
		{
			data_test[j] = data[j + i*n];
			//cout << data_test[i] << endl;	
		}
		// ע���� new ����Ŀռ�һ��Ҫ��ʼ��
		//double* out = new double[n];
		//memset(out, 0, sizeof(double) * n);
		cout << "time: " << T*i << "s ";
		if (my_dft(data_test, n, m) && time_piece(data_test, n))
			cout << "type: 1 " << endl;
		else
			cout << "type: 0" << endl;
		delete[] data_test;
		data_test = NULL;
	}
}



