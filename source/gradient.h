#ifndef GRADIENT_H
#define GRADIENT_H

#include "util.h"
#include <math.h>  
using namespace std;
// for guassian operator matrix generation
#define GAUS_SIZE 7
#define SIGMA 3
#define PI 3.14159265358979323846

//bool convol(int(&array)[H][W], double(&op)[GAUS_SIZE][GAUS_SIZE], int);
bool convol(int* array, int sizeImg[2], int* op, int sizeOp[2], int* outarray);
bool gausFilter(int* array);
bool gradientForm(int* array, int, int* grad, int* dir);
int angle_class(double);
int myMax(int, int, int);
bool fill(int* array1, int* array2, int div, int reduce);
bool fill_no_norm(int* array1, int* array2,int reduce);
#endif
