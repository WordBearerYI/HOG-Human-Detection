#ifndef HOG_H
#define HOG_H
#include "util.h"
#include <math.h>
#include "main.h"

bool cellDivide(int* dirArray, int* gradArray, double *cellBins, int cellSize);
bool featureForm(double* cellBins, double* blockbins, int cellSize);
void binForm(double angle, int grad, double bins[9]);

#endif
