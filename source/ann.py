import numpy as np
import csv
import os
import math
import matplotlib.pyplot as plt

cwd = "/Users/syd/Documents/CV/HOG-Human-Detection/HOG-Human-Detection/output/"

# sigmoid function and its derivative for back propagation
def sig(x, dev = False):
    if(dev==True):
        return x*(1-x);
    return 1.0/(1+np.exp(-x))

# implementation for relu and its derivative for back propagation
def relu(x ,dev = False):
    u = np.copy(x)
    for i in range(len(u)):
        for j in range(len(u[0])):
            if (dev==True):
                if u[i,j]<=0:
                    u[i,j] = -0.3
                else:
                    u[i,j] = 1
            else:
                if u[i,j]<=0:
                    u[i,j] =  -u[i,j]*0.3
    return u

# for reading my csv files
def readCsv(name):
    data = []
    label = []
    with open(name) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        index = 0
        for row in csv_reader:
            data_tmp = [1]
            sub_ind = 0
            for i in row[1].split():
                sub_ind+=1
                num = float(i)
                if math.isnan(num):
                    num = 0
                data_tmp.append(num)
            data.append(data_tmp)
            label.append(float(row[0]))
            index += 1
    print("data_num:",len(data)," data_size", len(data[0]))
    return data,label

data_train_1,label_train_1  = readCsv(cwd+'train.csv')
data_test_1,label_test_1 = readCsv(cwd+'test.csv')
data_train = np.array(data_train_1)
data_test = np.array(data_test_1)

label_train = np.array(label_train_1)
label_test = np.array(label_test_1)

#for testng the functionality of this script using obvious examples(linear seperable).
###
#data_train = np.array([[1,1],[0,0],[0,1],[1,0],[2,0],[-2,-3],[-1,-1],[3,0]])
#label_train = np.array([[1],[0],[1],[1],[1],[0],[0],[1]])
###

sample_num = len(data_train)
input_size = len(data_train[0])

#hyper parameters

hidden_size = 92
out_size = 1
salpha = 1
limit_ite = 10000

#42!
np.random.seed(42)
#b0 is embedded in to w0 [b0 w01 w02....;b1 w11 w12...] for vecetorization
w0 = np.random.normal(0,1,(input_size,hidden_size))
#b1 only size 1, doesn't matter
w1 = np.random.normal(0,1,(hidden_size,1))
b1 = np.random.normal(-1,1)

#first layer input
ly0 = data_train
t = np.reshape(label_train,(len(label_train),1))

errors = []
iteration = 0
loss = len(data_train)
accuracy = 0
alpha=salpha

#for test accuarcy and loss
def test(data,w0,w1):
    accuracy  = 0
    ly0 = data_test
    ly1 = sig(np.dot(ly0,w0))
    ly2 = sig(np.dot(ly1,w1)+b1)
    t = np.reshape(label_test,(len(label_test),1))
    ly2r = np.array([1 if i>=0.5 else 0 for i in ly2])
    for index in range(len(ly2)):
        if ly2r[index] == t[index]:
            accuracy += 1
        ly2[index] =round(ly2[index],2)

    accuracy = round(accuracy*1.0/len(ly2),2)
    print "\ntest accuracy: ", accuracy," test loss: ", np.mean((ly2-t)*(ly2-t))/2,'\n'
    print "output: ", np.reshape(ly2,(1,len(ly0))),'\n',"label: ", np.reshape(t,(1,len(ly0)))
    return accuracy

#training
while iteration<limit_ite:
    #vectorized feed forward
    #ly0 = data_train
    ly1 = sig(np.dot(ly0,w0))
    ly2 = sig(np.dot(ly1,w1)+b1)
    #print ("layer: ", np.shape(ly0),' ',np.shape(ly1),' ',np.shape(ly2),'\n')
    
    #back propagation
    ly2_e = t - ly2
    ly2_d = sig(ly2 ,dev = True)*ly2_e
    
    ly1_e = np.dot(ly2_d,w1.T)
    ly1_d = sig(ly1 ,dev = True)*ly1_e

    w1 += np.dot(ly1.T,ly2_d)*alpha
    b1 += np.sum(ly2_d) *alpha/len(ly2_d)
    w0 += np.dot(ly0.T,ly1_d)*alpha
    
    #error/loss computing
    e = np.mean(ly2_e*ly2_e/2.0)
    errors.append(e)
   
    if iteration % 100==0:
        for index in range(len(ly2)):
            if ly2[index]>=0.5 and t[index]==1:
                accuracy += 1
            elif ly2[index]<0.5 and t[index]==0:
                accuracy += 1
            ly2[index] = round(ly2[index],2)
        accuracy = accuracy/len(ly2)
        print "\n========================+iteration+ ",iteration,"================================\n",
        print "training loss: ", e, " training accuracy: ",max(accuracy,1.0),'\n'
        print "output: ", np.reshape(ly2,(1,sample_num)), '\n', "label: ", np.reshape(t,(1,sample_num))
        if (e<=1e-2 and iteration>800):
            #change of loss
            if test(data_test,w0,w1)>0.9 or e-laste<1e-6:
                print "early stop!"
                break
        if iteration>limit_ite:
            break
    #record loss from this time
    iteration += 1
    laste = e

#plot
#plt.figure()
plt.plot(errors)
plt.xlabel('Training Iteration')
plt.ylabel('Error')
plt.show()
