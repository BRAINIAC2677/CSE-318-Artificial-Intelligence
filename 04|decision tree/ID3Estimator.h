#ifndef ID3ESTIMATOR_H
#define ID3ESTIMATOR_H

#include <string>
#include <vector>
#include <map>
using namespace std;

#include "DecisionTree.h"

class ID3Estimator
{
    Attribute y_attribute;
    vector<Attribute> x_attributes;
    vector<Attribute> attributes;
    vector<map<string, string>> training_data;
    DecisionTree *tree;

    bool validate_fit_args(string _y_attribute, vector<map<string, string>> _training_data);
    vector<Attribute> find_attributes(vector<map<string, string>> _data);
    Attribute find_y_attribute(string _y_attribute);
    vector<Attribute> find_x_attributes(string _y_attribute);
    void replace_null_values();
    string get_most_common_value(string _attribute_name);
    string get_most_common_value(vector<map<string, string>> _data, string _attribute_name);
    void preprocess(string _y_attribute, vector<map<string, string>> _training_data);
    map<string, vector<map<string, string>>> get_split_data(vector<map<string, string>> _data, Attribute _attribute);
    double calculate_entropy(vector<map<string, string>> _data);
    double calculate_gain(vector<map<string, string>> _data, Attribute _attribute);
    Node *build_tree(vector<Attribute> _attributes, vector<map<string, string>> _current_data, vector<map<string, string>> _parent_data);

public:
    bool fit(string _y_attribute, vector<map<string, string>> _training_data);
    string predict(map<string, string> _instance);
    double evaluate(vector<map<string, string>> _test_data);
    void print(ostream &out);
};

#endif