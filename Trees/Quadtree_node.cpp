//
// Created by Wendi Zhao on 2020/11/5.
//
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include "Quadtree_node.h"

//constructor, sets city parameters
Quad_node::Quad_node(double x_long, double y_lat, long long pop, double cost, double salary, std::string city_name) {
    x = x_long;
    y = y_lat;
    population = pop;
    cost_living = cost;
    city = city_name;
    net_salary = salary;

    nw = nullptr;
    ne = nullptr;
    sw = nullptr;
    se = nullptr;
}

//destructor
Quad_node::~Quad_node() =default;

//handles recursive case of insert
bool Quad_node::insert(Quad_node *node, Quad_node *root) {

    //base case for when node already exists, tolerance of 0.00001
    if (std::fabs(node->x - root->x) < 0.00001 && std::fabs(node->y - root->y)<0.00001){
        std::cout<<"failure"<<std::endl;
        return false;
    }

    //base cases for inserting a node
    if (node -> x >= root ->x && node->y > root -> y){
        if (root->ne == nullptr){
            root->ne = node;
            std::cout<<"success"<<std::endl;
            return true;
        }
    }
    else if (node -> x < root ->x && node->y >= root -> y){
        if (root->nw == nullptr){
            root->nw = node;
            std::cout<<"success"<<std::endl;
            return true;
        }
    }
    else if (node -> x <= root ->x && node->y < root -> y){
        if (root->sw == nullptr){
            root->sw = node;
            std::cout<<"success"<<std::endl;
            return true;
        }
    }
    else if (node -> x > root ->x && node->y <= root -> y){
        if (root->se == nullptr){
            root->se = node;
            std::cout<<"success"<<std::endl;
            return true;
        }
    }

    //recursive cases for inserting a node
    if (node -> x >= root ->x && node->y > root -> y){
        return insert(node, root->ne);
    }
    else if (node -> x < root ->x && node->y >= root -> y){
        return insert(node, root->nw);
    }
    else if (node -> x <= root ->x && node->y < root -> y){
        return insert(node, root->sw);
    }
    else if (node -> x > root ->x && node->y <= root -> y){
        return insert(node, root->se);
    }


}

//handles recursive case of search
Quad_node* Quad_node::search(Quad_node *node, double x_long, double y_lat) {
    //base case for when the node to begin the search  from does not exist (node not found or tree is empty)
    if (node == nullptr){
        return nullptr;
    }

    //base case for when the node is found, tolerance of 0.00001
    if (std::fabs(node->x - x_long) < 0.00001 && std::fabs(node->y - y_lat)<0.00001){
        return node;
    }

    //recursive cases
    if (x_long >= node->x && y_lat > node -> y){
        return search(node->ne, x_long, y_lat);
    }
    else if (x_long < node->x && y_lat >= node -> y) {
        return search(node->nw, x_long, y_lat);
    }
    else if (x_long <= node->x && y_lat < node -> y) {
        return search(node->sw, x_long, y_lat);
    }
    else if (x_long > node->x && y_lat <= node -> y) {
        return search(node->se, x_long, y_lat);
    }
}

//clears the nodes, level order traversal
void Quad_node::clear() {
    if (this != nullptr){
        //level order traversal to reach the bottom of the tree
        this->ne->clear();
        this->nw->clear();
        this->se->clear();
        this->sw->clear();

        //deletes children
        delete this->ne;
        delete this->nw;
        delete this->se;
        delete this->sw;

        //gets rid of dangling pointers
        this->ne = nullptr;
        this->nw = nullptr;
        this->se = nullptr;
        this->sw = nullptr;
    }
}

//get children of node in specific direction, accessor
Quad_node * Quad_node::getChild(std::string dir) const {
    if (dir == "NE"){
        return this->ne;
    }
    else if (dir == "NW"){
        return this->nw;
    }
    else if (dir == "SE"){
        return this->se;
    }
    else{
        return this->sw;
    }
}
//gets name of a city, accessor
std::string Quad_node::getName() const { return this->city; }
//determines if a node is a leaf node
bool Quad_node::isLeaf() const { return (this->ne == nullptr && this->nw == nullptr &&this->se == nullptr&&this->sw == nullptr); }

