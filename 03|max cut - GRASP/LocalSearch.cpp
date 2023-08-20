#include "LocalSearch.hpp"
#include "Graph.hpp"

LocalSearch::LocalSearch(Graph _graph)
{
    this->graph = _graph;
}

Graph LocalSearch::get_graph()
{
    return this->graph;
}

ClassicalLocalSearch::ClassicalLocalSearch(Graph _graph) : LocalSearch(_graph)
{
}

vector<int> ClassicalLocalSearch::search(vector<int> _assignment, int &_number_of_iterations)
{
    _number_of_iterations = 0;
    while (true)
    {
        int idx = 0;
        for (; idx < this->graph.n; idx++)
        {
            vector<int> neighbor_assignment = _assignment;
            neighbor_assignment[idx] = 1 - neighbor_assignment[idx];
            if (this->graph.get_maxcut(neighbor_assignment) > this->graph.get_maxcut(_assignment))
            {
                _assignment = neighbor_assignment;
                _number_of_iterations++;
                break;
            }
        }
        if (idx >= this->graph.n)
        {
            break;
        }
    }
    return _assignment;
}

vector<int> ClassicalLocalSearch::optimized_search(vector<int> _assignment, int &_number_of_iterations)
{
    _number_of_iterations = 0;
    long long best_maxcut = this->graph.get_maxcut(_assignment);
    while (true)
    {
        int idx = 0;
        for (; idx < this->graph.n; idx++)
        {
            if (this->graph.get_maxcut(idx, best_maxcut, _assignment) > best_maxcut)
            {
                _assignment[idx] = 1 - _assignment[idx];
                _number_of_iterations++;
                break;
            }
        }
        if (idx >= this->graph.n)
        {
            break;
        }
    }
    return _assignment;
}