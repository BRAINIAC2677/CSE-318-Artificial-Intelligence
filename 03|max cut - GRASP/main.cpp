#include <iostream>
#include <string>
using namespace std;

#include "StatisticsGenerator.hpp"

string out_file_name = "statistics.csv";

int main(int argc, char **argv)
{
    StatisticsGenerator statistics_generator(argv[2]);
    statistics_generator.generate_statistics(argv[1]);
    return 0;
}