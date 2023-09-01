#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

#include "ID3Estimator.h"

#define ITERATIONS 20
#define SPLIT_RATIO 0.8
#define DATASET_SIZE 1728

vector<string> get_splitted_values(string line)
{
    vector<string> values;
    int start = 0;
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == ',')
        {
            values.push_back(line.substr(start, i - start));
            start = i + 1;
        }
    }
    values.push_back(line.substr(start, line.length() - start));
    return values;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <dataset_file>" << endl;
        return 0;
    }
    string dataset_file = argv[1];
    ifstream fin(dataset_file);
    vector<string> attribute_names = {"buying", "maint", "doors", "persons", "lug_boot", "safety", "class"};
    vector<map<string, string>> dataset;
    string line;
    for (int i = 0; i < DATASET_SIZE; i++)
    {
        getline(fin, line);
        vector<string> values = get_splitted_values(line);
        map<string, string> data;
        for (int i = 0; i < attribute_names.size(); i++)
        {
            data[attribute_names[i]] = values[i];
        }
        dataset.push_back(data);
    }

    ID3Estimator estimator;
    vector<double> accuracies;

    cout << "Dataset size: " << dataset.size() << endl;
    cout << "Train set size: " << int(dataset.size() * SPLIT_RATIO) << endl;
    cout << "Test set size: " << int(dataset.size() * (1 - SPLIT_RATIO)) << endl;

    cout << DIVIDER << endl;
    for (int i = 0; i < ITERATIONS; i++)
    {
        random_shuffle(dataset.begin(), dataset.end());
        vector<map<string, string>> training_data(dataset.begin(), dataset.begin() + dataset.size() * SPLIT_RATIO);
        vector<map<string, string>> test_data(dataset.begin() + dataset.size() * SPLIT_RATIO, dataset.end());
        estimator.fit("class", training_data);
        accuracies.push_back(estimator.evaluate(test_data));
        cout << "Iteration " << i + 1 << ": " << accuracies.back() << endl;
    }
    cout << DIVIDER << endl;

    double mean_accuracy = 0, standard_deviation = 0;
    for (auto accuracy : accuracies)
    {
        mean_accuracy += accuracy;
    }
    mean_accuracy /= (accuracies.size() * 1.0);
    for (auto accuracy : accuracies)
    {
        standard_deviation += (accuracy - mean_accuracy) * (accuracy - mean_accuracy);
    }
    standard_deviation /= (accuracies.size() * 1.0);

    cout << "Mean accuracy: " << mean_accuracy << endl;
    cout << "Standard deviation: " << standard_deviation << endl;

    string print_file = "car.dot";
    ofstream fout(print_file);
    estimator.print(fout);
    fout.close();
    cout << "Decision tree printed to " << print_file << endl;

    return 0;
}