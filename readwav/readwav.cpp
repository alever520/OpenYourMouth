#include <iostream>
#include<string>
#include<fstream>
using namespace std;
class readwav
{
	fstream fp;
	string ChunkID;
	short ChunkSize;
	string Format;
	string SubChunk1ID;
	short SubChunk1Size;
	string AudioFormat;
	int NumChannels;
	short SampleRate;
	short ByteRate;
	int BlockAlign;
	int BitsPerSample;
	string SubChunk2ID;
	short SubChunk2Size;
	unsigned char* data;
public:
	readwav(fstream& fp)
	{

	}
};
int main()
{
	
	
}