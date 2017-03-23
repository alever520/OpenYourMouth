#include "wavread.h"

int main()
{
	// Write WAvÎÄ¼þ
	Wave_header header(1, 48000, 16);

	uint32_t length = header.fmt_data->sample_per_sec * 10 * header.fmt_data->bits_per_sample / 8;
	uint8_t *data = new uint8_t[length];

	memset(data, 0x80, length);

	CWaveFile::write("e:\\test1.wav", header, data, length);


	//CWaveFile wave;
	//wave.read("e:\\test1.wav");

	cout << "end" << endl;
	getchar();
	return 0;
}

