#include <fstream>
#include <chrono>
using namespace std;
using namespace std::chrono;

#include "StatisticsGenerator.hpp"
#include "ConstructiveAlgorithm.hpp"
#include "LocalSearch.hpp"

#define inf 100000000

StatisticsGenerator::StatisticsGenerator(string _output_file_name)
{
    this->number_of_iterations = 50;
    this->output_file.open(_output_file_name, ios::app);

    ifstream temp_stream(_output_file_name);
    if (temp_stream.peek() == ifstream::traits_type::eof())
    {
        this->output_file << " Problem,,, Constructive Algorithm,,,,, Local Search,,,,,, GRASP,,,,,, Running Time" << endl;
        this->output_file << " Name, |V| or n, |E| or m, Simple Randomized, Greedy-1, Semi-Greedy-1, Greedy-2, Semi-Greedy-2, Local Search for Randomized,, Local Search for Semi-Greedy-1,, Local Search for Semi-Greedy-2,, GRASP for Randomized,, GRASP for Semi-Greedy-1,, GRASP for Semi-Greedy-2,," << endl;
        this->output_file << ",,,,,,,, Number of Iterations, Best Value, Number of Iterations, Best Value, Number of Iterations, Best Value, Number of Iterations, Best Value, Number of Iterations, Best Value, Number of Iterations, Best Value," << endl;
    }
}

