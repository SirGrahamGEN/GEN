#!/bin/sh
DIR=$1$2
OLDPATH=$(pwd)

echo $OLDPATH
echo Generate Project: $DIR

if [ -d "$DIR" ]; then 
  rm $1 -R; 
fi

if [ ! -d "$DIR" ]; then
  mkdir $1;
fi
 
if [ -d "$DIR" ]; then 
  rm $DIR -R; 
fi

if [ ! -d "$DIR" ]; then
  mkdir $DIR;
fi

cd $DIR
cmake -G "Ninja" -DTARGET=pc ../.. 
echo Compile ...
ninja
cd $OLDPATH
