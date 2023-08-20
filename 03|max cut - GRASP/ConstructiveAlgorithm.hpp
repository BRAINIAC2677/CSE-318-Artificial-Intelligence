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

class RandomConstructiveAlgorithm : public ConstructiveAlgorithm
{
public:
    RandomConstructiveAlgorithm(Graph _graph);
    vector<int> construct();
};

class SemiGreedyConstructiveAlgorithm1 : public ConstructiveAlgorithm
{
    int cardinality;

public:
    SemiGreedyConstructiveAlgorithm1(Graph _graph);
    void set_cardinality(int _cardinality);
    vector<int> construct();
};

class SemiGreedyConstructiveAlgorithm2 : public ConstructiveAlgorithm
{
    double alpha;
    void calculate_sigma_values(vector<pair<long long, long long>> &_sigma_values, vector<int> _assignment);

public:
    SemiGreedyConstructiveAlgorithm2(Graph _graph);
    void set_alpha(double _alpha);
    vector<int> construct();
};

#endif