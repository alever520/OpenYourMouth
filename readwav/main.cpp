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
	double srcdata[] = { 3.21,3.31,3.41,3.51,3.61,3.71,3.81 };
	double* outdata = new double[7];
	wavelet(srcdata, outdata, 7);
	for (int i = 0; i < 7; i++)
		cout << outdata[i] << ' ';
	system("pause");

}