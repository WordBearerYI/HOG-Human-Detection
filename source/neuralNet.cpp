#include "neuralNet.h"


double* layer(double *input, int sizeInput, double *output, int sizeOutput)
{
    double *weight=NULL;
    weight = new double[(sizeInput+1)*sizeOutput]{0};
    return weight;
}

//double* 
//type: 0 for sigmoid 1 for relu
double activation(double input,int type)
{
    if (type==0){
        return 1/(1+exp(-input));
    }
    else if (type==1){
        if (input<0)
            return 0;
        else
            return input;
    }
    return input;
}

