#!/bin/bash

g++ -std=c++17 ConstructiveAlgorithm.cpp LocalSearch.cpp StatisticsGenerator.cpp main.cpp -o main.o

if [ -z $1 ]; then
    echo "No input file or directory specified"
    exit 1
elif [ -z $2 ]; then
    echo "No output file specified"
    exit 1
elif [ -d $1 ]; then
    sorted_files=$(ls $1 | sort -V)
    for file in $sorted_files; do
        echo "Running $file"
        ./main.o $1/$file $2
    done
elif [ -f $1 ]; then
    echo "Running $1"
    ./main.o $1 $2
else
    echo "No input file or directory specified"
fi

rm -f *.o