#include "wavelet.h"
void wavelet(double* srcdata, int dataLen, double* outdata)
{
	int filterLen = 4; // �˲�������
    //  д���˲���
	double filter_H[4] = { -0.12941, 0.22414, 0.83652, 0.48296 };// ��ͨ���� DET
	double filter_L[4] = { -0.48296,0.83652,-0.22414,-0.12941 };// ��ͨ���� APP
	int exLen = dataLen + 2*filterLen - 2;  // ���غ�ĳ���
	// �Գ����غ������
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
	//  �����
	int outLen = (dataLen + filterLen - 1)/2; // ����ÿ��������������ĳ���
	for (int i = 0; i < outLen; i++)
	{
		// ������ݳ�ʼ��
		outdata[i] = 0.0;  //  ��ͨ����
		outdata[i + outLen] = 0.0;  //  ��ͨ���� 
		for (int j = filterLen-1,k=0; j >= 0; j--,k++)
		{
			outdata[i] += filter_H[j] * temp[i + k];  //   ���ͨ�˲��������
			outdata[i + outLen] += filter_L[j] * temp[i + k]; //   ���ͨ�˲��������
		}
	}
	//  ��ȡ��ֵ
	double sigma = 0.0;  //  ��ʼ��sigmaֵ
	if (outLen % 2 == 0)    //  ż������
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
	else   //  ��������
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
	//  ������ֵ T
	double T = sigma*sqrt(2 * log(outLen));
	//  ʹ����ֵ����
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