#include "wavelet.h"
using namespace std;
void wavelet::wavedec(double* srcdata, int dataLen,double* det,double* app)
{
	int filterLen = 4; // 滤波器长度


					   //  写出滤波器
	double filter_LD[4] = { -0.12941, 0.22414, 0.83652, 0.48296 };// 分解 高通部分 DET
	double filter_HD[4] = { -0.48296,0.83652,-0.22414,-0.12941 }; // 分解 低通部分 APP


	int exLen = dataLen + 2 * filterLen - 2;  // 延拓后的长度
											  // 对称延拓后的数据
	double* exdata = new double[exLen];   //  临时延拓后的数组
										  //  做对称延拓
	for (int i = 0; i < exLen; i++)
	{
		if (i < filterLen - 1)
			exdata[i] = srcdata[filterLen - 1 - i - 1];
		else if (i >= filterLen - 1 && i < exLen - filterLen + 1)
			exdata[i] = srcdata[i - 3];
		else
			exdata[i] = srcdata[dataLen - (i - dataLen - filterLen + 1) - 1];

	}


	//  做卷积
	int convLen = exLen - filterLen + 1; // 这是每个部分做完卷积后的长度
	double* pre_det = new double[convLen];  // 卷积后的细节（高通）数组
	double* pre_app = new double[convLen];  // 卷积后的轮廓（低通）数组
	for (int i = 0; i < convLen; i++)
	{
		// 输出数据初始化
		pre_det[i] = 0.0;  //  高通部分
		pre_app[i] = 0.0;  //  低通部分
		for (int j = filterLen - 1, k = 0; j >= 0; j--, k++)
		{
			pre_det[i] += filter_HD[j] * exdata[i + k];  //   与高通滤波器做卷积
			pre_app[i] += filter_LD[j] * exdata[i + k];  //   与低通滤波器做卷积
		}
	}
	delete[] exdata;    //  释放临时延拓后的数组


						//  向下采样
	int detLen = convLen / 2;   //  采样后的细节长度
	for (int i = 1, j = 0; i < convLen; i += 2, j++)
	{
		det[j] = pre_det[i];
		app[j] = pre_app[i];
	}
	delete[] pre_app;   //  释放空间
	delete[] pre_det;
	
}
void wavelet::waverec(double* det, double* app, int n,double* outdata)
{
	int filterLen = 4; // 滤波器长度

	//  写出滤波器
	double filter_HR[4] = { -0.12941,-0.22414,0.83652,-0.48296 }; // 重构 高通部分 DET
	double filter_LR[4] = { 0.48296,0.83652,0.22414,-0.12941 };   // 重构 低通部分 APP


	//  准备重构
	int upLen = n * 2 + 1;  //  上采样后的长度
	double* up_det = new double[upLen];
	double* up_app = new double[upLen];
	//  上采样
	for (int i = 0; i < n; i++)
	{
		up_det[2 * i] = 0.0;
		up_det[2 * i + 1] = det[i];
		up_app[2 * i] = 0.0;
		up_app[2 * i + 1] = app[i];
	}
	up_det[2 * n] = up_app[2 * n] = 0.0; //  末位置零
	//-----------------输出测试--------------
	//cout << "up_det: ";
	//for (int i = 0; i < upLen; i++)
	//{
	//	cout << up_det[i]<<" ";
	//}
	//cout << endl;


	//  延拓
	int exLen = upLen + 2 * filterLen - 2;  //  延拓后的数组长度
	double* exdet = new double[exLen];   //  延拓后的det数组
	double* exapp = new double[exLen];   //  延拓后的app数组
	for (int i = 0; i < exLen; i++)
	{
		if (i < filterLen - 1)
		{
			exdet[i] = up_det[filterLen - 1 - i - 1];
			exapp[i] = up_app[filterLen - 1 - i - 1];
		}

		else if (i >= filterLen - 1 && i < exLen - filterLen + 1)
		{
			exdet[i] = up_det[i - 3];
			exapp[i] = up_app[i - 3];
		}

		else
		{
			exdet[i] = up_det[upLen - (i - upLen - filterLen + 1) - 1];
			exapp[i] = up_app[upLen - (i - upLen - filterLen + 1) - 1];
		}
	}
	//-----------------输出测试--------------
	//cout << "exdet: ";
	//for (int i = 0; i < exLen; i++)
	//{
	//	cout << exdet[i] << " ";
	//}
	//cout << endl;
	delete[] up_det;
	delete[] up_app;
	//  做卷积
	int aftLen = exLen - filterLen + 1;  //   卷积后的长度
	double* aft_det = new double[aftLen];     //  卷积后的det部分
	double* aft_app = new double[aftLen];     //  卷积后的app部分
											  //double* recdata = new double[aftLen];   //   重构后的数据
	for (int i = filterLen-1,j=0; i < aftLen-filterLen+1; i++)
	{
		// 输出数据初始化
		aft_det[i] = 0.0;  //  高通部分
		aft_app[i] = 0.0;  //  低通部分
		for (int j = filterLen - 1, k = 0; j >= 0; j--, k++)
		{
			aft_det[i] += filter_HR[j] * exdet[i + k];  //   与高通滤波器做卷积
			aft_app[i] += filter_LR[j] * exapp[i + k];  //   与低通滤波器做卷积
		}
		//cout << aft_det[i] << " " << aft_app[i] << endl;
		outdata[j++] = aft_det[i] + aft_app[i];  //  高通与低通部分相加重构
	}
	delete[] exdet;
	delete[] exapp;
	delete[] aft_det;
	delete[] aft_app;

}
double wavelet::getT(double* det, int detLen)
{
	//  提取阈值
	double sigma = 0.0;  //  初始化sigma值
    //-----------------输出测试--------------
	//cout << "abs(det): ";
	//for (int i = 0; i < detLen; i++)
	//{
	//	if (det[i] < 0)
	//		det[i] = -det[i];
	//	cout << det[i]<<" ";
	//}
	//cout << endl;
	if (detLen % 2 == 0)    //  偶数长度
	{
		double &temp1 = det[detLen / 2 - 1];
		double &temp2 = det[detLen / 2];
		//  成为前半段的最大值
		for (int i = 0; i < detLen / 2; i++)
		{
			if (abs(temp1) > abs(temp2))
				exchange(temp1, temp2);
			if (det[i]>temp1 && det[i]<temp2)
				exchange(det[i], temp1);
			if (det[i] > temp2)
				exchange(det[i], temp2);
		}
		//  成为后半段的最小值
		for (int i = detLen / 2 + 1; i < detLen; i++)
		{
			if (det[i] < temp1)
				exchange(temp1, det[i]);
			if (det[i] > temp1 && det[i] < temp2)
				exchange(temp2, det[i]);
		}
		sigma = (temp1 + temp2) / 2;
	}
	else   //  奇数长度
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
	cout << "sigma: " << sigma << endl;
	//  计算阈值 T
	double T = sigma*sqrt(2 * log(detLen));
	return T;
}
void wavelet::wavecle(double* det, int detLen)
{
	double T = getT(det, detLen);
	//  使用阈值函数
	for (int i = 0; i < detLen; i++)
	{
		if (det[i] < T)
			det[i] = 0.0;
	}
}
void exchange(double &a, double &b)
{
	double temp;
	temp = a;
	a = b;
	b = temp;
}