#!/bin/zsh

# build
mkdir ./build/
cd ./build/
cmake ..
make
cd ..

# test
mkdir ./testfile/
rm -f ./testfile/*
./bin/test.out &> ./Output_of_test.txt
