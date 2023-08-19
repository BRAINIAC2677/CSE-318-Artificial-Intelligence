#include <iostream>
#include <string>
using namespace std;

#include "StatisticsGenerator.hpp"

string out_file_name = "statistics.txt";

int main()
{
    StatisticsGenerator statistics_generator(out_file_name);
    return 0;
}