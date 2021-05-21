//
// Created by Wendi Zhao on 2020/10/17.
//

#ifndef ECE250_PROJECT2_QUADTREE_NODE_H
#define ECE250_PROJECT2_QUADTREE_NODE_H
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

class Quad_node{
private:
    double x; //longitude
    double y; //latitude

    long long population;
    double cost_living;
    double net_salary;
    std::string city;

    Quad_node *nw;
    Quad_node *ne;
    Quad_node *sw;
    Quad_node *se;

public:
    Quad_node(double x_long, double y_lat, long long pop, double cost, double salary, std::string city_name);

    ~Quad_node();

    bool insert (Quad_node *node, Quad_node *root);

    Quad_node *search (Quad_node * node, double x_long, double y_lat);

    template <typename T>
    T q_max(char s);

    template <typename T>
    T q_min(char s);

    template <typename T>
    T q_total(char s);

    void clear();

    //accessors
    Quad_node* getChild(std::string dir) const;
    std::string getName() const;

    template<typename T>
    T getAttribute(char s) const;
    bool isLeaf() const;

};

//functions with templated typenames are defined in the header file


//q_max performs a level ordered traversal to determine the maximum value
template <typename T>
T Quad_node::q_max(char s) {
    //if the node is none-existent. This case should never be reached but is here for good measure.
    if (this == nullptr){
        return std::numeric_limits<T>::min();
    }

    //level order traversal base case
    if (this->isLeaf()){
        return this->getAttribute<T>(s);
    }

    //level order traversal
    T maxSW = this->sw->q_max<T>(s);
    T maxSE = this->se->q_max<T>(s);
    T maxNW = this->nw->q_max<T>(s);
    T maxNE = this->ne->q_max<T>(s);

    //compares current value with the results of the level order traversal to determine the max value
    return std::max(this->getAttribute<T>(s), std::max(maxNE, std::max(maxNW, std::max(maxSE, maxSW))));

}

//q_min performs a level ordered traversal to determine the minimum value
template <typename T>
T Quad_node::q_min(char s) {
    //if the node is none-existent. This case should never be reached but is here for good measure.
    if (this == nullptr){
        return std::numeric_limits<T>::max();
    }
    //level order traversal base case
    if (this->isLeaf()){
        return this->getAttribute<T>(s);
    }

    //level order traversal
    T minSW = this->sw->q_min<T>(s);
    T minSE = this->se->q_min<T>(s);
    T minNW = this->nw->q_min<T>(s);
    T minNE = this->ne->q_min<T>(s);

    //compares current value with the results of the level order traversal to determine the min value
    return std::min(this->getAttribute<T>(s), std::min(minNE, std::min(minNW, std::min(minSE, minSW))));

}

//q_total performs a level ordered traversal to determine the total value
template <typename T>
T Quad_node::q_total(char s) {
    //base care occurs when a empty children is reached in the level order traversal
    if (this == nullptr){
        return 0;
    }

    //level order traversal to determin the sum of the attribute
    if (s=='p'){
        return this->population + this->sw->q_total<T>(s) +this->se->q_total<T>(s)+this->ne->q_total<T>(s)+this->nw->q_total<T>(s);
    }
    else if (s=='r'){
        return this->cost_living + this->sw->q_total<T>(s) +this->se->q_total<T>(s)+this->ne->q_total<T>(s)+this->nw->q_total<T>(s);
    }
    else if (s=='s'){
        return this->net_salary + this->sw->q_total<T>(s) +this->se->q_total<T>(s)+this->ne->q_total<T>(s)+this->nw->q_total<T>(s);
    }

}

//getAttribute returns a specific attribute of a city based on the input s
template <typename T>
T Quad_node::getAttribute(char s) const {
    if (s == 'p'){
        return this->population;
    }
    else if (s=='r'){
        return this->cost_living;
    }
    else if (s=='s'){
        return this->net_salary;
    }
}


#endif //ECE250_PROJECT2_QUADTREE_NODE_H
