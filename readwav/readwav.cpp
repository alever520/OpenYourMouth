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
	int frequency()
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
void dft(double* in,my_complex* out, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			out[i].re += in[j] * cos(i*j*2.0*PI / n);
			out[i].im += -in[j] * sin(i*j*2.0*PI / n);
		}
	}
}
my_complex operator +(my_complex &a,my_complex &b)
{
	return _my_complex(a.re + b.re,a.im+ b.im);
}
my_complex operator -(my_complex &a,my_complex &b)
{
	return _my_complex(a.re - b.re,a.im- b.im);
}
my_complex operator *(my_complex &a,my_complex &b)
{
	return _my_complex(a.re*b.re-a.im*b.im ,a.re*b.im+b.re*a.im);
}
void fft(my_complex* in,int n)
{
	int L = 1; //蝶形运算层数
	while (n = n >> 1)
		L++;
	int len = 1 << L;// 将输入的一维数组对齐为 N=2^L
	int N; // 需要的扩充后的长度
	my_complex* expand = in;// 如果需要 指向扩充后的数组
	if (n * 2 == len)
		L -= 1;
	else if (n < len)
	{
		N = len; // 需要的扩充后的长度
		expand = new my_complex[N]; // 扩充后的数组
		memset(expand, 0, sizeof(my_complex)*N);
		memcpy(expand, in, sizeof(my_complex)*n);// 把之前数组里的数据复制过来
	}
	my_complex* exchange = new my_complex[N];  // 用作临时交换的数组
	for (int i = 0; i < N; i++)
	{
		int p = 0;
		for (int j = 0; j < L; j++)
			if (i&(1 << j))
				p += 1 << (L - j - 1);
		exchange[i] = expand[p];
	}
	memcpy(expand, exchange, sizeof(double)*N);// 将交换后的数据复制到expand中
	delete[]exchange;
	exchange = NULL;
	//------旋转因子----------------
	my_complex* W = new my_complex[N / 2];
	memset(W, 0, sizeof(my_complex)*N / 2);// 给出旋转因子数组 并置0
	for (int i = 0; i < N / 2; i++)
		W[i] = my_complex(cos(-2.0*3.1415926*i / N),sin(-2.0*3.1415926*i / N));
	//--------FFT算法--------------
	my_complex* out_temp = new my_complex[N]; //构建与补零后长度相同的临时输出数组
	for (int i = 0; i < L; i++) // 蝶形运算层数
	{
		int G = 1 << (L - i);
		int num = 1 << i; // 每组元素个数
		for(int j=0;j<num;j++)
			for (int k = 0; k < G; k++) //每层的组数
			{
				my_complex x1 = expand[k*num + j];
				my_complex x2 = expand[(k + 1)*num + j];
				expand[k*num + j] = x1 + W[j*(1 << (L - i - 1))] * x2;
				expand[(k + 1)*num + j] = x1 - W[j*(1 << (L - i - 1))] * x2;
			}
	}
	if (expand != NULL&&expand != in)
	{
		memcpy(in, expand, sizeof(my_complex)*n);
		delete[] expand;
		expand = NULL;
	}
	if (W != NULL)
	{
		delete[] W;
		W = NULL;
	}
	//my_complex* out = new my_complex[n]; // 构建与输入数组一样长的输出数组
	//memset(out, 0, sizeof(my_complex)*n);
	//memcpy(out, out_temp, sizeof(my_complex)*n); // 复制前n项到输出数组
	//delete[]expand;
	//delete[]W;
	//delete[]out_temp;
	//return out_temp;


}
int main()
{
	readwav read("test1.wav");
	int n = read.getlength();
	double* data = read.disp();
	double* data_test = new double[10];
	for (int i = 0; i < 10; i++)
	{
		data_test[i] = data[i];
		cout << data_test[i] << endl;	
	}
	// 注意用 new 构造的空间一定要初始化
	my_complex* out = new my_complex[10];
	memset(out, 0, sizeof(my_complex) * 10);
	dft(data_test, out, 10);
	cout << "------------------" << endl;
	for (int i = 0; i < 10; i++)
	{
		data_test[i] = sqrt(out[i].re*out[i].re + out[i].im*out[i].im);
		cout << data_test[i] << endl;
	//	cout << out[i].re << "+i" << out[i].im << endl;
	}

	//fft(data_test, 100);
	//read.disp();
	system("pause");
	
}