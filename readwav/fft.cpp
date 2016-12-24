#include "fft.h"
#include<iostream>
#include<math.h>
#include<string>
void fft(my_complex* in, int n)
{

	int L = 1; //蝶形运算层数
	while (n = n >> 1)
		L++;
	int len = 1 << L;// 将输入的一维数组对齐为 N=2^L
	int N; // 需要的扩充后的长度
	my_complex* expand = in;// 如果需要 指向扩充后的数组
	if (n * 2 == len)
		L -= 1;
	else if (n < len)
	{
		N = len; // 需要的扩充后的长度
		expand = new my_complex[N]; // 扩充后的数组
		memset(expand, 0, sizeof(my_complex)*N);
		memcpy(expand, in, sizeof(my_complex)*n);// 把之前数组里的数据复制过来
	}
	my_complex* exchange = new my_complex[N];  // 用作临时交换的数组
	for (int i = 0; i < N; i++)
	{
		int p = 0;
		for (int j = 0; j < L; j++)
			if (i&(1 << j))
				p += 1 << (L - j - 1);
		exchange[i] = expand[p];
	}
	memcpy(expand, exchange, sizeof(double)*N);// 将交换后的数据复制到expand中
	delete[]exchange;
	exchange = NULL;
	//------旋转因子----------------
	my_complex* W = new my_complex[N / 2];
	memset(W, 0, sizeof(my_complex)*N / 2);// 给出旋转因子数组 并置0
	for (int i = 0; i < N / 2; i++)
		W[i] = my_complex(cos(-2.0*3.1415926*i / N), sin(-2.0*3.1415926*i / N));
	//--------FFT算法--------------
	my_complex* out_temp = new my_complex[N]; //构建与补零后长度相同的临时输出数组
	for (int i = 0; i < L; i++) // 蝶形运算层数
	{
		int G = 1 << (L - i);
		int num = 1 << i; // 每组元素个数
		for (int j = 0; j<num; j++)
			for (int k = 0; k < G; k++) //每层的组数
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
	//my_complex* out = new my_complex[n]; // 构建与输入数组一样长的输出数组
	//memset(out, 0, sizeof(my_complex)*n);
	//memcpy(out, out_temp, sizeof(my_complex)*n); // 复制前n项到输出数组
	//delete[]expand;
	//delete[]W;
	//delete[]out_temp;
	//return out_temp;


}