#include <iostream>
using namespace std;

#include "DecisionTree.h"

Attribute::Attribute() {}

Attribute::Attribute(string _name, vector<string> _values) : name(_name), values(_values) {}

string Attribute::get_name()
{
    return name;
}

vector<string> Attribute::get_values()
{
    return values;
}

void Attribute::print(ostream &out)
{
    out << name << ": ";
    for (auto value : values)
    {
        out << value << " ";
    }
    out << endl;
}

InternalNode::InternalNode(Attribute _attribute) : attribute(_attribute) {}

bool InternalNode::is_leaf()
{
    return false;
}

Attribute InternalNode::get_attribute()
{
    return attribute;
}

void InternalNode::set_child(string _value, Node *_child)
{
    children[_value] = _child;
}

Node *InternalNode::get_child(string _value)
{
    return children[_value];
}

LeafNode::LeafNode(string _label) : label(_label)
{
}

bool LeafNode::is_leaf()
{
    return true;
}

string LeafNode::get_label()
{
    return label;
}

void DecisionTree::print(ostream &out, Node *_node, int indent)
{
    if (_node->is_leaf())
    {
        LeafNode *leaf_node = (LeafNode *)_node;
        out << leaf_node->get_label() << "\n";
    }
    else
    {
        InternalNode *internal_node = (InternalNode *)_node;
        Attribute attribute = internal_node->get_attribute();
        for (auto value : attribute.get_values())
        {
            for (int i = 0; i < indent; i++)
            {
                out << "-";
            }
            out << attribute.get_name() << " = " << value << ":" << ((internal_node->get_child(value))->is_leaf() ? "" : "\n");
            print(out, internal_node->get_child(value), indent + 4);
        }
    }
}

DecisionTree::DecisionTree(Node *_root) : root(_root)
{
}

string DecisionTree::classify(map<string, string> _instance)
{
    Node *node = root;

    while (!node->is_leaf())
    {
        InternalNode *internal_node = (InternalNode *)node;
        string attribute_value = _instance[internal_node->get_attribute().get_name()];
        node = internal_node->get_child(attribute_value);
    }
    LeafNode *leaf_node = (LeafNode *)node;
    return leaf_node->get_label();
}

void DecisionTree::print(ostream &out)
{
    print(out, this->root, 0);
}