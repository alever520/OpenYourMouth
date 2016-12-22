#include <iostream>
#include<string>
#include<fstream>
#include<math.h>
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
	void disp()
	{
		double output = 0;
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
			double final_data = (double)(data_complement / (double)32768);
			output = output + final_data;
			if (i % 1764 == 0)
			{
				ofstream out("test.txt",ios::app);
				out << output << endl;
				output = 0;
			}
			
		}
	}
	
};
void fft(double* in, int n)
{
	int L = 1; //蝶形运算层数
	while (n = n >> 1)
		L++;
	int len = 1 << L;// 将输入的一维数组对齐为 N=2^L
	int N; // 需要的扩充后的长度
	double* expand;// 如果需要 指向扩充后的数组
	if (n * 2 == len)
		L -= 1;
	else if (n < len)
	{
		N = len; // 需要的扩充后的长度
		expand = new double[N]; // 扩充后的数组
		memset(expand, 0, sizeof(double)*N);
		memcpy(expand, in, sizeof(double)*n);// 把之前数组里的数据复制过来
	}
	double* exchange = new double[N];  // 用作临时交换的数组
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
	double* W = new double[N / 2];
	memset(W, 0, sizeof(double)*N / 2);// 给出旋转因子数组 并置0
	for (int i = 0; i < N / 2; i++)
		W[i] = double(cos(-2.0*3.1415926*i / N));
	//--------FFT算法--------------
	for (int i = 0; i < L; i++) // 蝶形运算层数
	{
		int G = 1 << (L - i);
		int num = 1 << i; // 每组元素个数
		for(int j=0;j<num;j++)
			for (int k = 0; k < G; k++) //每层的组数
			{
				double x1 = expand[k*num + j];
				double x2 = expand[(k + 1)*num + j];
				expand[k*num + j] = x1 + W[j*(1 << (L - i - 1))] * x2;
				expand[(k + 1)*num + j] = x1 - W[j*(1 << (L - i - 1))] * x2;
			}
	}

}
int main()
{
	readwav read("test1.wav");
	//read.disp();
	system("pause");
	
}