void StatisticsGenerator::generate_statistics(Graph _graph)
{
    steady_clock::time_point start_time = steady_clock::now();
    RandomConstructiveAlgorithm random_constructive_algorithm(_graph);
    long long random_maxcut = 0;
    for (int i = 0; i < this->number_of_iterations; i++)
    {
        random_maxcut += random_constructive_algorithm.get_maxcut();
    }
    random_maxcut /= this->number_of_iterations;

    SemiGreedyConstructiveAlgorithm1 semi_greedy_constructive_algorithm1(_graph);
    semi_greedy_constructive_algorithm1.set_cardinality(1);
    long long greedy_maxcut1 = 0;
    for (int i = 0; i < this->number_of_iterations; i++)
    {
        greedy_maxcut1 += semi_greedy_constructive_algorithm1.get_maxcut();
    }
    greedy_maxcut1 /= this->number_of_iterations;

    semi_greedy_constructive_algorithm1.set_cardinality(5);
    long long semi_greedy_maxcut1 = 0;
    for (int i = 0; i < this->number_of_iterations; i++)
    {
        semi_greedy_maxcut1 += semi_greedy_constructive_algorithm1.get_maxcut();
    }
    semi_greedy_maxcut1 /= this->number_of_iterations;

    SemiGreedyConstructiveAlgorithm2 semi_greedy_constructive_algorithm2(_graph);
    semi_greedy_constructive_algorithm2.set_alpha(1);
    long long greedy_maxcut2 = 0;
    for (int i = 0; i < this->number_of_iterations; i++)
    {
        greedy_maxcut2 += semi_greedy_constructive_algorithm2.get_maxcut();
    }
    greedy_maxcut2 /= this->number_of_iterations;

    semi_greedy_constructive_algorithm2.set_alpha(0.9);
    long long semi_greedy_maxcut2 = 0;
    for (int i = 0; i < this->number_of_iterations; i++)
    {
        semi_greedy_maxcut2 += semi_greedy_constructive_algorithm2.get_maxcut();
    }
    semi_greedy_maxcut2 /= this->number_of_iterations;

    ClassicalLocalSearch classical_local_search(_graph);
    int n_iter1;
    long long random_local_search_maxcut = 0;
    vector<int> assignment = random_constructive_algorithm.construct();
    assignment = classical_local_search.optimized_search(assignment, n_iter1);
    // assignment = classical_local_search.search(assignment, n_iter1);
    random_local_search_maxcut = classical_local_search.get_graph().get_maxcut(assignment);

    int n_iter2;
    long long semi_greedy_local_search_maxcut1 = 0;
    assignment = semi_greedy_constructive_algorithm1.construct();
    assignment = classical_local_search.optimized_search(assignment, n_iter2);
    // assignment = classical_local_search.search(assignment, n_iter2);
    semi_greedy_local_search_maxcut1 = classical_local_search.get_graph().get_maxcut(assignment);

    int n_iter3;
    long long semi_greedy_local_search_maxcut2 = 0;
    assignment = semi_greedy_constructive_algorithm2.construct();
    assignment = classical_local_search.optimized_search(assignment, n_iter3);
    // assignment = classical_local_search.search(assignment, n_iter3);
    semi_greedy_local_search_maxcut2 = classical_local_search.get_graph().get_maxcut(assignment);

    long long random_grasp_maxcut = -inf;
    for (int i = 0; i < this->number_of_iterations; i++)
    {
        vector<int> assignment = random_constructive_algorithm.construct();
        int n_iter;
        assignment = classical_local_search.optimized_search(assignment, n_iter);
        // assignment = classical_local_search.search(assignment, n_iter);
        random_grasp_maxcut = max(random_grasp_maxcut, classical_local_search.get_graph().get_maxcut(assignment));
    }

    long long semi_greedy_grasp_maxcut1 = -inf;
    for (int i = 0; i < this->number_of_iterations; i++)
    {
        vector<int> assignment = semi_greedy_constructive_algorithm1.construct();
        int n_iter;
        assignment = classical_local_search.optimized_search(assignment, n_iter);
        // assignment = classical_local_search.search(assignment, n_iter);
        semi_greedy_grasp_maxcut1 = max(semi_greedy_grasp_maxcut1, classical_local_search.get_graph().get_maxcut(assignment));
    }

    long long semi_greedy_grasp_maxcut2 = -inf;
    for (int i = 0; i < this->number_of_iterations; i++)
    {
        vector<int> assignment = semi_greedy_constructive_algorithm2.construct();
        int n_iter;
        assignment = classical_local_search.optimized_search(assignment, n_iter);
        // assignment = classical_local_search.search(assignment, n_iter);
        semi_greedy_grasp_maxcut2 = max(semi_greedy_grasp_maxcut2, classical_local_search.get_graph().get_maxcut(assignment));
    }

    steady_clock::time_point end_time = steady_clock::now();
    duration<double> elapsed_seconds = duration_cast<duration<double>>(end_time - start_time);

    this->output_file << _graph.name << "," << _graph.n << "," << _graph.m << "," << random_maxcut << "," << greedy_maxcut1 << "," << semi_greedy_maxcut1 << "," << greedy_maxcut2 << "," << semi_greedy_maxcut2 << "," << n_iter1 << "," << random_local_search_maxcut << "," << n_iter2 << "," << semi_greedy_local_search_maxcut1 << "," << n_iter3 << "," << semi_greedy_local_search_maxcut2 << "," << this->number_of_iterations << "," << random_grasp_maxcut << "," << this->number_of_iterations << "," << semi_greedy_grasp_maxcut1 << "," << this->number_of_iterations << "," << semi_greedy_grasp_maxcut2 << "," << elapsed_seconds.count() << endl;
}

void StatisticsGenerator::generate_statistics(string _input_file_name)
{
    ifstream _input_file(_input_file_name);
    Graph graph;
    graph.name = _input_file_name.substr(_input_file_name.find_last_of("/\\") + 1);
    graph.name = graph.name.substr(0, graph.name.find_last_of("."));
    _input_file >> graph.n >> graph.m;
    graph.adj_list.assign(graph.n, vector<pair<int, long long>>());
    for (int i = 0; i < graph.m; i++)
    {
        Edge edge;
        _input_file >> edge.u >> edge.v >> edge.w;
        edge.u--;
        edge.v--;
        graph.edges.push_back(edge);
        graph.adj_list[edge.u].push_back({edge.v, edge.w});
        graph.adj_list[edge.v].push_back({edge.u, edge.w});
    }
    this->generate_statistics(graph);
}
