//  main.cpp
//  cannyEdgeDectector
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
    string trial = pwd + "trial/";
    cout << "start processing" <<endl;
    vector<vector<double>> data_training(20,vector<double>(7524,0));
    vector<double> output_training(20,0);
    vector<vector<double>> data_test(10,vector<double>(7524,0));
    vector<double> output_test(10,0);
    //cout<<data_training[0].size();
    char ss;
    for (int i = 0;i < 10; i++)
    {
        if (readImg(train+"pos/"+to_string(i)+ ".bmp"))
        {
            data_training[2*i] = preprocess(img);
            output_training[2*i] = 1;
            cout << "opened pos training image "<< to_string(i) << endl;
            
        }
        
        if (readImg(train+"neg/"+to_string(i)+".bmp"))
        {
            data_training[2*i+1] = preprocess(img);
            output_training[2*i+1] = 0;
            cout << "opened neg training image "<< to_string(i) << endl;
            // to print a sample 10*10 subimage to see if read correctly
        }
    }
    
    for (int i=0; i<data_training[0].size()/(11*19); i++)
    {
        cout<<data_training[3][i]<<' ';
        if( i%9==0 && i!=0 )
            cout<<endl;
    }
    cin>>ss;
    for (int i = 0;i < 5; i++)
    {
        if (readImg(test+"pos/"+to_string(i)+".bmp"))
        {
            data_test[2*i] = preprocess(img);
            output_test[2*i] = 1;
            cout << "opened pos test image "<< to_string(2*i) << endl;
        }
        
        if (readImg(test+"neg/"+to_string(i)+".bmp"))
        {
            data_test[2*i+1] = preprocess(img);
            output_test[2*i+1] = 0;
            cout << "opened neg test image "<< to_string(2*i+1)  << endl;
        }
    }
    
    
  
    //int total_input_siz = 7524;
    int total_input_siz = 2;
    //int hidden_size = 500;
    int hidden_size = 10;
    vector<int> neuron_size={total_input_siz,hidden_size,1};
    neuNet nn (neuron_size);
    
    
    
    
    double accu = 0;
    //accu = nn.test(data_training,output_training);
    vector<vector<double>> data = {{1,1},{0,0},{0,1},{1,0},{2,0},{-2,-3},{-1,-1},{3,0}};
    vector<double> output = {1,0,1,1,1,0,0,1};
    accu = nn.test(data,output);
    cout<<"training accuracy: " <<accu<<endl;
    
    cout<<nn.layers.size()<<" layers in total "<<endl;
    
    //nn.setInput(data_training);
    //nn.setOutput(output_training);

    nn.train(0.0005,10,data,output);
    
    //double accu_t,accu_tr = 0;
    double accu_tr = nn.test(data,output);
    //accu_t = nn.test(data_test,output_test);
   
   /*
   
    
    accu_tr = nn.test(data_training,output_training);
    accu_t = nn.test(data_test,output_test);
    
    cout<<"training accuracy: " <<accu_tr<< " test accuracy: "<<accu_t<<endl;
    
   

    */
}
void toFileCSV(string name, vector<double> data)
{
    ofstream myfile;
    
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
    
    /*
    for (int i=0; i<H; i++)
    {
        for (int j=0; j<W; j++)
        {
            cout<<dirArray[i*W+j]<<' ';
        }
        cout<<endl;
    }
    */
     //cellBins 2d vector for storing cellbins for each cell. [[H/s*W/s]*9]
    //feature 1d vector for storing final features. [(H/s-1)*(W/s-1)*4*9]*1
    //vector<double> discriptor(0,(H/CELLLENGTH-1)*(W/CELLLENGTH-1)*9*4);
    vector<double> descriptor = cellDivide(dirArray, magArray);
    return descriptor;
}
