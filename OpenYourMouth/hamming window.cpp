#include"hamming window.h"
double* hamming(double* data, int n)
{
	double* temp = data;
	double a = 0.46;
	for (int i = 0; i < n; i++)
	{
		temp[i] = temp[i] * ((1 - a) - a*cos(2 * PI*i / (n - 1)));
	}
	return data;
}