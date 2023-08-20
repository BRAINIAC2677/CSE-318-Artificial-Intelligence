#ifndef STATISTICS_GENERATOR_HPP
#define STATISTICS_GENERATOR_HPP

#include <fstream>
#include <string>
using namespace std;

#include "Graph.hpp"

class StatisticsGenerator
{
    int number_of_iterations;
    ofstream output_file;

public:
    StatisticsGenerator(string _output_file_name);
    void generate_statistics(Graph _graph);
    void generate_statistics(string _input_file_name);
};

#endif