#include "hog.h"
using namespace std;
// bins = 9 for each cell
// form cellbins for the picture
bool cellDivide(int* dirArray, int* gradArray, double *cellBins, int cellSize)
{
    cellBins = new double[9*(H/cellSize)*(W/cellSize)];
    for (int i = 0; i<H/cellSize; i++)
    {
        for (int j=0; j<W/cellSize; j++)
        {
            //cellBins[i*W/cellSize+j] = new double[9];
            double tmpBins[9]={0};
            for (int k=0; k<cellSize; k++)
            {
                for (int p=0; p<cellSize; p++)
                {
                    cout<<dirArray[(i*cellSize+k)*W+j*cellSize+p]<<' '<<gradArray[(i*cellSize+k)*W+j*cellSize+p]<<endl;
                    binForm(dirArray[(i*cellSize+k)*W+j*cellSize+p],gradArray[(i*cellSize+k)*W+j*cellSize+p],tmpBins);
                }
            }
            //cout<<i<<' '<<j<<' '<< (i*W/cellSize+j)<<endl;
            for (int q = 0; q<9; q++)
            {
                cellBins[9*(i*(W/cellSize)+j)+q] =tmpBins[q];
                cout<<tmpBins[q]<<' ';
                //cellBins[i*W/cellSize+j][q] = tmpBins[q];
                //cout<<tmpBins[q]<<endl;
            }
            cout<<endl;
        }
    }
    return 1;
}

// form block bins, stride unit: cell
// cellBins: (H/cellSize*W/cellSize) * 9
// blockbins: (H/cellSize-1)*(W/cellSize-1)*9*4
bool featureForm(double* cellBins, double* blockbins, int cellLength)
{
    for (int i = 0; i<H/cellLength-1; i++)
    {
        for (int j=0; j<W/cellLength-1; j++)
        {
            int curNum = i*(W/cellLength-1)+j;
            double tmpBlockBins[36]={0};
            double sum = 0;
            for (int p=0; p<2; p++)
            {
                for (int q=0; q<2; q++)
                {
                    int curBinPos = (p+i)*(W/cellLength-1)+q+j;
                    for (int n=0; n<9; n++)
                    {
                        sum += cellBins[curBinPos*9+n]*cellBins[curBinPos*9+n];
                        tmpBlockBins[(p*2+q)*9+n] = cellBins[curBinPos*9+n];
                    }
                }
            }
            sum = sqrt(sum);
            for (int l=0;l<36;l++)
            {
                blockbins[36*curNum+l] = tmpBlockBins[l]/sum;
            }
        }
    }
    return 1;
}



//calculate bins for angles from -10~170
//bin 10 30 50 70 90 110 130 150 170
//ind 0  1  2  3  4  5   6   7   8
void binForm(double angle, int grad, double bins[9])
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
    
}
