#pragma once
#include"dft.h"
#include"time_piece.h"
//----------声明一个用来识别的函数-------------
// data为输入数据段   T为采样周期  freq为原文件的采样频率  length为原文件的长度
void recognize(double* data, double T, int freq, int length);
