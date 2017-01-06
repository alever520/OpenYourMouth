#include"readwav.h"
#include"recognize.h"
#include <iostream>
#include<string>

using namespace std;
int main()
{
	readwav read("test3.wav");
	int length = read.getlength();// data数据的长度，是文件内data部分的一半
	int freq = read.getfrequency();// wav文件的采样频率
	double T = 0.02; // 给出做变换的采样周期 则频率间隔为1/T
	double* data = read.disp();

	recognize(data, T, freq, length);
	//dft_disp(data, T, freq, length);
	//time_piece(data, T, freq, length);
	//cout << "------------------" << endl;
	//for (int i = 0; i < 10; i++)
	//{
	//	cout << out[i] << endl;
	//}
	system("pause");

}