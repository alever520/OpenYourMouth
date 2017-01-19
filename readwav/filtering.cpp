#include "filtering.h"
void wavelet(double* srcdata, int dataLen, double* outdata)
{
	int filterLen = 4; // �˲�������
	int exLen = dataLen + 2*filterLen - 2;  // ���غ�ĳ���
	double* temp = new double[exLen];
	//  ���Գ�����
	for (int i = 0; i < exLen; i++)
	{
		if (i < filterLen - 1)
			temp[i] = srcdata[filterLen - 1 - i - 1];
		else if (i >= filterLen - 1 && i < exLen - filterLen + 1)
			temp[i] = srcdata[i-3];
		else
			temp[i] = srcdata[dataLen-(i-dataLen-filterLen+1)-1];

	}
	//  д���˲���
	double* filter_H = new double[filterLen]; // ��ͨ����
	double* filter_L = new double[filterLen]; // ��ͨ����
	//  �����
	int outLen = (dataLen + filterLen - 1)/2; // ����ÿ��������������ĳ���
	for (int i = 0; i < outLen; i++)
	{
		outdata[i] = 0.0;
		outdata[i + outLen] = 0.0; // ������ݳ�ʼ��
		for (int j = 0; j < filterLen; j++)
		{

		}
	}


}