#include "wavelet.h"
void wavelet(double* srcdata, int dataLen, double* outdata)
{
	int filterLen = 4; // 滤波器长度
    //  写出滤波器
	double filter_H[4] = { -0.12941, 0.22414, 0.83652, 0.48296 };// 高通部分 DET
	double filter_L[4] = { -0.48296,0.83652,-0.22414,-0.12941 };// 低通部分 APP
	int exLen = dataLen + 2*filterLen - 2;  // 延拓后的长度
	// 对称延拓后的数据
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
	//  做卷积
	int outLen = (dataLen + filterLen - 1)/2; // 这是每个部分做完卷积后的长度
	for (int i = 0; i < outLen; i++)
	{
		// 输出数据初始化
		outdata[i] = 0.0;  //  高通部分
		outdata[i + outLen] = 0.0;  //  低通部分 
		for (int j = filterLen-1,k=0; j >= 0; j--,k++)
		{
			outdata[i] += filter_H[j] * temp[i + k];  //   与高通滤波器做卷积
			outdata[i + outLen] += filter_L[j] * temp[i + k]; //   与低通滤波器做卷积
		}
	}
	//  提取阈值
	double sigma = 0.0;  //  初始化sigma值
	if (outLen % 2 == 0)    //  偶数长度
	{
		double &temp1 = outdata[outLen / 2 - 1];
		double &temp2 = outdata[outLen / 2];
		for (int i = 0; i < outLen/2; i++)
		{
			if (temp1 > temp2)
				exchange(temp1, temp2);
			if(outdata[i]>temp1 && outdata[i]<temp2)
				exchange(outdata[i], temp1);
			if ( outdata[i] > temp2)
				exchange(outdata[i], temp2);
		}
		for (int i = outLen / 2 + 1; i < outLen; i++)
		{
			if (outdata[i] < temp1)
				exchange(temp1, outdata[i]);
			if (outdata[i] > temp1 && outdata[i] < temp2)
				exchange(temp2,outdata[i]);
		}
		sigma = (temp1 + temp2) / 2;
	}
	else   //  奇数长度
	{
		double &temp = outdata[outLen / 2];
		for (int i = 0; i < outLen / 2; i++)
		{
			if (outdata[i] > temp)
				exchange(outdata[i], temp);
		}
		for (int i = outLen / 2 + 1; i < outLen; i++)
		{
			if (outdata[i] < temp)
				exchange(temp, outdata[i]);
		}
		sigma = temp;
	}
	//  计算阈值 T
	double T = sigma*sqrt(2 * log(outLen));
	//  使用阈值函数
	for (int i = 0; i < outLen; i++)
	{
		if (outdata[i] < T)
			outdata[i] = 0.0;
	}



}
void exchange(double &a, double &b)
{
	double temp;
	temp = a;
	a = b;
	b = temp;
}