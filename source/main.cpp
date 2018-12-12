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
    //current working diretory pwd defined in main.h
    string test = pwd + "test/";
    string train = pwd + "train/";
    cout << "start processing" <<endl;
    //intialized for storing training and test data.
    vector<vector<double> > data_training(20,vector<double>(7524,0));
    vector<double> output_training(20,0);
    vector<vector<double> > data_test(10,vector<double>(7524,0));
    vector<double> output_test(10,0);
    
    //preprocess for every train and test images
    for (int i = 0;i < 10; i++)
    {
        if (readImg(train+"pos/"+to_string(i)+ ".bmp"))
        {
            
            data_training[2*i] = preprocess(img,0);
            output_training[2*i] = 1;
            cout << "opened pos training image "<< to_string(i) << endl;
            toFileCSV(pwd+"/output/train.csv" ,1, data_training[2*i]);
            if (i==5)
            {
                toTxT(pwd+"/output/crop001278a.txt", data_training[2*i]);
            }
        }
        
        if (readImg(train+"neg/"+to_string(i)+".bmp"))
        {
           
            data_training[2*i+1] = preprocess(img,0);
            output_training[2*i+1] = 0;
            cout << "opened neg training image "<< to_string(i) << endl;
            // to print a sample 10*10 subimage to see if read correctly
            toFileCSV(pwd+"/output/train.csv" ,0, data_training[2*i+1]);
        }
    }
    //output txt files for inspection
    for (int i = 0;i < 5; i++)
    {
        if (readImg(test+"pos/"+to_string(i)+".bmp"))
        {
            data_test[2*i] = preprocess(img,1);
            output_test[2*i] = 1;
            cout << "opened pos test image"<< to_string(2*i) << endl;
            toFileCSV(pwd+"/output/test.csv" ,1, data_test[2*i]);
            if (i==3)
            {
                toTxT(pwd+"/output/crop001045b.txt", data_test[2*i]);
            }
        }
        
        if (readImg(test+"neg/"+to_string(i)+".bmp"))
        {
            data_test[2*i+1] = preprocess(img,1);
            output_test[2*i+1] = 0;
            cout << "opened neg test image "<< to_string(2*i+1)  << endl;
            toFileCSV(pwd+"/output/test.csv" ,0, data_test[2*i+1]);
        }
    }
}

//output our hog vectors to txt format as requested
void toTxT(string name, vector<double> data)
{
    ofstream myfile(name,std::ofstream::out | std::ofstream::app);
    for (int i=0;i<data.size();i++)
    {
        myfile<<to_string(data[i])<<endl;
    }
}

//output our vectors to csv format
void toFileCSV(string name, int label, vector<double> data)
{
    ofstream myfile(name,std::ofstream::out | std::ofstream::app);
    myfile<<to_string(label)<<",";
    for (int i=0;i<data.size();i++)
    {
        myfile<<data[i]<<' ';
    }
    myfile<<endl;
}

//proprocess core function utilized gradientForm from gradient.cpp and cellDivide from hog.cpp
vector<double> preprocess(int* img, int isOut)
{
    
    int *magArray, *dirArray;
    gausFilter(img);
    magArray = new int [H*W];
    dirArray = new int [H*W];
    //Function: gradient magnitude and direction computing
    // operation type 1: apply prewitt operator, using convolution
    gradientForm(img, 1, magArray, dirArray);
    //if this flag variable is 1, we output gradient mag to directory out
    if (isOut==1)
    {
        string dir = pwd+"output/"+ to_string(picnum)+".bmp";
        picnum++;
        writeImg(dir,magArray);
    }
    //cellBins 2d vector for storing cellbins for each cell. [[H/s*W/s]*9]
    //feature 1d vector for storing final features. [(H/s-1)*(W/s-1)*4*9]*1
    //vector<double> discriptor(0,(H/CELLLENGTH-1)*(W/CELLLENGTH-1)*9*4);
    vector<double> descriptor = cellDivide(dirArray, magArray);
    return descriptor;
}
