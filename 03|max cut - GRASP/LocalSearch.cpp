#include "LocalSearch.hpp"
#include "Graph.hpp"

long long LocalSearch::get_maxcut(vector<int> _assignment)
{
    long long maxcut = 0;
    for (auto edge : this->graph.edges)
    {
        maxcut += (_assignment[edge.u] == _assignment[edge.v] ? 0 : edge.w);
    }
    return maxcut;
}

LocalSearch::LocalSearch(Graph _graph)
{
    this->graph = _graph;
}

Graph LocalSearch::get_graph()
{
    return this->graph;
}

LocalSearch1::LocalSearch1(Graph _graph) : LocalSearch(_graph)
{
}

vector<int> LocalSearch1::search(vector<int> _assignment, int &_number_of_iterations)
{
    while (true)
    {
        int idx = 0;
        for (; idx < this->graph.n; idx++)
        {
            vector<int> neighbor_assignment = _assignment;
            neighbor_assignment[idx] = 1 - neighbor_assignment[idx];
            if (get_maxcut(neighbor_assignment) > get_maxcut(_assignment))
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