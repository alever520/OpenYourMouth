#include"hamming window.h"
void hamming(double* data, int n)
{
	double a = 0.46;
	for (int i = 0; i < n; i++)
	{
		data[i] = data[i] * ((1 - a) - a*cos(2 * PI*i / (n - 1)));
	}
}