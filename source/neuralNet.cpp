#include "neuralNet.h"
//using namespace std;

//from input until one layer before last
neuNet::neuNet(vector<int> neurons_size)
    {
        unsigned long size_layer = neurons_size.size();
        default_random_engine engine;
        normal_distribution<double> distribution(0,4);
        assert(size_layer==neurons_size.size());
        
        for(int i=0; i<size_layer; i++)
        {
            layer ly;
            if (i<size_layer-2)
            {
                ly.act_type = 0;
                ly.neu_next = neurons_size[i+1];
                ly.neu_this = neurons_size[i];
                vector<vector<double>> tmp (neurons_size[i],vector<double>(neurons_size[i+1],0));
                for (int j=0; j<ly.neu_this; j++)
                {
                    for (int p=0; p<ly.neu_next; p++)
                    {
                        tmp[j][p] = distribution(engine);
                        
                        cout<< tmp[j][p]<<' ';
                    }
                    cout<<endl;
                }
                
                ly.weights = tmp;
            }
            else
            {
                ly.act_type = 1;
                ly.neu_this = neurons_size[i];
                ly.weights = {{1}};
            }
            ly.bs.assign(ly.neu_next,0);
            for (int p=0; p<ly.neu_next; p++)
            {
                ly.bs[p] = distribution(engine);

            }
            
            ly.neurons.assign(neurons_size[i],0);
            this->layers.push_back(ly);
        }
    };


//method for injecting input and output.
void neuNet::clean()
    {
        //assert(input.size()==this->layers[0].neu_this && output.size() == (this->layers.back()).neu_this);
        for (int i=0;i<this->layers.size();i++)
        {
            this->layers[i].neurons.assign(layers[i].neu_this,0);
            this->layers[i].e.assign(layers[i].neurons.size(),0);
        }
        
    }

//
vector<double> neuNet::mul(vector<double> weight, vector<double> neuron, double bias, int type)
    {
        vector<double> res(weight.size()/neuron.size(),0);
        
        //if (weight[0].size()!=neuron.size())
        //return res;
        for (int i=0; i<weight.size()/neuron.size(); i++)
        {
            for (int j=0;j<neuron.size();j++)
            {
                res[i] += weight[i*neuron.size()+j]*neuron[j];
            }
            res[i] += bias;
            res[i] = activation(res[i], type);
        }
        //cout<<"bias: "<<bias<<' ';
        return res;
    }

    
vector<double> neuNet::pass()
    {
        //vector<double> hidden = mul((this->layers[0].weights)[0],this->input,0);
        //vector<double> res = mul((this->layers[0].weights)[0],this->input,0);
        cout<<"output: ";
        vector<double> out(this->input.size(),0);
        for (int j=0; j<this->input.size(); j++)
        {
            this->layers[0].neurons = this->input[j];
            //cout<<j<<' '<<input[j].size()<< " element ";
            for (int i=0; i<this->layers.size()-1; i++)
            {
                for (int q=0; q<this->layers[i].weights[0].size(); q++)
                {
                    for (int p=0; p<this->layers[i].weights.size(); p++)
                    {
                        this->layers[i+1].neurons[q] += this->layers[i].weights[p][q]*this->layers[i].neurons[p];
                    }
                    this->layers[i+1].neurons[q] += this->layers[i].bs[q];
                    this->layers[i+1].neurons[q] = activation(this->layers[i+1].neurons[q], this->layers[i].act_type);
                   
                }
                
            }
            
            out[j] = layers.back().neurons[0];
            cout<< out[j]<<' ';
        }
        cout<<endl;
        return out;
    }

double neuNet::pass(vector<double> input)
{
    //vector<double> hidden = mul((this->layers[0].weights)[0],this->input,0);
    //vector<double> res = mul((this->layers[0].weights)[0],this->input,0);
    
    this->layers[0].neurons = input;
    for (int i=0; i<this->layers.size()-1; i++)
    {
            for (int q=0; q<this->layers[i].weights[0].size(); q++)
            {
                for (int p=0; p<this->layers[i].weights.size(); p++)
                {
                    this->layers[i+1].neurons[q] += this->layers[i].weights[p][q]*this->layers[i].neurons[p];
                }
                this->layers[i+1].neurons[q] += this->layers[i].bs[q];
                
                this->layers[i+1].neurons[q] = activation(this->layers[i+1].neurons[q], this->layers[i].act_type);
                
            }
            //this->layers[i+1].neurons = this->mul(res,this->layers[i].neurons,this->layers[i+1].b,this->layers[i].act_type);
    }
    cout<<" output: "<<this->layers.back().neurons[0];
    return this->layers.back().neurons[0];
}
    
