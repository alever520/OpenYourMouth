#include"readwav.h"
#include"recognize.h"
#include <iostream>
#include<string>

using namespace std;
int main()
{
	readwav read("test3.wav");
	int length = read.getlength();// data���ݵĳ��ȣ����ļ���data���ֵ�һ��
	int freq = read.getfrequency();// wav�ļ��Ĳ���Ƶ��
	double T = 0.02; // �������任�Ĳ������� ��Ƶ�ʼ��Ϊ1/T
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