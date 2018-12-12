#-------------Config---------------------#
#if you run this on a a Mac OSX: 1 else: 0
OSX=1
#your working directory
pwd="/Users/syd/Documents/CV/HOG-Human-Detection/HOG-Human-Detection"
src_dir="$pwd"/source
out_dir="$pwd"/output
pyFile="$src_dir"/ann.py
#your file name, if you need to perform edge detection to new image, target should be put inside picIn directory
echo "$out_dir"
rm -rf "$out_dir"
mkdir "$out_dir"
cd "$src_dir"

#define alpha and hidden_size, if not, default: alpha = 0.02, hidden_size = 500,

if [ ! -n $1 ];then
    alpha=$1
else
    alpha=1
fi

if [ ! -n $2 ];then
    hidden_size=$2
else
    hidden_size=92
fi

act="sig"
#----------------------------------------#

echo leaning_rate="$alpha"
echo hidden_size="$hidden_size"
echo "$act"

if [ -e ann.py ];then
    echo "python file found"
else
    echo "no correct python file"
fi

if [ $OSX -eq 1 ];then
    sed -i'' -e "s/salpha = .*/salpha = $alpha/g" $pyFile
    sed -i'' -e "s/hidden_size = .*/hidden_size = $hidden_size/g" $pyFile
    sed -i'' -e "s/cwd = ".*"/cwd = $pwd/output//g" $pyFile
#   sed -i'' -e "s/ly1_d = .*(n/ly1_d = $act(n/g" $pyFile
else
    sed -i "s/salpha = .*/alpha = $salpha/g" $pyFile
    sed -i "s/hidden_size = .*/hidden_size = $hidden_size/g" $pyFile
    sed -i'' -e "s/cwd = ".*"/cwd = $pwd/output//g" $pyFile
#   sed -i "s/ly1_d = .*(n/ly1_d = $act(n/g" $pyFile
fi

if [ -e main.cpp ]; then
  #if you are on Linux or Powershell, {' '} is a must
    echo "starting comiling"
    g++ ./*.cpp -o oso
    echo "executing..."
    ./oso
    echo "preprocess completed"
else
  echo "no correct main cpp file"
fi

python ann.py