//alpha:learning rate, step for limitation
void neuNet::train(double alpha, int step_limit, vector<vector<double>> input, vector<double> output)
    {
        this->setInput(input);
        this->setOutput(output);
        vector<double> inter_output = this->pass();
        this->clean();
        
        
        for (unsigned long i=0; i<this->layers.size()-1; i++)
        {
            cout<<"----------------"<<5550000555<<"---------------------"<<endl;
            cout<<"layer: " << i << endl;
            cout<<"weight: " << endl;
            
            for (int p=0;p<this->layers[i].weights.size();p++)
            {
                for (int q=0;q<this->layers[i].weights[0].size();q++)
                {
                    cout<<this->layers[i].weights[p][q]<<' ';
                }
                cout<<endl;
            }
            cout<<"layer: "<<i<<" bias: "<< endl;
            for (int p=0;p<this->layers[i].neu_next;p++)
                cout<<this->layers[i].bs[p] <<' ';
            cout<<endl;
        }
        
        
        
        while (loss(inter_output,this->output)>0.3&&step_limit>0)
        {
           // cout<<"step_limit: "<<step_limit<<" remaining"<<endl;
            //here we only consider situation final output with one neuron
            //this->layers.back().e.assign(out[0]-this->output[0],1);
            for (int sample=1;sample<this->input.size();sample++)
            {
                double single_inter_output = this->pass(this->input[sample]);
                this->layers.back().e[0] = single_inter_output - this->output[sample];
                
            for (unsigned long i=this->layers.size()-2; i>0; i--)
            {
                for (int p=0;p<this->layers[i].weights.size();p++)
                {
                    for (int q=0;q<this->layers[i].weights[0].size();q++)
                    {
                        //sigmoid activation function
                        if (this->layers[i].act_type==1)
                        {
                            this->layers[i].e[p] = this->layers[i+1].e[q]*this->layers[i+1].neurons[q]*(1-this->layers[i+1].neurons[q]);
                            this->layers[i].weights[p][q] += alpha*this->layers[i].e[p]*this->layers[i].neurons[p];
                            this->layers[i].bs[q] += alpha*this->layers[i].e[p];
                        }
                        // relu activation function
                        else
                        {
                            if (this->layers[i+1].neurons[q]>=0)
                            {
                                this->layers[i].e[p] =this->layers[i+1].e[q];
                                this->layers[i].weights[p][q] += alpha*this->layers[i].e[p]*this->layers[i].neurons[p];
                                this->layers[i].bs[q] += alpha*this->layers[i].e[p];
                            }
                            else
                            {
                                this->layers[i].e[p] = 0;
                            }
                        }
                    }
                }
                
            }
            }
            for (unsigned long i=0; i<this->layers.size()-1; i++)
            {
                cout<<"----------------"<<step_limit<<"---------------------"<<endl;
                cout<<"layer: "<< i<<endl;
                cout<<"weight: "<<endl;
                
                for (int p=0;p<this->layers[i].weights.size();p++)
                {
                    for (int q=0;q<this->layers[i].weights[0].size();q++)
                    {
                        cout<<this->layers[i].weights[p][q]<<' ';
                    }
                    cout<<endl;
                }
                cout<<"layer: "<<i<<" bias: "<< endl;
                for (int p=0;p<this->layers[i].neu_next;p++)
                    cout<<this->layers[i].bs[p] <<' ';
                cout<<endl;
            }
            
            this->clean();
            inter_output = this->pass();
            step_limit -= 1;
        }
    }


double neuNet::test(vector<vector<double>> input, vector<double> output)
    {
        setInput(input);
        vector<double> out = this->pass();
        for  (int i=0;i<output.size();i++)
        {
            cout<<out[i]<<' ';
        }
        cout<<endl;
        
        double los = loss(out,output)/output.size();
        //cout<<los;
        double accuracy = 0;
        for (int i=0;i<output.size();i++)
        {
            if ((out[i]>0.5 && output[i]==1)||(out[i]<=0.5 && output[i]==0))
                accuracy++;
        }
        cout<<"accurracy: "<<accuracy/output.size()<<" loss: "<<los<<endl;
        //return accuracy/output.size();
        return los;
    }


    
double neuNet::loss(vector<double> output, vector<double> testoutput)
    {
        double los = 0;
        for (int i=0;i<output.size();i++)
        {
            los += (output[i]-testoutput[i])*(output[i]-testoutput[i]);
        }
        cout<<"//////////////loss: "<<los/2<<endl;
        return los/2;
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
void neuNet::setInput(vector<vector<double>> input)
{
    this->input = input;
}
void neuNet::setOutput(vector<double> output)
{
    this->output = output;
}
vector<double> neuNet::getInput (int i)
{
    return this->input[i];
}
vector<double> neuNet::getTestOutput(int i)
{
    return this->output;
}
vector<vector<double>> neuNet::getWeights(int i)
{
    return this->layers[i].weights;
}
vector<double> neuNet::getNeurons(int i)
{
    return this->layers[i].neurons;
}

//type: 1 for sigmoid 0 for relu
double activation(double input,int type)
{
    if (type==1)
    {
        return 1.0/(1+exp(-input));
    }
    else {
        if (input<=0)
            return 0;
        else
            return input;
    }
    return input;
}



