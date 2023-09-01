#! /bin/bash

dataset_file=$1

if [ -z "$dataset_file" ]; then
    echo "Usage: ./run.sh <dataset_file>"
    exit 1
fi

if [ ! -f "$dataset_file" ]; then
    echo "File $dataset_file does not exist"
    exit 1
fi

g++ DecisionTree.cpp ID3Estimator.cpp main.cpp -o main
./main "$dataset_file"
rm main
