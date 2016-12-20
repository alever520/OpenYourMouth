#include <iostream>
#include<string>
#include<fstream>
using namespace std;
class readwav
{
	fstream fp;
	char ChunkID[4];
	unsigned int ChunkSize;
	char Format[4];
	char SubChunk1ID[4];
	unsigned int SubChunk1Size[4];
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
		fp.seekg(4,ios::cur);
		//fp.read((char*)&ChunkSize, sizeof(ChunkSize));//sizeof(ChunkSize)
		fp.seekg(4, ios::cur);
		fp.read((char*)&Format, sizeof(Format));//sizeof(Format)
		fp.seekg(4, ios::cur);
		fp.read((char*)&SubChunk1ID, sizeof(SubChunk1ID));
		fp.seekg(4, ios::cur);
		fp.read((char*)&SubChunk1Size, sizeof(SubChunk1Size));
		//fp.seekg(0x12);
		//fp.read((char*)&AudioFormat, sizeof(AudioFormat));
		//fp.seekg(0x14);
		//fp.read((char*)&NumChannels, sizeof(NumChannels));
		//fp.seekg(0x18);
		//fp.read((char*)&SampleRate, sizeof(SampleRate));
		//fp.seekg(0x1c);
		//fp.read((char*)&ByteRate, sizeof(ByteRate));
		//fp.seekg(0x20);
		//fp.read((char*)&BlockAlign, sizeof(BlockAlign));
		//fp.seekg(0x22);
		//fp.read((char*)&BitsPerSample, sizeof(BitsPerSample));
		//fp.seekg(0x24);
		//fp.read((char*)&SubChunk2ID, sizeof(SubChunk2ID));
		fp.seekg(0x28);
		fp.read((char*)&SubChunk2Size, sizeof(SubChunk2Size));
		//long length = char2num(SubChunk2Size);
		fp.seekg(0x2c);
		//data = new unsigned char[SubChunk2Size];
		//fp.read((char*)&data, sizeof(data));

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

	}
	//void char2num(char*p)
	//{
	//	while (*p != '\0')
	//	{
	//		if (*p >= '0' && c <= '9')
	//			return c - '0';
	//		else if (*p >= 'a' && c <= 'f')
	//			return (c - 'a' + 10);
	//		else if (*p >= 'A' && c <= 'F')
	//			return (c - 'A' + 10);
	//		//assert(0);
	//		return 0;
	//	}
	//}
};
int main()
{
	readwav read("test.wav");
	system("pause");
	
}