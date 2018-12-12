YI SHI 2018 ys3237@nyu.edu
Computer Vision Project 2, NYU

-train  : where I store training images
-test 	: where I store test images
-output	: output image and descriptor sample directory 
-source	: source code directory
    -gradient.cpp/h : to get gradient magnitude and direction
    -util.cpp/h	 : from scratch read and write bmp function
    -main.cpp/h  : main 
    -hog.cpp/h   : creating descriptor 
    -neuralNet.cpp/h: where my c++ attempt for a tiny neural network toolbox(ignore)
    -ann.py      : actual realization of my neural network.
 
-run.sh : bash shell script for running the program
	  config inside: remember to change working directory, image name, your platform 


How to use it:
Simply configure the directory where you store target image and whether you run this on a Mac. XXX.bmp is only the name of your image.

> ./run.sh  
you can also use parameter without entering the files.
> ./run.sh $learning_rate $hidden_size $hidden_layer_act_type {relu/sig}
for example ./run.sh 0.02 250 

Or

You can compile and run c project
And then execute the python script for neural network