#pragma once
#ifndef NEURALNET_H
#define NEURALNET_H
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <assert.h>

using namespace std;
typedef struct layer {
    int neu_this;
    int neu_next;
    int act_type;
    vector<double> neurons;
    vector<double> e;
    vector<vector<double>> weights;
}layer;


class neuNet {
    public:
        //layer vector for storing weights
        vector<layer> layers;
        vector<double> input;
        vector<double> test_output;
        neuNet(int, vector<int>);
        layer neuNet_init_random(int ,layer);
        void neuNet_IO(vector<double>, vector<double>);
        vector<double> mul(vector<double>, vector<double>, int);
        vector<double> pass();
        void train(double, int);
        double test(vector<double>);
        double loss(vector<double>, vector<double>);
    
        vector<double> getInput ();
        vector<double> getTestOutput();
        vector<vector<double>> getWeights(int);
        vector<double> getNeurons(int);
};

double activation(double ,int);
//vector<double> flatten(vector<vector<double>>);
#endif

