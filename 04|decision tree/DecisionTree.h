#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include <ostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

const string DIVIDER = "----------------------------------------";

class Attribute
{
    string name;
    vector<string> values;

public:
    Attribute();
    Attribute(string _name, vector<string> _values);
    string get_name();
    vector<string> get_values();
    void print(ostream &out);
};

class Node
{
public:
    virtual bool is_leaf() = 0;
};

class InternalNode : public Node
{
    Attribute attribute;
    map<string, Node *> children;

public:
    InternalNode(Attribute _attribute);
    bool is_leaf();
    Attribute get_attribute();
    void set_child(string _value, Node *_child);
    Node *get_child(string _value);
};

class LeafNode : public Node
{
    string label;

public:
    LeafNode(string _label);
    bool is_leaf();
    string get_label();
};

class DecisionTree
{
    Node *root;
    void print(ostream &out, Node *_node, int indent);

public:
    DecisionTree(Node *_root);
    string classify(map<string, string> _instance);
    void print(ostream &out);
};

#endif