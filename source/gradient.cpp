//canny.cpp
#include "gradient.h"

int OP_PEWITT_X[9] = { -1,0,1,-1,0,1,-1,0,1 };
int OP_PEWITT_Y[9] = { 1,1,1,0,0,0,-1,-1,-1 };
int OP_SOBEL_X[9] = { -1,0,1,-2,0,2,-1,0,1 };
int OP_SOBEL_Y[9] = { 1,2,1,0,0,0,-1,-2,-1 };
int givenGausFil[49] = {  1,1,2,2,2,1,1, 1,2,2,4,2,2,1, 2,2,4,8,4,2,2 ,2,4,8,16,8,4,2 , 2,2,4,8,4,2,2 , 1,2,2,4,2,2,1 , 1,1,2,2,2,1,1  };

// Function convolution  array: image, sizeArray:size of image
//                       op: operator, sizeOp:size of operator
bool convol(int* array, int sizeArray[2], int* op, int sizeOp[2],int stride,int* outarray)
{
	size_t rowArray = sizeArray[0];
	size_t colArray = sizeArray[1];
	size_t rowOp = sizeOp[0];
	size_t colOp = sizeOp[1];

	for (int i = 0; i < rowArray ; i = i + stride)
	{
		for (int j = 0; j < colArray ; j = j + stride)
		{
            // use a temporary global array to transfer data
            // not a optimum way but working.
			outarray[i*colArray+j] = 0;
			if (i <rowOp / 2 || i >= rowArray - rowOp / 2 || j <colOp / 2 || j >= colArray - colOp / 2)
			{
				continue;
			}
			for (int p = i - rowOp / 2; p < i + rowOp / 2+1; p++)
			{
				for (int q = j - colOp / 2; q < j + colOp / 2+1; q++)
				{
					outarray[i*colArray+j] += array[p * colArray + q] * op[(p - (i - rowOp / 2)) * colOp + (q - (j - colOp / 2))];
				}
			}
		}
	}
	
	return 1;
}

// for guassian filter, may blur the image a bit but improve our overall edge detecting effect
bool gausFilter(int *array)
{
	
	int sizeImg[2] = {H,W};
	int sizeOp[2] = {GAUS_SIZE,GAUS_SIZE};
	cout << "start gaussian filtering:" <<endl;
    //since my convolution fucntion code was done in a 1d array
    int* outarray;
    outarray = new int[H*W];
	convol(array, sizeImg, givenGausFil, sizeOp,1,outarray);
	fill(outarray, array, 140, 3);
	return 1;
}

bool gradientForm(int *array,int opType,int *magArray, int *dirArray)
{
  	int rowArray = H;
	int colArray = W;
	int xGrad = 0;
	int yGrad = 0;
	if (opType == 0)
    {
        //naive way for gradient magnitude computation Gy = y[j]-y[j-1]
        for (int i = 1; i < rowArray; i++)
		{
			for (int j = 1; j < colArray; j++)
			{
				//int sizeOp[2] = { GAUS_SIZE,GAUS_SIZE };
				xGrad = array[i*colArray+j] - array[i*colArray+j-1];
				yGrad = array[i*colArray+j] - array[(i-1)*colArray+j];
				magArray[i*colArray+j] = sqrt(yGrad * yGrad + xGrad * xGrad);
				dirArray[i*colArray+j] = atan2(yGrad, xGrad) / PI * 180;
			}
		}
	}
	else if (opType == 1)
	{
        // We use pewitt operator and convlution to do gradient computing
		int sizeImg[2] = { H,W };
		int sizeOp[2] = { 3,3 };
        int *xarray,*yarray;
        xarray = new int[H*W];
        yarray = new int[H*W];
        //Gx
		convol(array, sizeImg, OP_PEWITT_X, sizeOp, 1, xarray);
		fill_no_norm(xarray, xarray,4);
        
        //Gy
		convol(array, sizeImg, OP_PEWITT_Y, sizeOp, 1, yarray);
		fill_no_norm(yarray, yarray,4);
        
        
        
        // make sure no pixel has a value larger than 255 (maximum of our greyscale)
		for (int i = 0; i < rowArray; i++)
		{
			for (int j = 0; j < colArray; j++)
			{

                //magnitude
                magArray[i*colArray+j] = sqrt(xarray[i*colArray+j]*xarray[i*colArray+j] + yarray[i*colArray+j]* yarray[i*colArray+j]);
                //direction
                if (yarray[i*colArray+j]==0|| xarray[i*colArray+j]==0)
                    dirArray[i*colArray+j] = 0;
                else
                    dirArray[i*colArray+j] = (atan2(yarray[i*colArray+j], xarray[i*colArray+j]) / PI * 180);
               
                
            
            }
		}
        /*
        for (int i = 0; i < rowArray; i++)
        {
            for (int j = 0; j < colArray; j++)
            {
                cout<<dirArray[i*colArray+j]<<' ';
            }
            cout<<endl;
        }
         */
        fill(magArray, magArray,1,4);
    }
	return 1;
}


// auxillary function for showing the max of these three values
int myMax(int a, int b, int c)
{
	if (a >= b)
	{
		if (a >= c)
			return a;
		else
			return c;
	}
	else
	{
		if (b >= c)
			return b;
		else
			return c;
	}
}

bool fill_no_norm(int* array1, int* array2,int reduce)
{
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (i>=H-reduce || j>=W-reduce||i<reduce||j<reduce)
            {
                array2[i * W + j] = 0;
            }
            
        }
    }
    
    return 1;
}

//auxillary function for truncate surrounding matrix and perform global division.
bool fill(int* array1, int* array2, int div, int reduce)
{
    int maxMag = 255;
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
            if (i>=H-reduce || j>=W-reduce||i<reduce||j<reduce)
            {
                array2[i * W + j] = 0;
            }
            else
            {
                array2[i * W + j] = abs(array1[i * W + j])/div;
                if(array2[i * W + j] > maxMag)
                {
                    maxMag = array2[i * W + j];
                }
            }
		}
	}
    
    for (int i = reduce;i < H-reduce; i++)
    {
        for (int j = reduce; j < W-reduce; j++)
        {
            
            array2[i * W + j] =  array2[i * W + j] /(1.0*maxMag)*255;
            
        }
    }
	return 1;
}


