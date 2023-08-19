#!/bin/bash

g++ -std=c++17 ConstructiveAlgorithm.cpp LocalSearch.cpp StatisticsGenerator.cpp main.cpp -o main.o

if [ -d $1 ]; then
    for file in $1/*; do
        echo "Running $file"
        ./main.o $file
    done
elif [ -f $1 ]; then
    echo "Running $1"
    ./main.o $1
else
    echo "No input file or directory specified"
fi

rm -f *.o