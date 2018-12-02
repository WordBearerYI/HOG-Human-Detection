//  util.h
//  cannyEdgeDectector
#pragma once
#ifndef UTIL_H
#define UTIL_H

#include"string.h"
#include <iostream>
#include <fstream>

//!! size of the image, ready to be changed by bash
//human 96*160
extern int H;
extern int W;

extern int num_Chn;
extern int isRead;
extern int *img;

bool readImg(std::string);
bool writeImg(std::string,int* array);
bool iniArray(size_t*);

#endif // !UTIL.H
