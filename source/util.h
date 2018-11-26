//  util.h
//  cannyEdgeDectector
#pragma once
#ifndef UTIL_H
#define UTIL_H

#include"string.h"
#include <iostream>
#include <fstream>

//!! size of the image, ready to be changed by bash
//lena: 512*512 24
//Lena256: 256*256  8
//zebra: 443*665(pad+3) 8
//tiger: 354*630(pad+2) 24
extern int H;
extern int W;

extern int num_Chn;
extern int isRead;
extern int *img;

bool readImg(std::string);
bool writeImg(std::string,int* array);
bool iniArray(size_t*);

#endif // !UTIL.H
