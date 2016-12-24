#include <iostream>
#include<string>
#include<fstream>
#include<math.h>
#define PI 3.1415926
using namespace std;
class readwav
{
	fstream fp;
	char ChunkID[4];
	unsigned int ChunkSize;
	char Format[4];
	char SubChunk1ID[4];
	unsigned int SubChunk1Size;
	unsigned short AudioFormat;
	unsigned short NumChannels;
	unsigned int SampleRate;
	unsigned int ByteRate;
	unsigned short BlockAlign;
	unsigned short BitsPerSample;
	char SubChunk2ID[4];
	unsigned int SubChunk2Size;
	unsigned char* data;
public:
	readwav(char* filename)
	{
		fp.open(filename, ios::in | ios::binary);
		fp.seekg(0, ios::beg);
		fp.read((char*)&ChunkID, 4);//sizeof(ChunkID)
		fp.seekg(0x04);
		fp.read((char*)&ChunkSize, sizeof(ChunkSize));//sizeof(ChunkSize)
		fp.seekg(0x08);
		fp.read((char*)&Format, 4);//sizeof(Format)
		fp.seekg(0x0c);
		fp.read((char*)&SubChunk1ID, 4);
		fp.seekg(0x10);
		fp.read((char*)&SubChunk1Size, 4);
		fp.seekg(0x14);
		fp.read((char*)&AudioFormat, sizeof(AudioFormat));
		fp.seekg(0x16);
		fp.read((char*)&NumChannels, sizeof(NumChannels));
		fp.seekg(0x18);
		fp.read((char*)&SampleRate, sizeof(SampleRate));
		fp.seekg(0x1c);
		fp.read((char*)&ByteRate, sizeof(ByteRate));
		fp.seekg(0x20);
		fp.read((char*)&BlockAlign, sizeof(BlockAlign));
		fp.seekg(0x22);
		fp.read((char*)&BitsPerSample, sizeof(BitsPerSample));
		fp.seekg(0x24);
		fp.read((char*)&SubChunk2ID, sizeof(SubChunk2ID));
		fp.seekg(0x28);
		fp.read((char*)&SubChunk2Size, sizeof(SubChunk2Size));
		//long length = char2num(SubChunk2Size);
		data = new unsigned char[SubChunk2Size];
		fp.seekg(0x2c);
		fp.read((char*)data, SubChunk2Size);
		
		

		cout << "ChunkID " << ChunkID << endl;
		cout << "ChunkSize " << ChunkSize << endl;
		cout << "Format " << Format << endl;
		cout << "SubChunk1ID " << SubChunk1ID << endl;
		cout << "SubChunk1Size " << SubChunk1Size << endl;
		cout << "AudioFormat " << AudioFormat << endl;
		cout << "NumChannels " << NumChannels << endl;
		cout << "SampleRate " << SampleRate << endl;
		cout << "ByteRate " << ByteRate << endl;
		cout << "BlockAlign " << BlockAlign << endl;
		cout << "BitsPerSample " << BitsPerSample << endl;
		cout << "SubChunk2ID " << SubChunk2ID << endl;
		cout << "SubChunk2Size " << SubChunk2Size << endl;
		//cout << n << endl;
		

	}
	// 数据输出到一块内存空空间
	double* disp()
	{
		//double output = 0;
		double* output = new double[SubChunk2Size / 2];
		int j = 0;
		for (unsigned int i = 0; i < SubChunk2Size; i = i + 2)
		{
			unsigned long data_low = data[i];
			unsigned long data_high = data[i + 1];
			double data_true = data_high * 256 + data_low;
			long data_complement = 0;
			int my_sign = (int)(data_high / 128);
			if (my_sign == 1)
				data_complement = data_true - 65536;
			else
				data_complement = data_true;
			output[j] = (double)(data_complement / (double)32768);
			j++;
			//output = output + final_data;
			//if (i % 1764 == 0)
			//{
			//	ofstream out("test.txt",ios::app);
			//	out << output << endl;
			//	output = 0;
			//}
			
		}
		return output;
	}
	// 给出输出的data的长度
	int getlength()
	{
		return SubChunk2Size/2;
	}
	int getfrequency()
	{
		return SampleRate;
	}
	
};
typedef struct _my_complex
{
	double re;
	double im;
	// 构造函数
	_my_complex(){}
	_my_complex(double a, double b)
	{
		re = a;
		im = b;
	}
}my_complex;
// 重载运算符
//-----------dft------------
//****in为输入数据 out为输出数据
//****n 为输入数据长度   m为参与判断的点的个数
void my_dft(double* in,double* out, int n,int m)
{
	double sum = 0; // 记录一次dft的总幅值
	double count = 0; // 记录前m个点的和
	my_complex* temp = new my_complex[n];
	memset(temp, 0, sizeof(my_complex)*n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			temp[i].re += in[j] * cos(i*j*2.0*PI / n);
			temp[i].im += -in[j] * sin(i*j*2.0*PI / n);
		}
		out[i] = sqrt(temp[i].re*temp[i].re + temp[i].im*temp[i].im);
		sum += out[i];
		if (i <= m)
			count += out[i];
		
	}
	cout << "sum:" << sum << " count:" << count << endl;
	delete[] temp;
	temp = NULL;
}
int main()
{
	readwav read("test3.wav");
	int length = read.getlength();// data数据的长度，是文件内data部分的一半
	int freq = read.getfrequency();// wav文件的采样频率
	double T = 0.02; // 给出做变换的采样周期 则频率间隔为1/T
	int n = T*freq; // 每次变换的点数
	int L = length / n; //变换的轮次数
	int m = 1000 * T;
	double* data = read.disp();
	for (int i = 0; i < L; i++)
	{
		double* data_test = new double[n];
		for (int j = 0; j < n; j++)
		{
			data_test[j] = data[j+i*n];
			//cout << data_test[i] << endl;	
		}
		// 注意用 new 构造的空间一定要初始化
		double* out = new double[n];
		memset(out, 0, sizeof(double) * n);
		my_dft(data_test, out, n, m);
		delete[] data_test;
		data_test = NULL;
		delete[] out;
		out = NULL;
	}
	//cout << "------------------" << endl;
	//for (int i = 0; i < 10; i++)
	//{
	//	cout << out[i] << endl;
	//}
	system("pause");
	
}