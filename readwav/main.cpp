#include"readwav.h"
#include"recognize.h"
#include <iostream>
#include<string>
#include"wavelet.h"

using namespace std;
int main()
{
	//readwav read("test2.wav");
	//int length = read.getlength();// data数据的长度，是文件内data部分的一半
	//int freq = read.getfrequency();// wav文件的采样频率
	//double T = 0.02; // 给出做变换的采样周期 则频率间隔为1/T
	//double* data = read.disp();

	//recognize(data, T, freq, length);
	//dft_disp(data, T, freq, length);
	//time_piece(data, T, freq, length);
	//cout << "------------------" << endl;
	//for (int i = 0; i < 10; i++)
	//{
	//	cout << out[i] << endl;
	//}
	readwav clc("7577.wav");
	int length = 1000;
	//int length = clc.getlength();
	double* srcdata = clc.disp();
	//double srcdata[] = { 420.2,423.53,423.52,423.35,424.52,428,430.79,428.92 };
	double* det = new double[(length + 4 - 1) / 2];
	double* app = new double[(length + 4 - 1) / 2];
	wavelet a;
	a.wavedec(srcdata, length, det, app);
	double* outdata = new double[length];
	a.wavecle(det, (length + 4 - 1) / 2);
	//cout << a.getT(det, 5) << endl;
	a.waverec(det, app, (length + 4 - 1) / 2, outdata);
	cout << "outdata: ";
	for (int i = 0; i < length; i++)
	{
		cout << outdata[i] << endl;
	}

	//for (int i = 0; i < 7; i++)
	//	cout << outdata[i] << endl;
	
	system("pause");
	//delete[] outdata;
}