//  main.h
//  cannyEdgeDectector
#pragma once
#ifndef MAIN_H
#define MAIN_H

#include "util.h"
#include "gradient.h"
#include "hog.h"
#include "neuralNet.h"

#define CELLLENGTH 8
#define BLOCKLENGTH 16
#define STRIDE 8
const int cSize = (H/CELLLENGTH)*(W/CELLLENGTH)*9;
const int bSize = (H/CELLLENGTH-1)*(W/CELLLENGTH-1)*4*9;

#endif
