#ifndef LOCAL_SEARCH_HPP
#define LOCAL_SEARCH_HPP

#include <vector>
using namespace std;

#include "Graph.hpp"

class LocalSearch
{
protected:
    Graph graph;

public:
    LocalSearch(Graph _graph);
    Graph get_graph();
    virtual vector<int> search(vector<int> _assignment, int &_number_of_iterations) = 0;
};

class ClassicalLocalSearch : public LocalSearch
{
public:
    ClassicalLocalSearch(Graph _graph);
    vector<int> search(vector<int> _assignment, int &_number_of_iterations);
    vector<int> optimized_search(vector<int> _assignment, int &_number_of_iterations);
};

#endif