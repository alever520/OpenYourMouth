#include"readwav.h"
#include"recognize.h"
#include <iostream>
#include<string>
#include"wavelet.h"

using namespace std;
int main()
{
	//readwav read("test2.wav");
	//int length = read.getlength();// data���ݵĳ��ȣ����ļ���data���ֵ�һ��
	//int freq = read.getfrequency();// wav�ļ��Ĳ���Ƶ��
	//double T = 0.02; // �������任�Ĳ������� ��Ƶ�ʼ��Ϊ1/T
	//double* data = read.disp();

	//recognize(data, T, freq, length);
	//dft_disp(data, T, freq, length);
	//time_piece(data, T, freq, length);
	//cout << "------------------" << endl;
	//for (int i = 0; i < 10; i++)
	//{
	//	cout << out[i] << endl;
	//}
	double srcdata[] = { 420.2,423.53,423.52,423.35,424.52,428,430.79,428.92 };
	//double* outdata = new double[7];
	double* det = new double[5];
	double* app = new double[5];
	wavelet a;
	a.wavedec(srcdata, 8, det, app);
	double* outdata = new double[8];
	a.waverec(det, app, 5, outdata);
	for (int i = 0; i < 8; i++)
	{
		cout << "outdata: " << outdata[i];
	}

	//for (int i = 0; i < 7; i++)
	//	cout << outdata[i] << endl;
	
	system("pause");
	//delete[] outdata;
}