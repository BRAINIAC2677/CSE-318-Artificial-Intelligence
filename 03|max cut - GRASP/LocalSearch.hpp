#ifndef LOCAL_SEARCH_HPP
#define LOCAL_SEARCH_HPP

#include <vector>
using namespace std;

#include "Graph.hpp"

class LocalSearch
{
protected:
    Graph graph;
    long long get_maxcut(vector<int> _assignment);

public:
    LocalSearch(Graph _graph);
    Graph get_graph();
    virtual vector<int> search(vector<int> _assignment) = 0;
};

// classic local search
class LocalSearch1 : public LocalSearch
{
public:
    LocalSearch1(Graph _graph);
    vector<int> search(vector<int> _assignment, int &_number_of_iterations);
};

#endif