#include"recognize.h"
#include<iostream>
using namespace std;

// 对原始数据采样 采样间隔T ，每个样本点数为n = T*freq
//变换的轮次数为 L = length / n ，统计前 m = 3000 * T 的值作为比较
// 3000为阈值
void recognize(double* data, double T, int freq, int length)
{
	int n = T*freq; // 每次变换的点数
	int L = length / n; //变换的轮次数 也就是要做dft的片段数
	int m = 3000 * T;
	for (int i = 0; i < L; i++)
	{
		double* data_test = new double[n];
		for (int j = 0; j < n; j++)
		{
			data_test[j] = data[j + i*n];
			//cout << data_test[i] << endl;	
		}
		// 注意用 new 构造的空间一定要初始化
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



