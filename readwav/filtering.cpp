#include "filtering.h"
void wavelet(double* srcdata, int dataLen, double* outdata)
{
	int filterLen = 4; // 滤波器长度
	int exLen = dataLen + 2*filterLen - 2;  // 延拓后的长度
	double* temp = new double[exLen];
	//  做对称延拓
	for (int i = 0; i < exLen; i++)
	{
		if (i < filterLen - 1)
			temp[i] = srcdata[filterLen - 1 - i - 1];
		else if (i >= filterLen - 1 && i < exLen - filterLen + 1)
			temp[i] = srcdata[i-3];
		else
			temp[i] = srcdata[dataLen-(i-dataLen-filterLen+1)-1];

	}
	//  写出滤波器
	double* filter_H = new double[filterLen]; // 高通部分
	double* filter_L = new double[filterLen]; // 低通部分
	//  做卷积
	int outLen = (dataLen + filterLen - 1)/2; // 这是每个部分做完卷积后的长度
	for (int i = 0; i < outLen; i++)
	{
		outdata[i] = 0.0;
		outdata[i + outLen] = 0.0; // 输出数据初始化
		for (int j = 0; j < filterLen; j++)
		{

		}
	}


}