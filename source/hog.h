#ifndef HOG_H
#define HOG_H
#include "util.h"
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <assert.h>
using namespace std;
#ifndef CELLLENGTH
#define CELLLENGTH 8
#endif
vector<double> cellDivide(int* dirArray, int* gradArray);
//vector<double> featureForm(vector<vector<double>> &cellBins);
void binForm(double , int , vector<double>&);

#endif
