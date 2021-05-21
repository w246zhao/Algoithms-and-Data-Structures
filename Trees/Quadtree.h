//
// Created by Wendi Zhao on 2020/10/17.
//

#ifndef ECE250_PROJECT2_QUADTREE_H
#define ECE250_PROJECT2_QUADTREE_H
#include <iomanip>
#include "Quadtree_node.h"

class Quadtree{
private:
    Quad_node *root;
    int nodes; //holds size of tree
public:

    Quadtree();

    ~Quadtree();

    bool is_tree_empty() const;

    void insert(double x_long, double y_lat, long long pop, double cost, double net_salary, std::string city_name);

    void search(double x_long, double y_lat);

    void q_max(double x, double y, std::string const & d, char s);

    void q_min(double x, double y, std::string const & d, char s);

    void q_total(double x, double y, std::string const & d, char s);

    void print();

    void print_help(Quad_node* root_node, std::string &output);

    void clear ();

    void size() const;

};



#endif //ECE250_PROJECT2_QUADTREE_H
