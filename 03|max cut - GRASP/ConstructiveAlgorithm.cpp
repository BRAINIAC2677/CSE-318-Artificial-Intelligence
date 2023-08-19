#include <random>
#include <algorithm>
using namespace std;

#include "ConstructiveAlgorithm.hpp"

void ConstructiveAlgorithm::assign(vector<int> *_assignment, Edge _edge)
{
    if ((*_assignment)[_edge.u] == -1 && (*_assignment)[_edge.v] == -1)
    {
        (*_assignment)[_edge.u] = rand() % 2;
        (*_assignment)[_edge.v] = 1 - (*_assignment)[_edge.u];
    }
    else if ((*_assignment)[_edge.u] == -1)
    {
        (*_assignment)[_edge.u] = 1 - (*_assignment)[_edge.v];
    }
    else if ((*_assignment)[_edge.v] == -1)
    {
        (*_assignment)[_edge.v] = 1 - (*_assignment)[_edge.u];
    }
}

void ConstructiveAlgorithm::random_assignment(vector<Edge> *_restricted_candidates, vector<int> *_assignment)
{
    int random_index = rand() % _restricted_candidates->size();
    assign(_assignment, (*_restricted_candidates)[random_index]);
    for (int j = random_index + 1; j < _restricted_candidates->size(); j++)
    {
        (*_restricted_candidates)[j - 1] = (*_restricted_candidates)[j];
    }
    _restricted_candidates->pop_back();
}

ConstructiveAlgorithm::ConstructiveAlgorithm(Graph _graph)
{
    this->graph = _graph;
}

Graph ConstructiveAlgorithm::get_graph()
{
    return this->graph;
}

long long ConstructiveAlgorithm::get_maxcut()
{
    vector<int> _assignment = this->construct();
    long long maxcut = 0;
    for (auto edge : this->graph.edges)
    {
        maxcut += (_assignment[edge.u] == _assignment[edge.v] ? 0 : edge.w);
    }
    return maxcut;
}

GreedyConstructiveAlgorithm::GreedyConstructiveAlgorithm(Graph _graph) : ConstructiveAlgorithm(_graph)
{
}

vector<int> GreedyConstructiveAlgorithm::construct()
{
    vector<int> assignment(this->graph.n, -1);
    sort(this->graph.edges.rbegin(), this->graph.edges.rend());
    for (auto edge : this->graph.edges)
    {
        assign(&assignment, edge);
    }
    for (auto &i : assignment)
    {
        i = max(i, 0);
    }
    return assignment;
}

SemiGreedyConstructiveAlgorithm::SemiGreedyConstructiveAlgorithm(Graph _graph) : ConstructiveAlgorithm(_graph)
{
    this->cardinality = 3;
}

void SemiGreedyConstructiveAlgorithm::set_cardinality(int _cardinality)
{
    this->cardinality = _cardinality;
}

vector<int> SemiGreedyConstructiveAlgorithm::construct()
{
    vector<int> assignment(this->graph.n, -1);
    vector<Edge> restricted_candidates;
    sort(this->graph.edges.rbegin(), this->graph.edges.rend());
    for (int i = 0; i < this->graph.m; i++)
    {
        restricted_candidates.push_back(this->graph.edges[i]);
        if (restricted_candidates.size() == this->cardinality)
        {
            random_assignment(&restricted_candidates, &assignment);
        }
    }
    while (restricted_candidates.size() > 0)
    {
        random_assignment(&restricted_candidates, &assignment);
    }
    return assignment;
}

RandomConstructiveAlgorithm::RandomConstructiveAlgorithm(Graph _graph) : ConstructiveAlgorithm(_graph)
{
}

vector<int> RandomConstructiveAlgorithm::construct()
{
    vector<int> assignment(this->graph.n, -1);
    for (int i = 0; i < this->graph.n; i++)
    {
        assignment[i] = rand() % 2;
    }
    return assignment;
}