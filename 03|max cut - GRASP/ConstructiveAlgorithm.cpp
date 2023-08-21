#include <random>
#include <algorithm>
#include <set>
#include <map>
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
    return this->graph.get_maxcut(_assignment);
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

SemiGreedyConstructiveAlgorithm1::SemiGreedyConstructiveAlgorithm1(Graph _graph) : ConstructiveAlgorithm(_graph)
{
    this->cardinality = 5;
}

void SemiGreedyConstructiveAlgorithm1::set_cardinality(int _cardinality)
{
    this->cardinality = _cardinality;
}

// time complexity: O(m*log(m))
vector<int> SemiGreedyConstructiveAlgorithm1::construct()
{
    this->cardinality = min(this->cardinality, this->graph.m);
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

void SemiGreedyConstructiveAlgorithm2::calculate_sigma_values(vector<pair<long long, long long>> &_sigma_values, vector<int> _assignment)
{
    _sigma_values.assign(this->graph.n, make_pair(0, 0));
    for (auto edge : this->graph.edges)
    {
        if (_assignment[edge.u] != -1 && _assignment[edge.v] == -1)
        {
            if (_assignment[edge.u] == 0)
            {
                _sigma_values[edge.v].first += edge.w;
            }
            else if (_assignment[edge.u] == 1)
            {
                _sigma_values[edge.v].second += edge.w;
            }
        }
        else if (_assignment[edge.u] == -1 && _assignment[edge.v] != -1)
        {
            if (_assignment[edge.v] == 0)
            {
                _sigma_values[edge.u].first += edge.w;
            }
            else if (_assignment[edge.v] == 1)
            {
                _sigma_values[edge.u].second += edge.w;
            }
        }
    }
}

SemiGreedyConstructiveAlgorithm2::SemiGreedyConstructiveAlgorithm2(Graph _graph) : ConstructiveAlgorithm(_graph)
{
    this->alpha = 1;
}

void SemiGreedyConstructiveAlgorithm2::set_alpha(double _alpha)
{
    this->alpha = _alpha;
}

// time complexity: O(m*log(m) + n*log(n))
vector<int> SemiGreedyConstructiveAlgorithm2::construct()
{
    vector<int> assignment(this->graph.n, -1);
    vector<pair<long long, long long>> sigma_values(this->graph.n);

    // initializing the partitions with the vertices of the maximum weighted edge
    sort(this->graph.edges.rbegin(), this->graph.edges.rend());
    assignment[this->graph.edges[0].u] = 0;
    assignment[this->graph.edges[0].v] = 1;

    this->calculate_sigma_values(sigma_values, assignment);
    multiset<long long> sigma_values_set;
    map<long long, vector<int>> sigma_values_map;
    for (int i = 0; i < this->graph.n; i++)
    {
        if (assignment[i] == -1)
        {
            sigma_values_set.insert(max(sigma_values[i].first, sigma_values[i].second));
            sigma_values_map[max(sigma_values[i].first, sigma_values[i].second)].push_back(i);
        }
    }

    for (int i = 0; i < this->graph.n - 2; i++)
    {
        // random selection from restricted candidates list
        long long wmin = *sigma_values_set.begin();
        long long wmax = *sigma_values_set.rbegin();
        long long cutoff_value = wmin + this->alpha * (wmax - wmin);
        long long random_selected_value = rand() % (wmax - cutoff_value + 1) + cutoff_value;
        random_selected_value = *sigma_values_set.lower_bound(random_selected_value);
        int random_selected_node = sigma_values_map[random_selected_value].back();

        // assigning partition to the selected vertex
        if (sigma_values[random_selected_node].first > sigma_values[random_selected_node].second)
        {
            assignment[random_selected_node] = 1;
        }
        else
        {
            assignment[random_selected_node] = 0;
        }

        // after assigning the selected vertex to a partition updating the sigma_values, sigma_values_set and sigma_values_map
        sigma_values_set.erase(sigma_values_set.find(random_selected_value));
        sigma_values_map[random_selected_value].pop_back();
        for (auto adj : this->graph.adj_list[random_selected_node])
        {
            int v = adj.first;
            long long w = adj.second;
            if (assignment[v] == -1)
            {
                sigma_values_set.erase(sigma_values_set.find(max(sigma_values[v].first, sigma_values[v].second)));
                sigma_values_map[max(sigma_values[v].first, sigma_values[v].second)].erase(find(sigma_values_map[max(sigma_values[v].first, sigma_values[v].second)].begin(), sigma_values_map[max(sigma_values[v].first, sigma_values[v].second)].end(), v));
                if (assignment[random_selected_node] == 0)
                {
                    sigma_values[v].first += w;
                }
                else
                {
                    sigma_values[v].second += w;
                }
                sigma_values_set.insert(max(sigma_values[v].first, sigma_values[v].second));
                sigma_values_map[max(sigma_values[v].first, sigma_values[v].second)].push_back(v);
            }
        }
    }
    return assignment;
}