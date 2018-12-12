//  main.h
//  cannyEdgeDectector
#pragma once
#ifndef MAIN_H
#define MAIN_H

#include "util.h"
#include "gradient.h"
#include "hog.h"
#include "neuralNet.h"

using namespace std;

#define CELLLENGTH 8
const int cSize = (H/CELLLENGTH)*(W/CELLLENGTH)*9;
const int bSize = (H/CELLLENGTH-1)*(W/CELLLENGTH-1)*4*9;


const string pwd = "/Users/syd/Documents/CV/HOG-Human-Detection/HOG-Human-Detection/";
int picnum = 0;

vector<double> preprocess(int* img,int isOut);
void toFileCSV(string, int, vector<double>);
void toTxT(string, vector<double>);

#endif
