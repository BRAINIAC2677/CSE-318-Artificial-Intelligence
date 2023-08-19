#include "StatisticsGenerator.hpp"
#include "ConstructiveAlgorithm.hpp"
#include "LocalSearch.hpp"

StatisticsGenerator::StatisticsGenerator(string _statistics_file_name)
{
    this->statistics_file.open(_statistics_file_name);
    ifstream temp_stream(_statistics_file_name);
    if (temp_stream.peek() == ifstream::traits_type::eof())
    {
        this->statistics_file << "Name,n,m,Random-1,Greedy-1,Semi Greedy-1,No. of Iterations (Local Search),Best Value (Local Search),No. of Iterations (GRASP),Best Value (GRASP),Known Best Solution/Upper Bound" << std::endl;
    }
}

void StatisticsGenerator::generate_statistics(Graph _graph)
{
}

void StatisticsGenerator::generate_statistics(ifstream &_input_file)
{
    Graph graph;
    _input_file >> graph.n >> graph.m;
    for (int i = 0; i < graph.m; i++)
    {
        Edge edge;
        _input_file >> edge.u >> edge.v >> edge.w;
        graph.edges.push_back(edge);
    }
    this->generate_statistics(graph);
}
