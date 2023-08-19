#ifndef CONSTRUCTION_ALGORITHM_HPP
#define CONSTRUCTION_ALGORITHM_HPP

#include <vector>
using namespace std;

#include "Graph.hpp"

class ConstructiveAlgorithm
{
protected:
    Graph graph;
    void assign(vector<int> *_assignment, Edge _edge);
    void random_assignment(vector<Edge> *_restricted_candidates, vector<int> *_assignment);

public:
    ConstructiveAlgorithm(Graph _graph);
    Graph get_graph();
    virtual vector<int> construct() = 0;
    long long get_maxcut();
};

// greedy construction
class GreedyConstructiveAlgorithm : public ConstructiveAlgorithm
{
public:
    GreedyConstructiveAlgorithm(Graph _graph);
    vector<int> construct();
};

// cardinality based semi greedy construction
class SemiGreedyConstructiveAlgorithm : public ConstructiveAlgorithm
{
    int cardinality;

public:
    SemiGreedyConstructiveAlgorithm(Graph _graph);
    void set_cardinality(int _cardinality);
    vector<int> construct();
};

class RandomConstructiveAlgorithm : public ConstructiveAlgorithm
{
public:
    RandomConstructiveAlgorithm(Graph _graph);
    vector<int> construct();
};

#endif