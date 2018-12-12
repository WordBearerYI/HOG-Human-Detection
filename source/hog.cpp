#include "hog.h"
// bins = 9 for each cell
// form cellbins for the picture

//form histogram for each cell
vector<double> cellDivide(int* dirArray, int* gradArray)// double *cellBins, int cellSize)
{
    vector<vector<double> > cellBins((H/CELLLENGTH)*(W/CELLLENGTH),vector<double>(9,0));
    for (int i = 0; i<H/CELLLENGTH; i++)
    {
        for (int j=0; j<W/CELLLENGTH; j++)
        {
            vector<double> tmpBins(9,0);
            for (int k=0; k<CELLLENGTH; k++)
            {
                for (int p=0; p<CELLLENGTH; p++)
                {
                    //cout<<dirArray[(i*CELLLENGTH+k)*W+j*CELLLENGTH+p]<<' '<<gradArray[(i*CELLLENGTH+k)*W+j*CELLLENGTH+p]<<endl;
                    binForm(dirArray[(i*CELLLENGTH+k)*W+j*CELLLENGTH+p],gradArray[(i*CELLLENGTH+k)*W+j*CELLLENGTH+p],tmpBins);
                }
            }
            cellBins[i*(W/CELLLENGTH)+j] = tmpBins;
        }
    }
    // form block bins, stride unit: cell
    // cellBins: (H/cellSize*W/cellSize) * 9
    // blockbins: (H/cellSize-1)*(W/cellSize-1)*9*4
    
    //store 2d descriptors N*1, {(H/cellSize-1)*(W/cellSize-1)}*{36}
    vector<vector<double> > descriptor((H/CELLLENGTH-1)*(W/CELLLENGTH-1),vector<double>(9*4,0));
    //store flat descriptors {(H/cellSize-1)*(W/cellSize-1)*9*4}*1
    vector<double> descriptor_flat((H/CELLLENGTH-1)*(W/CELLLENGTH-1)*36,0);
    
    cout<<descriptor.size()<<' '<<descriptor[0].size()<<endl;
    cout<<cellBins.size()<<' '<<cellBins[0].size()<<endl;
    for (int i = 0; i<H/CELLLENGTH-1; i++)
    {
        for (int j=0; j<W/CELLLENGTH-1; j++)
        {
            double sum = 0;
            for (int p=0; p<2; p++)
            {
                for (int q=0; q<2; q++)
                {
                    //forming block from cells;
                    for (int n=0; n<9; n++)
                    {
                        sum += cellBins[(i+p)*(W/CELLLENGTH-1)+j+q][n]*cellBins[(i+p)*(W/CELLLENGTH-1)+j+q][n];
                        descriptor[i*(W/CELLLENGTH-1)+j][(p*2+q)*9+n]= cellBins[(i+p)*(W/CELLLENGTH-1)+j+q][n];
                    }
                }
            }
            sum = sqrt(sum);
            for (int l=0; l<36; l++)
            {
                descriptor[i*(W/CELLLENGTH-1)+j][l] = descriptor[i*(W/CELLLENGTH-1)+j][l]/sum;
            }
        }
    }
    
    for (int i = 0; i<descriptor.size(); i++)
    {
        for (int j=0; j<descriptor[0].size(); j++)
        {
            descriptor_flat[i*descriptor[0].size()+j] = descriptor[i][j];
        }
    }
    return descriptor_flat;
}


//calculate bins for angles from -10~170
//bin 10 30 50 70 90 110 130 150 170
//ind 0  1  2  3  4  5   6   7   8
//divide between neighbors with proportion
void binForm(double angle, int grad, vector<double>&bins)
{
    if (angle >= 170)
    {
        angle -= 180;
    }
    if (angle < -10)
    {
        angle += 180;
    }
    if (angle <= 0)
    {
        bins[0] += grad*(20-abs(angle))/20.0;
        bins[9] += grad*(abs(angle))/20.0;
    }
    else if (angle > 160)
    {
        bins[0] += grad*((angle)-160)/20.0;
        bins[9] += grad*(180-angle)/20.0;
    }
    else if (angle >0 && angle <= 20)
    {
        bins[0] += grad*(20-(angle))/20.0;
        bins[1] += grad*(angle)/20.0;
    }
    else if (angle >20 && angle <= 40)
    {
        bins[1] += grad*(40-angle)/20.0;
        bins[2] += grad*(angle-20)/20.0;
    }
    else if (angle >40 && angle <= 60)
    {
        bins[2] += grad*(60-angle)/20.0;
        bins[3] += grad*(angle-40)/20.0;
    }
    else if (angle > 60 && angle <= 80)
    {
        bins[3] += grad*(80-angle)/20.0;
        bins[4] += grad*(angle-60)/20.0;
    }
    else if (angle > 80 && angle <= 100)
    {
        bins[4] += grad*(100-angle)/20.0;
        bins[5] += grad*(angle-80)/20.0;
    }
    else if (angle > 100 && angle <= 120)
    {
        bins[5] += grad*(120-angle)/20.0;
        bins[6] += grad*(angle-100)/20.0;
    }
    else if (angle > 120 && angle <= 140)
    {
        bins[6] += grad*(140-angle)/20.0;
        bins[7] += grad*(angle-120)/20.0;
    }
    else if (angle > 140 && angle <= 160)
    {
        bins[7] += grad*(160-angle)/20.0;
        bins[8] += grad*(angle-140)/20.0;
    }
    return;
}
