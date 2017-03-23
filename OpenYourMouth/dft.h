#pragma once
#include "hamming window.h"
#define PI 3.1415926
typedef struct _my_complex
{
	double re;
	double im;
	// ¹¹Ôìº¯Êý
	_my_complex() {}
	_my_complex(double a, double b)
	{
		re = a;
		im = b;
	}
}my_complex;
bool my_dft(double* in, int n, int m);
