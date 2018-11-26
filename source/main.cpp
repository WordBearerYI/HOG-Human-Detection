//
//  main.cpp
//  cannyEdgeDectector
//
//  Created by syd on 2018/10/31.
//  Copyright © 2018年 syd. All rights reserved.
//
#include <iostream>
#include <stdlib.h>
#include "main.h"

using namespace std;
int main(int argc, char* argv[])
{
    //picture directory，ready to be changed by Bash Script
    string nameIn = "Lena256.bmp";
    string pwd = "/Users/syd/Desktop/c_proj/cannyEdgeDectector/cannyEdgeDectector/";
    string pwdIn = pwd + "picIn/";
    string pwdOut = pwd + "picOut/";
    cout << "start processing" << endl;
    if (readImg(pwdIn+nameIn))
    {
        cout << "opened file complete!" << endl;
        // to print a sample 10*10 subimage to see if read correctly
    }
    else
    {
        cout << "opened file failed" << endl;
        return 0;
    }
    
    if (writeImg(pwdOut+"trial.bmp", img))
    {
        cout << "ouput successful" << endl;
    }
    //Function: guas filter
    if (gausFilter(img))
    {
        cout << "gaus filtering successful" << endl;
        
        if (writeImg(pwdOut+"normalized.bmp", img))
        {
            cout << "gaus filtering ouput successful" << endl;
        }
    }
    
    //Function: gradient magnitude and direction computing
    int *magArray, *dirArray;
    magArray = new int [H*W];
    dirArray = new int [H*W];
    
    // operation type 1: apply prewitt operator, using convolution
    gradientForm(img, 1, magArray, dirArray);
    if (writeImg(pwdOut+"magGrad.bmp", dirArray))
    {
        cout << "ouput Grad mag successful" << endl;
    }
    
    //cellBins 1d array for storing cellbins for each cell. [H/s*W/s*9]*1
    double *cellBins = NULL;
    
    
    //feature 1d array for storing final features. [(H/s-1)*(W/s-1)*4*9]*1
    double *feature = NULL;
    feature = new double[bSize];
    cout<<H/CELLLENGTH<<' '<<W/CELLLENGTH<<' '<<CELLLENGTH<<endl;
    cellDivide(dirArray, magArray, cellBins, CELLLENGTH);
    //featureForm(cellBins, feature, CELLLENGTH);
    
    for (int i=0; i<H/CELLLENGTH; i++)
    {
        for (int j=0; j<W/CELLLENGTH; j++)
        {
            //for (int q = 0; q<9; q++)
               // cout<<cellBins[9*(i*W/CELLLENGTH+j)+q]<<' ';
            //cout<<endl;
        }
    }
    /*
     */
}
