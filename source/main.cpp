//
//  main.cpp
//  cannyEdgeDectector
//
//  Created by syd on 2018/10/31.
//  Copyright © 2018年 syd. All rights reserved.
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "main.h"


int main(int argc, char* argv[])
{
    //current working diretory
    string pwd = "/Users/syd/Documents/CV/HOG-Human-Detection/HOG-Human-Detection/";
    string test = pwd + "test/";
    string train = pwd + "train/";
    string trial = pwd +"trial/";
    cout << "start processing" <<endl;
    vector<vector<double>> data_training(20,vector<double>(7524,0));
    vector<vector<double>> data_test(10,vector<double>(7524,0));
    //cout<<data_training[0].size();
    
    for (int i = 0;i < 10; i++)
    {
        if (readImg(train+"pos/"+to_string(i)+".bmp"))
        {
            data_training[2*i] = preprocess(img);
            cout << "opened pos training image "<< to_string(i) << endl;
            
        }
        
        if (readImg(train+"neg/"+to_string(i)+".bmp"))
        {
            data_training[2*i+1] = preprocess(img);
            cout << "opened neg training image "<< to_string(i) << endl;
            // to print a sample 10*10 subimage to see if read correctly
        }
    }
    
    for (int i = 0;i < 5; i++)
    {
        if (readImg(test+"pos/"+to_string(i)+".bmp"))
        {
            data_test[2*i] = preprocess(img);
            cout << "opened pos test image "<< to_string(2*i) << endl;
        }
        
        if (readImg(test+"neg/"+to_string(i)+".bmp"))
        {
            data_test[2*i] = preprocess(img);
            cout << "opened neg test image "<< to_string(2*i+1)  << endl;
        }
    }
    
    int hidden_size = 3;
    //int total_input_siz = 7524;
    vector<int> neuron_size={3,hidden_size,1};
    neuNet nn(3, neuron_size);
    cout<<nn.layers.size()<<" layers in total "<<endl;
   
    vector<vector<double>> input = {{1,1,2},{0,0,1},{0,1,4},{2,1,0}};
    vector<double> output = {{1},{0},{1},{1}};
    for (int i=0;i<input.size();i++)
    {
        nn.neuNet_IO(input[i], {output[i]});
        //tba
    }
    
    for (int i=0;i<2;i++)
    {
        vector<vector<double>> wt = nn.getWeights(i);
        cout<<"layer"<<i<<": "<<endl;
        
       
        for (int p=0;p<nn.layers[i].neu_this;p++)
        {
            cout<<"neurons "<<nn.layers[i].neurons[p]<<' ';
            for (int q=0;q<nn.layers[i].neu_next;q++)
            {
                
                //cout<<wt[p][q]<<' ';
            }
            //cout<<endl;
        }
        cout<<endl;
    }
    
    cout<<"final "<<nn.layers.back().neurons[0]<<endl;
    /*
    if (writeImg(trial+"trial.bmp", img))
    {
        cout << "ouput successful" << endl;
    }
    //Function: guas filter
    if (gausFilter(img))
    {
        cout << "gaus filtering successful" << endl;
        if (writeImg(trial+"normalized.bmp", img))
        {
            cout << "ouput successful" << endl;
        }
    }
   
   
    if (writeImg(pwd+trial+"magGrad.bmp", dirArray))
    {
        cout << "ouput Grad mag successful" << endl;
    }
     */
}

vector<double> preprocess(int* img)
{
    int *magArray, *dirArray;
    gausFilter(img);
    magArray = new int [H*W];
    dirArray = new int [H*W];
     //Function: gradient magnitude and direction computing
    // operation type 1: apply prewitt operator, using convolution
    gradientForm(img, 1, magArray, dirArray);
    
     //cellBins 2d vector for storing cellbins for each cell. [[H/s*W/s]*9]
    //feature 1d vector for storing final features. [(H/s-1)*(W/s-1)*4*9]*1
    //vector<double> discriptor(0,(H/CELLLENGTH-1)*(W/CELLLENGTH-1)*9*4);

    vector<double> descriptor = cellDivide(dirArray, magArray);
    
   // vector<double> discriptor = featureForm(cellBins);
    /*
    for (int i=0; i<cellBins.size(); i++)
    {
        for (int j=0; j<cellBins[0].size(); j++)
        {
            cout<<cellBins[i][j]<<' ';
        }
        cout<<endl;
    }
     */
    
    return descriptor;
}
