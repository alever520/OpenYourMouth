#include "wavelet.h"
void wavelet(double* srcdata, double* outdata, int dataLen)
{
	int filterLen = 4; // �˲�������


    //  д���˲���
	double filter_HD[4] = { -0.12941, 0.22414, 0.83652, 0.48296 };// �ֽ� ��ͨ���� DET
	double filter_LD[4] = { -0.48296,0.83652,-0.22414,-0.12941 }; // �ֽ� ��ͨ���� APP
	double filter_HR[4] = { -0.12941,-0.22414,0.83652,-0.48296 }; // �ع� ��ͨ���� DET
	double filter_LR[4] = { 0.48296,0.83652,0.22414,-0.12941 };   // �ع� ��ͨ���� APP


	int exLen = dataLen + 2*filterLen - 2;  // ���غ�ĳ���
	// �Գ����غ������
	double* temp = new double[exLen];   //  ��ʱ���غ������
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
	int convLen = exLen - filterLen + 1; // ����ÿ��������������ĳ���
	double* pre_det = new double[convLen];  // ������ϸ�ڣ���ͨ������
	double* pre_app = new double[convLen];  // ��������������ͨ������
	for (int i = 0; i < convLen; i++)
	{
		// ������ݳ�ʼ��
		pre_det[i] = 0.0;  //  ��ͨ����
		pre_app[i] = 0.0;  //  ��ͨ����
		for (int j = filterLen-1,k=0; j >= 0; j--,k++)
		{
			pre_det[i] += filter_HD[j] * temp[i + k];  //   ���ͨ�˲��������
			pre_app[i] += filter_LD[j] * temp[i + k];  //   ���ͨ�˲��������
		}
	}
	delete[] temp;    //  �ͷ���ʱ���غ������


	//  ���²���
	int detLen = convLen / 2;   //  �������ϸ�ڳ���
	double* det = new double[convLen / 2];  //  ������������ϸ�ڲ���
	double* app = new double[convLen / 2];  //  ��������������������
	for (int i = 1, j = 0; i < convLen; i += 2, j++)
	{
		det[j] = pre_det[i];
		app[j] = pre_app[i];
	}
	delete[] pre_app;   //  �ͷſռ�
	delete[] pre_det;



	//  ��ȡ��ֵ
	double sigma = 0.0;  //  ��ʼ��sigmaֵ
	if ( detLen% 2 == 0)    //  ż������
	{
		double &temp1 = det[detLen / 2 - 1];
		double &temp2 = det[detLen / 2];
		//  ��Ϊǰ��ε����ֵ
		for (int i = 0; i < detLen/2; i++)
		{
			if (temp1 > temp2)
				exchange(temp1, temp2);
			if(det[i]>temp1 && det[i]<temp2)
				exchange(det[i], temp1);
			if ( det[i] > temp2)
				exchange(det[i], temp2);
		}
		//  ��Ϊ���ε���Сֵ
		for (int i = detLen / 2 + 1; i < detLen; i++)
		{
			if (det[i] < temp1)
				exchange(temp1, det[i]);
			if (det[i] > temp1 && det[i] < temp2)
				exchange(temp2,det[i]);
		}
		sigma = (temp1 + temp2) / 2;
	}
	else   //  ��������
	{
		double &temp = det[detLen / 2];
		for (int i = 0; i < detLen / 2; i++)
		{
			if (det[i] > temp)
				exchange(det[i], temp);
		}
		for (int i = detLen / 2 + 1; i < detLen; i++)
		{
			if (det[i] < temp)
				exchange(temp, det[i]);
		}
		sigma = temp;
	}
	//  ������ֵ T
	double T = sigma*sqrt(2 * log(detLen));
	//  ʹ����ֵ����
	for (int i = 0; i < detLen; i++)
	{
		if (det[i] < T)
			det[i] = 0.0;
	}
	//  ׼���ع�
	int upLen = detLen * 2 + 1;  //  �ϲ�����ĳ���
	double* up_det = new double[upLen];
	double* up_app = new double[upLen];
	//  �ϲ���
	for (int i = 0; i < detLen; i++)
	{
		up_det[2 * i] = 0.0;
		up_det[2 * i + 1] = det[i];
		up_app[2 * i] = 0.0;
		up_app[2 * i + 1] = app[i];
	}
	up_det[2 * detLen] = up_app[2 * detLen] = 0.0; //  ĩλ����
	//  ����
	int up_exLen = upLen + 2 * filterLen - 2;  //  ���غ�����鳤��
	double* up_exdet = new double[up_exLen];   //  ���غ��det����
	double* up_exapp = new double[up_exLen];   //  ���غ��app����
	for (int i = 0; i < up_exLen; i++)
	{
		if (i < filterLen - 1)
		{
			up_exdet[i] = up_det[filterLen - 1 - i - 1];
			up_exapp[i] = up_app[filterLen - 1 - i - 1];
		}
			
		else if (i >= filterLen - 1 && i < up_exLen - filterLen + 1)
		{
			up_exdet[i] = up_det[i - 3];
			up_exapp[i] = up_app[i - 3];
		}
			
		else
		{
			up_exdet[i] = up_det[upLen - (i - upLen - filterLen + 1) - 1];
			up_exapp[i] = up_app[upLen - (i - upLen - filterLen + 1) - 1];
		}
	}
	delete[] up_det;
	delete[] up_app;
	//  �����
	int aftLen = up_exLen - filterLen + 1;  //   �����ĳ���
	double* aft_det = new double[aftLen];     //  ������det����
	double* aft_app = new double[aftLen];     //  ������app����
	//double* recdata = new double[aftLen];   //   �ع��������
	for (int i = 0; i < aftLen; i++)
	{
		// ������ݳ�ʼ��
		aft_det[i] = 0.0;  //  ��ͨ����
		aft_app[i] = 0.0;  //  ��ͨ����
		for (int j = filterLen - 1, k = 0; j >= 0; j--, k++)
		{
			aft_det[i] += filter_HR[j] * up_exdet[i + k];  //   ���ͨ�˲��������
			aft_app[i] += filter_LR[j] * up_exapp[i + k];  //   ���ͨ�˲��������
		}
		outdata[i] = aft_det[i] + aft_app[i];  //  ��ͨ���ͨ��������ع�
	}
	delete[] up_exdet;
	delete[] up_exapp;
	delete[] aft_det;
	delete[] aft_app;

}
void exchange(double &a, double &b)
{
	double temp;
	temp = a;
	a = b;
	b = temp;
}