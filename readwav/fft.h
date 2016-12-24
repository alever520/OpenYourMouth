#pragma once
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
my_complex operator +(my_complex &a, my_complex &b)
{
	return _my_complex(a.re + b.re, a.im + b.im);
}
my_complex operator -(my_complex &a, my_complex &b)
{
	return _my_complex(a.re - b.re, a.im - b.im);
}
my_complex operator *(my_complex &a, my_complex &b)
{
	return _my_complex(a.re*b.re - a.im*b.im, a.re*b.im + b.re*a.im);
}