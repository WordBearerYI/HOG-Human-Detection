#pragma once
#ifndef NEURALNET_H
#define NEURALNET_H
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <assert.h>
#include <random>

using namespace std;
typedef struct layer {
    int neu_this;
    int neu_next;
    int act_type;
    vector<double> bs;
    vector<double> neurons;
    vector<double> e;
    vector<vector<double> > weights;
}layer;


class neuNet {
    public:
        //layer vector for storing weights
        vector<layer> layers;
        vector<vector<double> > input;
        vector<double> output;
        neuNet(vector<int>);
        void init_random(layer);
        void clean();
        vector<double> mul(vector<double>, vector<double>, double, int);
        vector<double> pass();
        double pass(vector<double>);
        void train(double, int, vector<vector<double> >, vector<double>);
        double test(vector<vector<double> >,vector<double>);
        double loss(vector<double>, vector<double>);
    
    
        void setInput(vector<vector<double> >);
        void setOutput(vector<double>);
        vector<double> getInput (int);
        vector<double> getTestOutput(int);
        vector<vector<double> > getWeights(int);
        vector<double> getNeurons(int);
};

double activation(double ,int);
//vector<double> flatten(vector<vector<double> >);
#endif

