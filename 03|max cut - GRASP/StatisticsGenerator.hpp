#ifndef STATISTICS_GENERATOR_HPP
#define STATISTICS_GENERATOR_HPP

#include <fstream>
#include <string>
using namespace std;

#include "Graph.hpp"

class StatisticsGenerator
{
    ofstream statistics_file;

public:
    StatisticsGenerator() {}
    StatisticsGenerator(int _n) {}
    StatisticsGenerator(string _statistics_file_name);
    void generate_statistics(Graph _graph);
    void generate_statistics(ifstream &_input_file);
};

#endif