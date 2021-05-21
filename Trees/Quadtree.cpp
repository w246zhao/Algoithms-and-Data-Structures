//
// Created by Wendi Zhao on 2020/11/5.
//
#include "Quadtree.h"

//constructor, defines an empty tree
Quadtree::Quadtree() {
    root = nullptr;
    nodes = 0;
}

//destructor, uses clear to clear the tree
Quadtree::~Quadtree() {
    if (is_tree_empty()){
        return;
    }
    root ->clear();
    delete root;
    root = nullptr;
    nodes = 0;
}

//function that determine if the tree is empty
bool Quadtree::is_tree_empty() const{
    return (nodes==0);
}

//inserts a city into the tree if it is not found, uses insert in Quadtree_node to handle recursive case
void Quadtree::insert(double x_long, double y_lat, long long pop, double cost, double net_salary,
                      std::string city_name) {
    Quad_node *node = new Quad_node(x_long, y_lat, pop, cost, net_salary, city_name);
    //corner case of inserting into an empty tree
    if (root == nullptr){
        root = node;
        std::cout<<"success"<<std::endl;
        nodes++;
        return;
    }
    //if insert was successful
    bool test = root->insert(node, root);
    if (test){
        nodes++;
    }
    else{
        delete node; //deallocate the node that is to be inserted if the insert was unsuccessful
        node = nullptr;
    }
}

//searches for a city based on lat and long, references search in Quadtree_node for recursive cases
void Quadtree::search(double x_long, double y_lat) {
    //corner case of when tree is empty
    if (is_tree_empty()){
        std::cout<<"not found"<<std::endl;
        return;
    }

    Quad_node *tmp = root->search(root, x_long, y_lat);
    //if tree was not found
    if (tmp == nullptr){
        std::cout<<"not found"<<std::endl;
        return;
    }

    std::cout<<"found "<<tmp->getName()<<std::endl;
}

//finds maximum value of an attribute in a direction, references q_max in Quadtree_node
void Quadtree::q_max(double x, double y, std::string const & d, char s) {
    //handles corner case of if the tree is empty
    if (is_tree_empty()){
        std::cout<<"failure"<<std::endl;
        return;
    }
    //searches for the starting node
    Quad_node *tmp = root->search(root, x, y);
    //handles corner case of if the starting node does not exist
    if (tmp == nullptr){
        std::cout<<"failure"<<std::endl;
        return;
    }
    //get correct direction to begin the search
    tmp = tmp->getChild(d);
    //handles corner case for if the direction does not exist
    if (tmp == nullptr){
        std::cout<<"failure"<<std::endl;
        return;
    }
    if (s=='r' || s=='s'){
        auto max = tmp->q_max<double>(s);
        std::cout<<std::fixed;
        std::cout<<std::setprecision(2);
        std::cout<<"max "<<max<<std::endl;
        tmp = nullptr;
        return;
    }
    else if (s=='p'){
        auto max = tmp->q_max<long long>(s);
        std::cout<<"max "<<max<<std::endl;
        tmp = nullptr;
        return;
    }
}

//finds minimum value of an attribute in a direction, references q_min in Quadtree_node
void Quadtree::q_min(double x, double y, std::string const & d, char s) {
    //handles corner case of if the tree is empty
    if (is_tree_empty()){
        std::cout<<"failure"<<std::endl;
        return;
    }
    //searches for the starting node
    Quad_node *tmp = root->search(root, x, y);
    //handles corner case of if the starting node does not exist
    if (tmp == nullptr){
        std::cout<<"failure"<<std::endl;
        return;
    }
    //get correct direction to begin the search
    tmp = tmp->getChild(d);
    //handles corner case for if the direction does not exist
    if (tmp == nullptr){
        std::cout<<"failure"<<std::endl;
        return;
    }


    if (s=='r' || s=='s'){
        auto min = tmp->q_min<double>(s);
        std::cout<<std::fixed;
        std::cout<<std::setprecision(2);
        std::cout<<"min "<<min<<std::endl;
        tmp = nullptr;
        return;
    }
    else if (s=='p'){
        auto min = tmp->q_min<long long>(s);
        std::cout<<"min "<<min<<std::endl;
        tmp = nullptr;
        return;
    }
}

//finds total value of an attribute in a direction, references q_total in Quadtree_node
void Quadtree::q_total(double x, double y, std::string const & d, char s) {
    //handles corner case of if the tree is empty
    if (is_tree_empty()){
        std::cout<<"failure"<<std::endl;
        return;
    }
    //searches for the starting node
    Quad_node *tmp = root->search(root, x, y);
    //handles corner case of if the starting node does not exist
    if (tmp == nullptr){
        std::cout<<"failure"<<std::endl;
        return;
    }
    //gets correct direction to begin the totaling
    tmp = tmp->getChild(d);
    //handles corner case for if the direction does not exist
    if (tmp == nullptr){
        std::cout<<"failure"<<std::endl;
        return;
    }

    if (s=='r' || s=='s'){
        auto total = tmp->q_total<double>(s);
        std::cout<<std::fixed;
        std::cout<<std::setprecision(2);
        std::cout<< "total  "<<total<< std::endl;
        tmp = nullptr;
        return;
    }
    else if (s=='p'){
        auto total = tmp->q_total<long long>(s);
        std::cout<<"total "<<total<<std::endl;
        tmp = nullptr;
        return;
    }
}

//function that prints the tree with the help of print_help
void Quadtree::print() {
    //handles corner case for when tree is empty
    if (is_tree_empty()){
        return;
    }
    //references print_help to perform the in-order traversal
    std::string output = "";
    print_help(root, output);
    //prints the returned string till the second last character, removes trailing space
    output = output.substr(0, output.size()-1);
    std::cout<<output<<std::endl;
}

//performs in-order traversal to determine the order at which the tree should be printed
void Quadtree::print_help(Quad_node *root_node, std::string &output) {
    if (root_node != nullptr){
        print_help(root_node->getChild("NE"), output);
        print_help(root_node->getChild("NW"), output);
        output += root_node->getName() + " ";
        print_help(root_node->getChild("SW"), output);
        print_help(root_node->getChild("SE"), output);
    }
}

//references clear in quad_node to perform a clear using level-ordered traversal on all internal/leaf nodes
//deletes the root node after the clear is complete
void Quadtree::clear() {
    if (is_tree_empty()){
        std::cout<<"success"<<std::endl;
        return;
    }
    root ->clear();
    delete root;
    root = nullptr;
    nodes = 0;

    std::cout<<"success"<<std::endl;
}

//prints the size of the tree
void Quadtree::size() const{
    std::cout<<"tree size "<<nodes<<std::endl;
}