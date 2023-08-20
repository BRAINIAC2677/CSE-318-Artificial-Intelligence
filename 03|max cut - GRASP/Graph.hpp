#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>
using namespace std;

struct Edge
{
    int u, v;
    long long w;

    bool operator<(const Edge &other) const
    {
        return w < other.w;
    }
};
typedef struct Edge Edge;

struct Graph
{
    int n, m;
    string name;
    vector<Edge> edges;
    vector<vector<pair<int, long long>>> adj_list;

    long long get_maxcut(vector<int> _assignment)
    {
        long long maxcut = 0;
        for (auto edge : this->edges)
        {
            maxcut += (_assignment[edge.u] == _assignment[edge.v] ? 0 : edge.w);
        }
        return maxcut;
    }

    long long get_maxcut(int _change_index, long long _prev_maxcut, vector<int> _prev_assignment)
    {
        long long maxcut = _prev_maxcut;
        for (auto adj : this->adj_list[_change_index])
        {
            int v = adj.first;
            long long w = adj.second;
            maxcut += (_prev_assignment[_change_index] == _prev_assignment[v] ? w : -w);
        }
        return maxcut;
    }
};
typedef struct Graph Graph;

#endif