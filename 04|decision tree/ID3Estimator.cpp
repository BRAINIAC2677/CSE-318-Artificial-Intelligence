#include <set>
#include <math.h>
using namespace std;

#include "ID3Estimator.h"

bool ID3Estimator::validate_fit_args(string _y_attribute, vector<map<string, string>> _training_data)
{
    return _training_data.size() > 0 && _training_data[0].find(_y_attribute) != _training_data[0].end();
}

vector<Attribute> ID3Estimator::find_attributes(vector<map<string, string>> _data)
{
    set<string> attribute_set;
    vector<Attribute> attributes;
    for (auto instance : _data)
    {
        for (auto attribute : instance)
        {
            attribute_set.insert(attribute.first);
        }
    }
    for (auto attribute_name : attribute_set)
    {
        set<string> value_set;
        for (auto instance : _data)
        {
            if (instance.find(attribute_name) != instance.end())
            {
                value_set.insert(instance[attribute_name]);
            }
        }
        vector<string> values;
        for (auto value : value_set)
        {
            values.push_back(value);
        }
        attributes.push_back(Attribute(attribute_name, values));
    }
    return attributes;
}

// call this function after finding all attributes
Attribute ID3Estimator::find_y_attribute(string _y_attribute)
{
    for (size_t i = 0; i < this->attributes.size(); i++)
    {
        if (this->attributes[i].get_name() == _y_attribute)
        {
            return this->attributes[i];
        }
    }
    return Attribute("null", vector<string>());
}

// call this function after finding all attributes
vector<Attribute> ID3Estimator::find_x_attributes(string _y_attribute)
{
    vector<Attribute> x_attributes;
    for (size_t i = 0; i < this->attributes.size(); i++)
    {
        if (this->attributes[i].get_name() != _y_attribute)
        {
            x_attributes.push_back(this->attributes[i]);
        }
    }
    return x_attributes;
}

void ID3Estimator::replace_null_values()
{
    for (auto &instance : this->training_data)
    {
        for (auto &attribute : instance)
        {
            if (attribute.second == "")
            {
                attribute.second = get_most_common_value(attribute.first);
            }
        }
    }
}

string ID3Estimator::get_most_common_value(string _attribute_name)
{
    return this->get_most_common_value(this->training_data, _attribute_name);
}

string ID3Estimator::get_most_common_value(vector<map<string, string>> _data, string _attribute_name)
{
    map<string, int> value_counts;
    for (auto instance : _data)
    {
        if (instance.find(_attribute_name) != instance.end())
        {
            value_counts[instance[_attribute_name]]++;
        }
    }
    int max_count = 0;
    string most_common_value;
    for (auto value_count : value_counts)
    {
        if (value_count.second > max_count)
        {
            max_count = value_count.second;
            most_common_value = value_count.first;
        }
    }
    return most_common_value;
}

void ID3Estimator::preprocess(string _y_attribute, vector<map<string, string>> _training_data)
{
    this->training_data = _training_data;
    this->attributes = this->find_attributes(this->training_data);
    this->y_attribute = this->find_y_attribute(_y_attribute);
    this->x_attributes = this->find_x_attributes(_y_attribute);
    this->replace_null_values();
}

map<string, vector<map<string, string>>> ID3Estimator::get_split_data(vector<map<string, string>> _data, Attribute _attribute)
{
    map<string, vector<map<string, string>>> split_data;
    for (auto instance : _data)
    {
        if (instance.find(_attribute.get_name()) != instance.end())
        {
            split_data[instance[_attribute.get_name()]].push_back(instance);
        }
    }
    for (auto value : _attribute.get_values())
    {
        if (split_data.find(value) == split_data.end())
        {
            split_data[value] = vector<map<string, string>>();
        }
    }
    return split_data;
}

double ID3Estimator::calculate_entropy(vector<map<string, string>> _data)
{
    map<string, int> value_counts;
    for (auto instance : _data)
    {
        if (instance.find(this->y_attribute.get_name()) != instance.end())
        {
            value_counts[instance[this->y_attribute.get_name()]]++;
        }
    }
    double entropy = 0;
    for (auto value_count : value_counts)
    {
        double p = (double)value_count.second / _data.size();
        entropy -= p * log2(p);
    }
    return entropy;
}

double ID3Estimator::calculate_gain(vector<map<string, string>> _data, Attribute _attribute)
{
    double gain = this->calculate_entropy(_data);
    auto split_data = this->get_split_data(_data, _attribute);
    for (auto split : split_data)
    {
        double p = (double)split.second.size() / _data.size();
        gain -= p * this->calculate_entropy(split.second);
    }
    return gain;
}

Node *ID3Estimator::build_tree(vector<Attribute> _attributes, vector<map<string, string>> _current_data, vector<map<string, string>> _parent_data)
{
    // 1. if no instances left, return most common value of y in parent data
    if (_current_data.size() == 0)
    {
        return new LeafNode(this->get_most_common_value(_parent_data, this->y_attribute.get_name()));
    }

    // 2. if no attributes left, return most common value of y in current data
    if (_attributes.size() == 0)
    {
        return new LeafNode(this->get_most_common_value(_current_data, this->y_attribute.get_name()));
    }

    // 3. if all instances have same label, return that label
    string label = _current_data[0][this->y_attribute.get_name()];
    bool same_label = true;
    for (auto instance : _current_data)
    {
        if (instance[this->y_attribute.get_name()] != label)
        {
            same_label = false;
            break;
        }
    }
    if (same_label)
    {
        return new LeafNode(label);
    }

    // 4. find attribute with max gain and recurse down until above base 3 case occurs.
    double max_gain = 0;
    Attribute max_gain_attribute;
    for (auto attribute : _attributes)
    {
        double gain = this->calculate_gain(_current_data, attribute);
        if (gain > max_gain)
        {
            max_gain = gain;
            max_gain_attribute = attribute;
        }
    }
    InternalNode *node = new InternalNode(max_gain_attribute);
    auto split_data = this->get_split_data(_current_data, max_gain_attribute);
    vector<Attribute> new_attributes;
    for (auto attribute : _attributes)
    {
        if (attribute.get_name() != max_gain_attribute.get_name())
        {
            new_attributes.push_back(attribute);
        }
    }
    for (auto split : split_data)
    {
        node->set_child(split.first, this->build_tree(new_attributes, split.second, _current_data));
    }
    return node;
}

bool ID3Estimator::fit(string _y_attribute, vector<map<string, string>> _training_data)
{
    if (!this->validate_fit_args(_y_attribute, _training_data))
    {
        return false;
    }
    this->preprocess(_y_attribute, _training_data);
    Node *root = this->build_tree(this->x_attributes, this->training_data, this->training_data);
    this->tree = new DecisionTree(root);
    return true;
}

string ID3Estimator::predict(map<string, string> _instance)
{
    return this->tree->classify(_instance);
}

double ID3Estimator::evaluate(vector<map<string, string>> _test_data)
{
    int correct = 0;
    for (auto instance : _test_data)
    {
        if (this->predict(instance) == instance[this->y_attribute.get_name()])
        {
            correct++;
        }
    }
    return (double)correct / _test_data.size();
}

void ID3Estimator::print(ostream &out)
{
    out << "Attributes:\n"
        << DIVIDER << "\n";
    for (auto attribute : this->attributes)
    {
        attribute.print(out);
    }
    out << DIVIDER << "\nTree:\n";
    this->tree->print(out);
}