#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
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
    vector<Edge> edges;
};
typedef struct Graph Graph;

#endif