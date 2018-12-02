#include "neuralNet.h"
//using namespace std;

//from input until one layer before last
neuNet::neuNet(int size_layer, vector<int> neurons_size)
    {
        assert(size_layer==neurons_size.size());
        for(int i=0; i<size_layer; i++)
        {
            layer ly;
            if (i<size_layer-1)
            {
                ly.act_type = 1;
                ly.neu_next = neurons_size[i+1];
                ly.neu_this = neurons_size[i];
                vector<vector<double>> tmp (neurons_size[i],vector<double>(neurons_size[i+1],0));
                ly.weights = tmp;
                ly = neuNet_init_random(1,ly);
            }
            else
            {
                ly.act_type = 0;
                ly.neu_this = neurons_size[i];
            }
           
            ly.neurons.assign(0,neurons_size[i]);
            this->layers.push_back(ly);
        }
    };
    
layer neuNet::neuNet_init_random(int type, layer ly)
    {
        srand(time(NULL));
        for (int j=0; j<ly.neu_this; j++)
            for (int p=0; p<ly.neu_next; p++)
                ly.weights[j][p] = rand()/RAND_MAX;
        
        return ly;
    };
    
//method for injecting input and output.
void neuNet::neuNet_IO(vector<double> input, vector<double> output)
    {
        //assert(input.size()==this->layers[0].neu_this && output.size() == (this->layers.back()).neu_this);
        for (int i=0;i<this->layers.size();i++){
            this->layers[i].neurons.assign(layers[i].neu_this,0);
        }
        this->input = input;
        this->layers[0].neurons = input;
        this->test_output = output;
        (this->layers.back()).neurons = output;
        (this->layers.back()).act_type = 1;
        
    }
    
vector<double> neuNet::mul(vector<double> weight, vector<double> neuron, int type)
    {
        vector<double> res(0,weight.size()/neuron.size());
        
        //if (weight[0].size()!=neuron.size())
         //   return res;
        for (int i=0; i<weight.size()/neuron.size(); i++)
        {
            for (int j=0;j<neuron.size();j++)
            {
                res[i] += weight[i*neuron.size()+j]*neuron[j];
            }
            res[i] = activation(res[i], type);
        }
        return res;
    }

    
vector<double> neuNet::pass()
    {
        //vector<double> hidden = mul((this->layers[0].weights)[0],this->input,0);
        //vector<double> res = mul((this->layers[0].weights)[0],this->input,0);
        for (int i=0; i <this->layers.size()-1; i++)
        {
            vector<double> res(0,this->layers[i].weights.size()*this->layers[i].weights[0].size());
            for (int p=0;p<this->layers[i].weights.size();p++)
            {
                for (int q=0;q<this->layers[i].weights[0].size();q++)
                {
                    res[p*this->layers[i].weights[0].size()+q] = this->layers[i].weights[p][q];
                }
            }
            if (i<this->layers.size()-2)
                this->layers[i+1].neurons = this->mul(res,this->layers[i].neurons,1);
            else
                this->layers[i+1].neurons = this->mul(res,this->layers[i].neurons,0);
        }
        return layers.back().neurons;
    }
    
    
//alpha:learning rate, step for limitation
void neuNet::train(double alpha, int step)
    {
        vector<double> out = this->pass();
        while (loss(this->test_output,out)>0.2||step<=0)
        {
            //here we onl consider situation final output with one neuron
            this->layers.back().e.assign(out[0]-this->test_output[0],1);
            for (unsigned long i=this->layers.size()-2; i>0; i--)
            {
                this->layers[i].e.assign(0,layers[i].neurons.size());
            
                for (int p=0;p<this->layers[i].weights.size();p++)
                {
                    for (int q=0;q<this->layers[i].weights[0].size();q++)
                    {
                        
                        //sigmoid activation function
                        if (this->layers[i].act_type==0)
                        {
                            this->layers[i].e[p] = this->layers[i+1].e[q]*this->layers[i+1].neurons[q]*(1-this->layers[i+1].neurons[q])*this->layers[i].neurons[p];
                            this->layers[i].weights[p][q] += alpha*this->layers[i].e[p];
                        }
                        // relu activation function
                        else
                        {
                            if (this->layers[i+1].neurons[q]>=0)
                            {
                                this->layers[i].e[p] =this->layers[i+1].e[q]*this->layers[i].neurons[p];
                                this->layers[i].weights[p][q] += alpha*this->layers[i].e[p];
                            }
                            else
                            {
                                this->layers[i].e[p] = 0;
                            }
                        }
                    }
                }
            }
            step -= 1;
        }
    }
    
double neuNet::test(vector<double> testInput)
    {
        vector<double> out = this->pass();
        double l = loss(out,testInput);
        return l;
    }
    
double neuNet::loss(vector<double> output, vector<double> test)
    {
        double l = 0;
        for (int i=0;i<output.size();i++)
        {
            l+= (output[i]-test[i])*(output[i]-test[i]);
        }
        return sqrt(l);
    }
    
    /*
    void printWeight()
    {
        for (int i=0;i<this->layers.size();i++)
        {
            for (int j=0;j<this->layers[i].weights.size();j++)
            {
                cout << this->layers[i].weights[j] << ' ';
            }
            cout << endl;
        }
    }
    */

vector<double> neuNet::getInput ()
{
    return this->input;
}
vector<double> neuNet::getTestOutput()
{
    return this->test_output;
}
vector<vector<double>> neuNet::getWeights(int i)
{
    return this->layers[i].weights;
}
vector<double> neuNet::getNeurons(int i)
{
    return this->layers[i].neurons;
}

//type: 0 for sigmoid 1 for relu
double activation(double input,int type)
    {
        if (type==0)
        {
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
/*
vector<double> flatten(vector<vector<double>> twod)
{
    vector<double> res(0,twod.size()*twod[0].size());
    for (int p=0;p<twod.size();p++)
    {
        for (int q=0;q<twod[0].size();q++)
        {
            res[p*twod[0].size()+q] = twod[p][q];
        }
    }
    return res;
}
 */




